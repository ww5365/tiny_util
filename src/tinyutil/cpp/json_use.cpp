#include "../inc/com_use.h"
#include "nlohmann/json.hpp"
#include <string>
#include <iostream>
#include <unordered_map>

using Json = nlohmann::json;

// 空串
#define EMPTY_JSON R"({})"_json
// 空数组
#define EMPTY_JSON_ARRAY nlohmann::json::array()
// null json串
#define NULL_JSON nlohmann::json()

// 将json串转成map
std::unordered_map<std::string, std::string> jsonToUnorderedMap(const Json &j)
{
    std::unordered_map<std::string, std::string> result;

    // 确保传入的是一个对象
    if (j.is_object()) {
        for (Json::const_iterator it = j.begin(); it != j.end(); ++it) {
            const std::string key = it.key();  // 直接转成string了
            const Json &value = it.value(); // value还可能是Json

            // 检查值是否为字符串类型
            if (value.is_string()) {
                result[key] = value.get<std::string>();
            } else {
                // 如果值不是字符串，可以选择转换为字符串或跳过
                result[key] = value.dump(); // 使用dump()将JSON值转换为字符串
            }
        }
    }

    return result;
}

void json_test()
{
    // 怎么安装nlohmann json解析库？ 直接下载,在cmake中include_directories 包含头文件就可以使用了;参考cmakelist.txt;

    std::string str = R"(test)"; // R"()"  raw string 括号里面的是表示字符串的内容
    std::cout << "test json : " << str << std::endl;

    // literal 方式定义json串
    nlohmann::json json1 = "{ \"happy\": true, \"pi\": 3.141 }"_json;
    nlohmann::json json2 = R"(
          {
            "happy": true,
            "pi": 3.141
          }
    )"_json;

    std::cout << "json1: " << json1.dump() << std::endl;
    std::cout << "json2: " << json2.dump() << std::endl;

    // explicitly 方式
    nlohmann::json json3 = nlohmann::json::parse(R"({"happy": true, "pi": 3.141})");
    std::cout << "json3: " << json3.dump() << std::endl;

    // 获取反序列后的结果
    nlohmann::json json4 = "this is a test";
    std::cout << "json4: " << json4.dump() << std::endl; // dump是反序列化后的结果

    // 获取json中的original string
    std::string str1 = json4.get<std::string>();
    std::cout << "json -> original string: " << str1 << std::endl;
    std::string str2;
    json4.get_to(str2); // 已经定义了变量str2
    std::cout << "json -> original string2: " << str2 << std::endl;

    // 获取json串中的数据值
    nlohmann::json json5 = nlohmann::json::parse(R"({"happy": true, "pi": ["3.141","23"]})");
    std::cout << "json5 str: " << json5.dump() << std::endl;
    const nlohmann::json &pi_arr = json5.value("pi", EMPTY_JSON_ARRAY);
    std::cout << "json5 pi arr: " << pi_arr.dump() << std::endl;

    // array类型处理
    if (pi_arr.is_array()) {
        for (const nlohmann::json &elem : pi_arr) {
            std::string tmp;
            if (elem.is_string()) {
                elem.get_to<std::string>(tmp);
                std::cout << "pi arr type: " << tmp << std::endl;
            }
        }
    }

    // 通过key获取value值
    if (!json5.is_null() && json5.contains("happy")) {
        bool tmp2 = json5["happy"].get<bool>();
        std::cout << "happy bool type: " << tmp2 << std::endl;
    }

    auto pi_arr2 = json5["pi"]; // 获取 pi 对应的 JSON 数组
    std::cout << "=== json pi value ===" << std::endl;
    for (const auto &val : pi_arr2) {
        std::cout << val << std::endl; // "3.141"
    }

    std::cout << "=== json pi value 22 ===" << std::endl;
    if (json5.contains("pi")) {
        std::vector<std::string> piVal = json5["pi"].get<std::vector<std::string>>();
        for (const auto &val : piVal) {
            std::cout << val << std::endl; // 3.141  和上面的pi_arr2有区别
        }
    }

    std::unordered_map<std::string, std::string> testResult = jsonToUnorderedMap(json5);

    for (const auto &elem : testResult) {
      std::cout << "elem: " << elem.first << " : " << elem.second << std::endl;
      // elem: pi : ["3.141","23"]
      // elem: happy : true
    } 
}
