/* 
* future和promise的作用是在不同线程之间传递数据
* https://www.cnblogs.com/guxuanqing/p/11360572.html
* https://www.limerence2017.com/2023/09/17/concpp07/
*/

// 方法1
#include <iostream>
#include <functional>
#include <future>
#include <thread>
#include <chrono>
#include <cstdlib>

void thread_set_promise(std::promise<int>& promiseObj) {
    std::cout << "In a thread, making data...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    promiseObj.set_value(45);
    std::cout << "SetPromise Finished\n";
}

int main() {
    std::promise<int> promiseObj;
    std::future<int> futureObj = promiseObj.get_future();
    std::thread t(&thread_set_promise, std::ref(promiseObj));
    std::cout << futureObj.get() << std::endl;
    t.join();

    system("pause");
    return 0;
}


// 方法2

// future example
#include <iostream>       // std::cout
#include <future>         // std::async, std::future
#include <chrono>         // std::chrono::milliseconds

// a non-optimized way of checking for prime numbers:
bool is_prime (int x) {
  for (int i=2; i<x; ++i) if (x%i==0) return false;
  return true;
}

int main ()
{
  // call function asynchronously:
  std::future<bool> fut = std::async (is_prime,444444443);

  // do something while waiting for function to set future:
  std::cout << "checking, please wait";
//  std::chrono::milliseconds span (100);
//  while (fut.wait_for(span)==std::future_status::timeout)
//    std::cout << '.' << std::flush;

  bool x = fut.get();     // retrieve return value

  std::cout << "\n444444443 " << (x?"is":"is not") << " prime.\n";

  return 0;
}




