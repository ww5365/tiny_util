
/*
 * 系统设计题目：

* 设计实现一个磁盘管理系统 DiskSystem，初始化时指定磁盘容量 capacity
* 
* add(fileId, fileSize)
* 存储一个编号为fileId，大小为fileSize的文件
* 如果剩余空间足够，存储成功，返回存储完成后最大的存储地址的编号
* 如果剩余空间不够，存储失败，返回 - 1
* 注：先从小的地址开始存储，不要求地址空间连续
* 
* remove(fileId)
* 删除磁盘中编号为 fileId 的文件
* 文件存在，释放文件占用的存储空间，返回 1
* 文件不存在，返回 -1
* 
* defrag()
* 文件碎片整理
* 将文件编号一样的文件存储在连续的磁盘空间里，并案文件编号从小到大排序
* 返回磁盘里有多少个文件
 * 
 * 
 */

#include "01_all.h"
#include <stack>
#include <vector>
#include <map>
#include <queue>
#include <iostream>


// 初步思路, 有问题
class DiskSystem {

public:
    explicit DiskSystem(int capacity)
    {
        this->capacity = capacity;
        leftSize = capacity;
        idx = 0;
        flag.resize(capacity, false);
    }
    ~ DiskSystem()
    {
        flag.clear();
    }
    int Add(int fileId, int fileSize)
    {
        if (leftSize < fileSize) {
            return -1;
        }
        auto it = mFile2Block.find(fileId);
        if (it == mFile2Block.end()) {
            mFile2Block[fileId] = std::vector<int>();
        }
        int count = 0;
        int res = 0;
        for (int i = 0; i < capacity && count < fileSize; ++i) {
            if (!flag[i]) {
                flag[i] = true;
                leftSize --;
                count ++;
                mFile2Block[fileId].push_back(i);
                res = i;
            }
        }
        return res;
    }
    int Remove(int fileId)
    {
        auto it = mFile2Block.find(fileId);
        if (it == mFile2Block.end()) {
            return -1;
        }

        // 删除文件fileId
        for (const int &elem : it->second) {
            leftSize ++;
            flag[elem] = false;
        }
        mFile2Block.erase(it);
        return leftSize;
    }
    int Defrag()
    {
        int res = 0;
        if (mFile2Block.size() <= 0) {
            return res;
        }
        std::vector<bool> tmp(this->capacity, false);
        int idx = 0;
        for (auto &elem : mFile2Block) {
            int fileNo = elem.first;
            int fileSize = elem.second.size();
            res += fileSize;
            int i = idx;
            for (;i < fileSize; ++i) {
                tmp[i] = true;
                elem.second[i] = i;
            }
            idx = i;
        }
        this->flag.swap(tmp);
        return res;
    }
private:
    int capacity;
    int idx; //记录最小的空闲编号，这个没有设计好。很难管理!!!
    int leftSize;
    std::vector<bool> flag; //已经占用的磁盘号的标识
    std::map<int, std::vector<int>> mFile2Block; //记录文件占用的磁盘号; 有序
};


// 借鉴别人的思路
class DiskSystem2{
public:
    explicit DiskSystem2(int capacity):cap(capacity),file2Block()
    {
        for (int i = 0; i < capacity; ++i) {
            qu.push(i); //小顶堆入队
        }
    }

    int Add(int fileId, int fileSize)
    {
        if (qu.size() < fileSize) {
            return -1;
        }
        // 空闲最小编号磁盘出队
        for (int i = 0; i < fileSize; ++i) {
            int freeBlock = qu.top();
            qu.pop();
            auto it = file2Block.find(fileId);
            if (it == file2Block.end()) {
                file2Block[fileId] = std::vector<int>();
            }
            file2Block[fileId].push_back(freeBlock);
        }
        return file2Block[fileId].back();
    }

    int Remove(int fileId)
    {
        auto it = file2Block.find(fileId);
        if (it == file2Block.end()) {
            return -1; //文件不存在
        }
        //文件存在
        for (const int & elem : it->second) {
            qu.push(elem); // 释放占用的磁盘块
        }
        file2Block.erase(it);
        return qu.size();
    }

    int Defrag()
    {   
        if (file2Block.size() == 0) {
            return 0;
        }
        std::map<int, std::vector<int>> tmpFile2Block;
        for (int i = 0; i < cap; ++i) {
            qu.push(i);
        }
        for (auto &elem : file2Block) {
            for (int block : elem.second) {
                int freeBlock = qu.top();
                qu.pop();
                tmpFile2Block[elem.first].push_back(freeBlock);
            }
        }
        file2Block.clear();
        std::swap(file2Block, tmpFile2Block);
        return file2Block.size();
    }
private:

    std::priority_queue<int, std::vector<int>, std::greater<int>> qu; 
    //因为每次分配空间时，都从最小编号分配; 使用优先级队列保存空闲磁盘块,小顶堆,完美解决了空闲块的管理问题
    std::map<int, std::vector<int>> file2Block; //每个文件占用的磁盘块编号, key 有序存放
    int cap;
};


void TestExam0()
{
    // Solution s;

    std::cout <<"this is test exam 0 " << std::endl;


}
