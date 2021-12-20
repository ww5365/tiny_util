
/*
 * 
 * 
 * 
 */

#include "01_all.h"
#include <stack>
#include <vector>
#include <map>
#include <iostream>


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
    int idx;
    int leftSize;
    std::vector<bool> flag;
    std::map<int, std::vector<int>> mFile2Block;
};




void TestExam0()
{
    // Solution s;

    std::cout <<"this is test exam 0 " << std::endl;


}
