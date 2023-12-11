void TestBitSet() {

    // bitset 使用
    // 构造
    std::string s1 = "11000";
    std::string s2 = "0010";
    // 定义并初始化
    bitset<4> foo(s1);  // <>中指明了bitset的大小，s1的长度比Size大，取左边4位, 即：1100  
    bitset<4> bar(s2);
    bool b0 = bar[0];
    bool b1 = bar[1];
    bool b2 = bar[2];
    bool b3 = bar[3];
    
    std::cout << b0 << std::endl;
    std::cout << b1 << std::endl;
    std::cout << b2 << std::endl;
    std::cout << b3 << std::endl;
    std::cout << (!bar[0] && bar[1]) << std::endl;

    // 运算： 与，或，异或
    std::cout << "bitset nor: " << (foo ^ bar) << std::endl;
    std::cout << "bitset or : " << (foo | bar) << std::endl;
    std::cout << "bitset and: " << (foo & bar) << std::endl;
    std::cout << "bitset []: " << foo[0] << std::endl;  // 不会检查越界，最右边的元素是0，最左边的元素是size-1

    // 类型转换
    unsigned long ul1 = foo.to_ullong(); // 转成u long
    std::string s3 = foo.to_string(); // 将bitset转成string类型   
    std::cout << "ul: " << ul1  << " string:  " << s3 << std::endl;

}
