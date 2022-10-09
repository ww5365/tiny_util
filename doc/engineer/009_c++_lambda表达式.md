
# c++ lambda表达式





``` c++

void ShowLambda()
{
    int var = 5;
    static int base = 3;
    auto func = [=]() mutable {
        ++base;
        ++var;
        // cout<< var <<" "<< base << endl;
        return base + var;
    };
    auto ret1 = func();
    auto ret2 = func(); // 第二次调用，直接原lambda函数继续执行
    cout<< ret1 <<" "<< ret2 <<" "<< var <<" "<< base << endl; // 10 12 5 5

    /*
    * 多思考集中场景：
    1 . 去掉mutable  编译报错  readonly base var
    2. static int base 变成  int base ，输出：10 12 5 3
    3. [&]() 输出变成： 10 12 7 5
    */
}

// 分析上面程序段输出?

```




