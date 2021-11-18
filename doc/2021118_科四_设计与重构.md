# 科目4  软件设计与重构





solid
正交四原则






#### 卫语句


卫语句定义：
如果条件语句极其复杂，就应该将条件语句拆解开，然后逐个检查，并在条件为真时立刻从函数中返回，这样的单独检查通常被称之为“卫语句”(Guard Clauses)。

说人话就是：写方法时在合适的时候尽快return，少用else

按卫语句对函数进行重构应遵循：

* 及时return，if中能return就return。(一旦满足条件return后你根本无需关注后面的代码)
* 能够return的就尽量少使用else。(用else太多，读者需要维护大量的栈在大脑中)
* 减少嵌套，一般嵌套超过4层读者就会产生阅读恐惧感。


``` c++
//没有使用未语句
double GetPayAmount()
{
    double result;
    if (IsDead())
    {
        result = DeadAmount();
    }
    else
    {
        if (IsSeparated())
        {
            result = SeparatedAmount();
        }
        else
        {
            if (IsRetired())
            {
                result = RetiredPayAmount();
            }
            else
            {
                result = NormalPayAmount();
            }
        }
    }

    return result;
}
```

``` c++
//使用卫语句
double getPayAmount()
{
    if (isDead())
    {
        return deadPayAmount();
    }
    if (isSeparated())
    {
        return separatedPayAmount();
    }
    if (isRetired())
    {
        return retiredPayAmount();
    }

    return normalPayAmount();
}
```
