# 



##


1、如果想要定义Rational类的乘法操作符重载，且要求支持连乘操作，以下实现方法中正确的是（）

```  c++

A.
const Rational& operator*(const Rational& lhs, const Rational& rhs)
{
　　Rational result(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator());
　　return result;  //返回局部变量的地址：返回类型是对象的引用，局部变量释放导致返回引用悬空
}
B.
Rational operator*(const Rational& lhs, const Rational& rhs)
{
　　return Rational(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator());
} // ok   

//性能的讨论：主流的编译器几乎都会在打开了优化选项的情况下对其进行优化，使得返回时不发生对象拷贝。

C.
const Rational& operator*(const Rational& lhs, const Rational& rhs)
{
　　Rational* result = new Rational(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator());
　　return *result; // 返回new创建的对象但未保证释放：返回类型是对象的引用，heap上对象不会悬空；但Rational c = a * b 会导致a*b的临时对象的指针丢失，造成内存泄漏；同时，禁止将局部变量的地址返回到其作用域以外。
}
D.
const Rational& operator*(const Rational& lhs, const Rational& rhs)
{
　　std::shared_ptr result = std::make_shared(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator());
　　return *(result.get()); //误用智能指针: get 返回对象的原始指针，返回类型是引用，管理指针计数器不会增加1，导致函数结束后，指向悬空了。 
　　// 使用智能指针时，应当尽量避免取出原始指针或取出内部保管的对象的引用，同时还要避免使用智能指针类型的引用。只有这样才能充分发挥智能指针自动管理生命周期的作用，减少编码错误. 
　　//同时不能支持连乘的实现
}
```