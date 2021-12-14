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


## 圈复杂和优化

### 圈复杂度

1.从函数第一行一致往下通过程序 
2.一旦遇到以下关键字或者同类的词就加1：if、while、repeat、for、and、or 
3.给case语句中的每一种情况加1 

圈复杂度(Cyclomatic Complexity)是一种代码复杂度的衡量标准。它可以用来衡量一个模块判定结构的复杂程度，数量上表现为独立现行路径条数，也可理解为覆盖所有的可能情况最少使用的测试用例数。圈复杂度大说明程序代码的判断逻辑复杂，可能质量低且难于测试和维护。程序的可能错误和高的圈复杂度有着很大关系。

### 常用的优化方法

#### if 中的判断条件简化有助于圈复杂降低

``` c++
if (date.before (SUMMER_START) || date.after(SUMMER_END))
    charge = quantity * _winterRate + _winterServiceCharge;
else 
    charge = quantity * _summerRate;

```
从if、then、else三个段落中分别提炼出独立函数,如下：

```
if (notSummer(date))
    charge = winterCharge(quantity);
else 
    charge = summerCharge (quantity);

```


#### 提炼函数


``` java
void printOwing(double previousAmount)
 {
    Enumeration e = _orders.elements();
    double outstanding = previousAmount * 1.2;
    
      // print banner
    System.out.println ("**************************");
    System.out.println ("***** Customer Owes ******");
    System.out.println ("**************************");

    // calculate outstanding
    while (e.hasMoreElements()) 
    {
        Order each = (Order) e.nextElement();
        outstanding += each.getAmount();
    }

    //print details
    System.out.println ("name:" + _name);
    System.out.println ("amount" + outstanding);
}
```
将这段代码放进一个独立函数中，并让函数名称解释该函数的用途，如下提炼：

``` java
void printOwing(double previousAmount) 
{
    printBanner();
    double outstanding = getOutstanding(previousAmount * 1.2);
    printDetails(outstanding);
}

void printBanner() 
{
    // print banner
    System.out.println ("**************************");
    System.out.println ("***** Customer Owes ******");
}


double getOutstanding(double initialValue) 
{
    double result = initialValue;
    Enumeration e = _orders.elements();
    while (e.hasMoreElements()) 
    {
        Order each = (Order) e.nextElement();
        result += each.getAmount();
    }
    return result;
}

void printDetails (double outstanding)
 {
    System.out.println ("name:" + _name);
    System.out.println ("amount" + outstanding);
}

```



