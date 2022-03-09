#include "01_all.h"

#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>
#include <map>
#include <queue>
using namespace std;


/*

打印目录结构

opt/test
opt/test/file1
opt/test/file2
root
mnt/test

打印结果：按照字母排序；下一级目录或文件，使用两个空格进行缩进；

mnt
  test
opt
  test
    file1
    file2
root


核心思路： 多叉树  +  dfs 搜索

1、 文件的目录结构，使用多叉树的数据结构进行存储
2、 打印： 多叉树的遍历，使用dfs
3、 字符串的处理，按照某个字符进行分割

*/


// 注意结点，构建完多叉树后，需要释放内存，避免内存泄漏
struct TreeNode {
    string key;
    map<string, TreeNode *> next;
    TreeNode(string k) : key(k){}
    virtual ~TreeNode(){}
};

// 这种方式，不需要手动释放内存
struct TreeNode2 {
    string key;
    map<string, TreeNode> next;
};

class Solution {

public:
// 构建多叉树的文件目录结构
void BuildTree(const vector<string> &paths) {

    if (paths.empty()) {
        return;
    }
    root = new TreeNode("/");
    for (const string &path : paths) {
        vector<string> splitPath = Split(path, "/");
        TreeNode *tmp = root;
        for (const string &elem : splitPath) {
            map<string, TreeNode*>::iterator it = tmp->next.find(elem);
            if (it == tmp->next.end()) {
                tmp->next[elem] = new TreeNode(elem);
                tmp = tmp->next[elem];
            } else {
                tmp = it -> second;
            }
        }
    } //end for

    return;
}

// dfs的方式打印目录文件结构
void PrintTree(const vector<string> &paths) {
    
    BuildTree(paths);
    if (!root) 
        return;
    Dfs(root,0);
    
    return;
}

// 释放内存

virtual ~Solution() {

    // 层次遍历
    if (root) {
        queue<TreeNode*> qu;
        qu.push(root);
        
        while (!qu.empty()) {
            TreeNode *tmp = qu.front();
            qu.pop();
            for (const auto &elem : tmp->next) {
                qu.push(elem.second);
            }
            cout << "delete one node key:" << tmp->key << endl;
            delete tmp;
        }
    }
}

private:

// 深度遍历多叉树
void Dfs(TreeNode *node, int depth) {
    if (node->next.empty()) {
        return;
    }
    for (const auto &node : node->next) {
        for (int i = 0; i < depth; ++i) {
            cout << "  ";
        }
        cout << node.first << endl;
        Dfs(node.second, depth + 1);
    }
    return;
}

// 将字符串str按照某种分隔符进行分割, 结果存放在vector中
// eg ：opt/test -> {opt, test}
vector<string> Split(string str, string delimiter) {
    vector<string> result;
    if (str.empty() || delimiter.length() < 1) {
        return result;
    }
    size_t idx = 0;
    size_t next = 0;
    for (idx = 0; (next = str.find(delimiter, idx)) != string::npos; idx  = next + 1){
        result.push_back(str.substr(idx, next - idx));
    }
    if (idx < str.size()) {
        result.push_back(str.substr(idx));
    }
    return result;
}

private:

    TreeNode *root = nullptr;

};

void TestPrintDirectories() {

    string str = "opt/test/";
    // string str = "/";

    vector<string> paths = { "opt/test",
                             "opt/test/file1" ,
                             "opt/test/file2",
                             "root",
                             "mnt/test"
                            };
    Solution s;

    cout << "----------------------test print directories---------------" << endl;
    
    // vector<string> res = s.Split(str, "/");
    // cout << "result size: " << res.size() << endl;
    // copy(res.begin(), res.end(), std::ostream_iterator<string>(std::cout, " "));
    // cout << endl;

    s.PrintTree(paths);
    
    cout << "----------------------test print directories finished---------------" << endl;



}