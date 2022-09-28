
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
}

// 分析上面程序段输出?

```




