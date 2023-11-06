#include "01_all.h"

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <list>
using namespace std;

/* 

LFU: https://www.lintcode.com/problem/24/

LFU是一个著名的缓存逐出算法。
对于容量为k的缓存，如果缓存已满，并且需要逐出其中的密钥，则最少使用的密钥将被踢出。
实现LFU中的set 和 get

思路：
1. 使用双hash的思路实现：
   cache
   hash 

2. cache替换：
1)优先替换频次使用少的节点
2)对于使用频次相同的，最近被使用的不被替换，最久被使用的替换

*/

struct Node {
    int key;
    int value;
    int freq;   // 缓存节点中记录该节点被使用的频次
    Node(int k = 0, int v = 0, int f = 0): key(k), value(v), freq(f){}
    ~Node(){}
};

class LFUCache {
private:
    int _capacity;
    unordered_map<int, list<Node>> cache;  // 缓存节点，不仅仅是list管理，结合访问频次进行分类管理
    unordered_map<int, list<Node>::iterator> hash;
    int _minfreq;
public:
    /*
    * @param capacity: An integer
    */
    LFUCache(int capacity) {
        // do intialization if necessary
        _capacity = capacity;
        _minfreq = 0;
    }

    /*
     * @param key: An integer
     * @param value: An integer
     * @return: nothing
     */
    void set(int key, int value) {
        // write your code herea

        auto it = hash.find(key);
        if (it == hash.end()) {
            // 原来缓存中没有的
            if (hash.size() >= _capacity) {
                // 要淘汰旧的
                auto iter = cache.find(_minfreq);
                int k = iter->second.back().key;
                int val = iter->second.back().value;
                int freq = iter->second.back().freq;
                iter->second.pop_back(); // 淘汰使用最少且最久的node
                if (hash.find(k) != hash.end()) {
                    hash.erase(k);
                }
            }
            //开始放入最新的节点
            _minfreq = 1;
            if (cache.find(_minfreq) == cache.end()) {
                cache[_minfreq] = list<Node>();
            }
            cache[_minfreq].push_front(Node(key, value, 1));
            hash[key] = cache[_minfreq].begin();
        } else {
            // 原来内存中已经有节点了,主要是重置value
            int k = it->second->key;
            int val = it->second->value;
            int freq = it->second->freq;
        
            // 在原来分类上删除节点node
            cache[freq].erase(it->second);
            if (cache[freq].empty()) {
                cache.erase(freq);
                if (_minfreq == freq) {
                    _minfreq = freq + 1;
                }
            }

            // 新建节点并写入到
            if (cache.find(freq + 1) == cache.end()) {
                cache[freq + 1] = list<Node>();
            }
            cache[freq + 1].push_front(Node(k, value, freq + 1));  // 用最新的value来更新缓存
            hash[k] = cache[freq + 1].begin();
        }

        return;

    }

    /*
     * @param key: An integer
     * @return: An integer
     */
    int get(int key) {
        // write your code here

        auto iter = hash.find(key);
        if (iter == hash.end()) {
            return -1; // 未命中，返回-1
        }

        int k = iter->second->key;
        int val = iter->second->value;
        int freq = iter->second->freq;
        
        // 在原来分类上删除节点node
        cache[freq].erase(iter->second);
        if (cache[freq].empty()) {
            cache.erase(freq);
            if (_minfreq == freq) {
                _minfreq = freq + 1;
            }
        }

        // 新建节点并写入到
        if (cache.find(freq + 1) == cache.end()) {
            cache[freq + 1] = list<Node>();
        }
        cache[freq + 1].push_front(Node(k, val, freq + 1));
        hash[k] = cache[freq + 1].begin();
        return val;        
    }
};

void TestLFUCache()
{
    std::cout << "----begin to TestLRUCache ---" << std::endl;
    std::cout << "----finished TestLRUCache ---" << std::endl;
}
