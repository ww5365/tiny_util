# heap



## 一、堆的实现

c++ 中使用优先级队列可以模拟实现堆的功能

``` c++
/*
*  priorrity_queue 队列使用
* 需求：有5个同学随意入队；他们都有成绩和姓名；请按照成绩从低到高出队列，如果成绩相等，按照名字字母逆顺序出队；

*  模拟大小顶堆的实现
*  priority_queue <类名, 底层容器, 比较类>  
*  头文件: #include <queue>
*  第三个参数：比较类重载()运算，实现仿函数功能，类似本例；
              也可以通过重载类本身operator<运算符，进行比较实现
              left < right: 大顶堆  出队时：元素从大到小
              left > right: 小顶堆  出队是： 元素从小到大  greator<T>
              默认：less<T>
*  push   emplace ： 入队
*  pop ：出队
*  top: 队头元素
*  参考：https://en.cppreference.com/w/cpp/container/priority_queue
*/
void stl_use::priority_queue_use(){
    //下面是使用优先级队列的常见形式；deque中数据是按照分数从小到大排序
    // std::priority_queue<Student,std::deque<Student>,CompareClass> qu_test;
    std::priority_queue<Student,std::deque<Student>> qu_test;

    //  void sort (RandomAccessIterator first, RandomAccessIterator last, Compare comp) 最后一个参数是比较对象
    //  sort(it1, it2, CompareClass()); //最后是一个对象

    Student s1("wang",60);
    Student s2("wei",60);
    Student s3("song",54);
    Student s4("ni",76);
    Student s5("havy",80);

    qu_test.push(s1);
    qu_test.push(s2);
    qu_test.push(s3);
    qu_test.push(s4);
    qu_test.push(s5);

    std::cout << "priority que1 score \t name " <<std::endl;

    while(!qu_test.empty()){
        std::cout << qu_test.top().get_score() << "\t"
                <<qu_test.top().get_name() <<std::endl;

        qu_test.pop();
    }

    priority_queue<int, deque<int>, greater<int>> que2; //默认是less<int> 类: 大顶堆  而： greater<int> 是小顶堆，从小到大
    que2.push(8);
    que2.push(4);
    que2.push(5);
    que2.push(9);
    while (!que2.empty()){
        std::cout << "priority que2: " << que2.top() << std::endl;//小顶堆，队头最小;默认大顶堆，队头最大；
        que2.pop();
    }
}

// 另外两个类
class Student{
private:
    std::string name;
    short score;
public:
    Student():name(""),score(0){}
    Student(std::string name,short score):name(name),score(score){}
    short get_score() const{
        return score;
    }
    std::string get_name() const{
        return name;
    }

    // 内部重载运算符号<
    bool operator<(const Student &s) const
    {
        if (score == s.get_score()) {
            return name < s.get_name();
        }
        return score > s.get_score(); //score的小顶堆
    }
};

// 重写仿函数: 比较类，重载()运算符号
class CompareClass{
public:
    bool operator() (const Student &lf,const Student &rg) const {
        if (lf.get_score() == rg.get_score()){
            return lf.get_name() < rg.get_name(); //大顶堆：x1 < x2 < x3(队头) 从大到小出队; 实际是满足的偏序关系，return true时，rg是需要在队头
        }
        return lf.get_score() > rg.get_score();// 小顶堆： x1 > x2 > x3(队头)  队头是最小的元素，出队顺序从小到大
    }
};

```

## 堆排序

1、辅助理解：
less<T>  x3 < x2 < x1  建立的是大顶堆，输出从大到小的元素
greater<T>  x3 > x2 > x1  建立的是小顶堆，输出从小到大的元素

2、堆排序：关键是堆调 和  建堆 两个过程

```c++
void heap_adjust(int vec[], int start, int end)
{
//start和end之间的元素，除了首位，其它都满足大顶堆的定义；将vec[start:end]调整成大顶堆
if (start >= end) {
	return;
}

while (start < end) {
    int idx = 2 * start;
    if (idx > end) break;
	if (idx <= end && idx + 1 <= end && vec[idx] < vec[idx + 1]){
		idx += 1;
	}
	if (vec[start] >= vec[idx]) break;
	//栈顶元素小于其中一个子元素
	swap(vec, start, idx);
	start = idx;
	}
} 

/*
* 进行堆排序：
* start：从1开始进行堆排序
*  
*/
bool heap_sort(int vec[], int start, int end)
{

	if((end - start) < 1) return true;
	
	//从mid位置开始到1结束，进行堆调整
	int mid = end/2;
	for (int i = end/2; i >= start; --i) {
		heap_adjust(vec, i, end);
	}
	
	//输出排序结果
	for(int i = end; i > start; --i){
		swap(vec, i, start);
		heap_adjust(vec, start, i-1);
	}
	
	return true;
}

```

