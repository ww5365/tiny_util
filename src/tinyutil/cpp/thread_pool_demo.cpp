#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>
#include <iostream>
#include <cmath>



class ThreadPool {
// https://blog.csdn.net/GavinGreenson/article/details/72770818  这篇有代码的详细说明
/*
其它补充说明：
1. thread  和  pthread  区别？  
    
    - thread 是c++ 11标准开始提供，可以跨平台； pthread 是posix库提供，主要运行再linux平台
    - thread 构造函数
        thread() noexcept;
        template <class Fn, class... Args>explicit thread (Fn&& fn, Args&&... args); 
*/

public:
    ThreadPool(size_t);
    template <class F, class... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type>;
    ~ThreadPool();

private:
    // need to keep track of threads so we can join them
    std::vector<std::thread> workers;
    // the task queu
    std::queue<std::function<void()>> tasks;

    // synchronization
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};

// the constructor just launches some amount of workers
inline ThreadPool::ThreadPool(size_t threads) : stop(false)
{
    for (size_t i = 0; i < threads; ++i)
        workers.emplace_back([this] {
            for (;;) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(this->queue_mutex);
                    // condition.wait(lock, [this]{…}): 使当前线程进入阻塞状态： 当第二个参数为false时，wait()会阻塞当前线程，为true时解除阻塞；在本例中的条件就是，当线程池运行或者任务列表为空时，线程进入阻塞态。然后判断，如果线程池运行或者任务列表为空则继续后续操作，否则退出这个[this]{…}线程函数。
                    this->condition.wait(lock, [this] { return this->stop || !this->tasks.empty(); });
                    if (this->stop && this->tasks.empty())
                        return;
                    task = std::move(this->tasks.front());
                    this->tasks.pop();
                }
                task();
            }
        });
}

// add new work item to the pool
template <class F, class... Args>
auto ThreadPool::enqueue(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type>
{
    using return_type = typename std::result_of<F(Args...)>::type;

    auto task =
        std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
        // packaged_task 类型是 return_type FUN()  等价于  f(Args args ...) -> return_type

    std::future<return_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        // don't allow enqueueing after stopping the pool
        if (stop) {
            std::cerr << "enqueue on stopped ThreadPool" << std::endl;
            abort();
        }
        tasks.emplace([task]() { (*task)(); });  // task指向的f(Args args ...) 任务进入线程池；当线程池中的任务被调用时，执行(*task)()
    }
    condition.notify_one(); //解除一个正在等待唤醒的线程的阻塞态
    return res;
}

// the destructor joins all threads
inline ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();
    for (std::thread& worker : workers)
        worker.join();
}

#endif // THREAD_POOL_H


// 使用线程池的如下代码

// std::vector<std::future<int>> resultVector

//             for (auto &subDocs : results) {
//                 resultVector.emplace_back(m_threadPool->enqueue(std::bind(&BertRankStrategy::BoostRankdocScoreThread, this, std::ref(subDocs), std::ref(processTime)))); // 绑定了类中成员函数方式 bind(&类::成员函数, &类对象, 参数列表)
//             }


// auto nluSearchRet = m_threadPool->enqueue([this, request]() { return nluSearch->Search(request);});


// m_threadPool->enqueue(
//             [this](std::shared_ptr<EsSearchContext> ctx) { return this->ShoppingEsSearch(*(ctx));}, esSearchContext); // 线程池中要执行的任务：f = [](int para){} 传入的参数：para    上面等价于：enqueue(f, para)


//     m_threadPool->enqueue([searchContext]() mutable {
//         delete searchContext;
//         searchContext = nullptr;
//     })


int f(int x, int y) 
{
    return std::pow(x, y);

}

void task_lambda()
{
    std::packaged_task<int(int, int)> task([](int a, int b){ return std::pow(a, b);});
    std::future<int> res = task.get_future();
    task(2, 3);
    // task(2, 5);
    std::cout << "task lambda res: " << res.get() << std::endl;
}

void task_bind()
{
    std::packaged_task<int(int)> task(std::bind(f, std::placeholders::_1, 5));
    std::future<int> res = task.get_future();
    task(2); // 不需要再两个传参数了，因为bind已经固定传了一个5，task只需要传一个参数即可
    std::cout << "task bind res: " << res.get() << std::endl;
}

void task_thread()
{

    std::packaged_task<int(int, int)> task(f);
    std::future<int> res = task.get_future();
    std::thread task_thread(std::move(task), 2, 10);  // 函数对象的右值
    task_thread.join();
    std::cout << "task thread res: " << res.get() << std::endl;
}

 void thread_pool_test() {

     /*
     std::pacakaged_task 使用
    - 构造函数
     Defined in header <future>
        template< class > class packaged_task; //not defined
        template< class R, class ...ArgTypes >
            class packaged_task<R(ArgTypes...)>;
    - 主要应用场景：
        一组相同的callable目标(function, lambda, bind, other function object),放在一起进行asynchronous invoking; 异步返回的结果，可以通过std::future来保存;
     */

     // std::pacakge_task  std::future 

    task_lambda();
    task_bind();
    task_thread();

    

    // 线程池

    ThreadPool pool(4); // 创建了能容纳4个线程的线程池
    std::vector<std::future<int>> results; // 保存异步调用的结果

    for (int i = 0; i < 8; ++i) {
        std::string para = "para";
        results.emplace_back(
            pool.enqueue([i](std::string s){
                std::cout << "hello" << i << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                std::cout << "word" << i <<std::endl;
                std::cout << "para: " << s << std::endl;
                return i*i;
                },para));  // 线程池使用：enqueue(callable, args..)
    }

    for (auto &&res : results) {
        std::cout << res.get() << " ";
    }
    std::cout << std::endl;

 }


