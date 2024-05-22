


## c++ mock对象不基于接口来实现

在C++中，虽然基于接口或抽象类来实现Mock对象是最常见和推荐的方式，但确实存在不基于接口创建Mock对象的情况。以下是几种不严格依赖接口来实现Mock对象的方法：

### 1. 继承具体类

如果无法使用接口或抽象类（例如，由于使用的具体类没有定义接口或抽象基类），可以通过继承具体类并覆盖其方法来创建Mock对象。

```cpp
class RealClass {
public:
    void doSomething() {
        // 具体的实现
    }
};

class MockClass : public RealClass {
public:
    MOCK_METHOD(void, doSomething, (), (override));
};
```

在这个例子中，`MockClass`继承自`RealClass`，并使用Mock框架（如Google Mock）来模拟`doSomething`方法。

### 2. 利用虚函数

如果具体类中已有虚函数，可以直接在派生类中覆盖这些虚函数，实现Mock行为。

```cpp
class BaseClass {
public:
    virtual void action() {
        // 默认实现
    }
};

class MockClass : public BaseClass {
public:
    void action() override {
        // Mock实现
    }
};
```

### 3. 使用函数指针或函数对象

可以在类中定义函数指针或函数对象来模拟外部依赖的行为。

```cpp
class SystemUnderTest {
public:
    SystemUnderTest(std::function<int()> dependency) : _dependency(dependency) {}

    int execute() {
        return _dependency();
    }

private:
    std::function<int()> _dependency;
};
```

### 4. 使用全局函数或静态方法

定义一个全局函数或静态方法来模拟依赖的行为，然后在需要测试的代码中调用这个函数或方法。

```cpp
int ExternalDependencyFunction() {
    // 模拟外部依赖的实现
}

class SystemUnderTest {
public:
    int execute() {
        return ExternalDependencyFunction();
    }
};
```

### 5. 服务定位器模式

使用服务定位器模式来查找并注入依赖项，可以在测试时提供Mock版本的依赖。

```cpp
class ServiceLocator {
public:
    static std::unique_ptr<IDependency>& GetDependency() {
        static std::unique_ptr<IDependency> instance = std::make_unique<MockDependency>();
        return instance;
    }
};

class SystemUnderTest {
public:
    void execute() {
        IDependency* dep = ServiceLocator::GetDependency();
        // 使用依赖项
    }
};
```

### 注意事项

- 不基于接口创建Mock对象可能会使测试代码与具体实现耦合更紧密，这可能会降低测试的灵活性和可维护性。
- 继承具体类的方法可能会限制Mock类只能用于测试特定的类。
- 使用函数指针、全局函数或服务定位器模式时，需要确保这些模拟的依赖项在测试执行时能够被正确地设置和访问。

尽管有这些方法可以在不使用接口的情况下创建Mock对象，但基于接口或抽象类的方法仍然是最推荐的方式，因为它提供了最大的灵活性和可维护性。
