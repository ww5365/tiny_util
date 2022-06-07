/*
 * 18_lru_cache.cpp
 *
 *  Created on: Jun 26, 2018
 *      Author: wangwei69
 */

#include "test_main.h"
#include <map>
#include <unordered_map>
#include <list>
#include <iostream>

/*
 *算法思路：
 * 1、map 存储： key -> (key, value，iterator)   也就是把 value 存储在 map中
 * 2、list 存储：key 来标识哪些 key 还在 cache 中，同时标明它访问的顺序
 */

template<typename K, typename V>
class LRU{

    //可以使用模板类中类型，来定义新的数据类型；要开眼；
    using key_tractor_type = std::list<K>;
    using key_to_value_type = std::map<K, std::pair<V, typename key_tractor_type::iterator>>;

private:

    size_t _capcity; //cache容量
    key_to_value_type _key_value_map;
    key_tractor_type _key_tractor_list;

public:

    LRU() : _capcity(100){
        //默认构造函数
    }
    LRU(size_t cap) : _capcity(cap){

    }

    ~LRU(){
        //析构方式，合适吗？
        if (!_key_value_map.empty())
            _key_value_map.clear();
        if (!_key_tractor_list.empty())
            _key_tractor_list.clear();
    }


    /*
     * 获取cache中key对应的value；
     * 命中：  更新tactor,把最新被访问的节点放在list的头部；返回true；
     * 不命中： 返回false；
     */

    bool get(K key, V &val){

        typename key_to_value_type::iterator it = _key_value_map.find(key);

        if (it != _key_value_map.end()){
            val = it->second.first;
            _key_tractor_list.splice(_key_tractor_list.begin(), _key_tractor_list, it->second.second);
            return true;
        }
        return false;
    }

    /*
     * cache中添加数据；
     * 超过capcity的情况下，需要删除cache块；腾出空间来；
     */

    bool set(const K &key, const V &val){

        auto it = _key_value_map.find(key);

        if (it != _key_value_map.end()){//已经存在key
            it->second.first = val;//更新val值
            _key_tractor_list.splice(_key_tractor_list.begin(), _key_tractor_list, (it->second).second);//更新链表
            return true;
        }else{
            if (_key_value_map.size() >= _capcity){
                K del_key = _key_tractor_list.back();
                _key_value_map.erase(del_key);
                _key_tractor_list.pop_back();//删除最后一个元素

                std::cout << "need del key!" <<std::endl;
            }
            //插入头部list，插入元素到map

           typename key_tractor_type::iterator it_new =
                     _key_tractor_list.insert(_key_tractor_list.begin(), key);//list的插入操作

           _key_value_map.insert(std::make_pair(key, std::make_pair(val, it_new)));//map(元素都是pair)插入操作

           return true;
        }
    }

    /*
     * 获取cache块的key链的首尾迭代器(地址)；
     */

    bool get_key_list(typename key_tractor_type::iterator &head,
                      typename key_tractor_type::iterator &end)
    {
        if (!_key_tractor_list.empty()){
            head = _key_tractor_list.begin();
            end = _key_tractor_list.end();
            return true;
        }
        return false;
    }

};

/*
 * v2：版本
 *
 * 1、 map： 使用 hashmap 来存储(key, iterator) ; list：使用 list 来存储(key,value)
 *    为什么都要存key？ list更新(cash块淘汰)时，通过 key 同步更新 hashmap
 *
 *
 */

class LRU2{

private:

    struct LNode{
        int key;
        int value;
        LNode(int k, int v):key(k), value(v){};
    };

private:
    int capcity ;
    int size;
    std::unordered_map<int, std::list<LNode>::iterator> hash;
    std::list<LNode> cache;

public:

    LRU2(int cap = 3):capcity(cap), size(0){

    }

    /*
     * hash存在key： 直接通过iterator获取到 list 中的 value；同时要更新最近访问的 list 队列；
    * hash 不存在 key： 返回 -1；
    */

    int get(int key){
        auto it = hash.find(key);
        if (it == hash.end())
            return -1;
        std::list<LNode>::iterator list_it = it -> second;
        cache.splice(cache.begin(), cache, list_it); //更新 cache 将当前访问的点，剪切到链表头部

        return list_it->value;
    }

    /*
     * set(key, value)
     *
     * 存在 key 的情况： 刷新 value 的值，同时将值节点放到 cache 的头部
     *
     * 不存在 key 的情况： 如果 cache 的 capcity 足够，将最新的 cache 节点插入到头部且size+1，同时更新 hash 映射；
     *                   如果 cache 的 capcity 不够，需要淘汰 cache 的尾部节点，最新节点插入到头部，同时更新 hash 映射中；
     *
     */
    void set(int key, int value){
        auto it = hash.find(key);
        if (it != hash.end()){
            std::list<LNode>::iterator list_it;
            list_it = it -> second;
            list_it -> value = value; //更新 value
            cache.splice(cache.begin(), cache, list_it); //将最新节点插入到头部
        }else{//不在 cache 中
            if (size >= capcity){
                //需要进行淘汰
                int del_key = cache.back().key; //list尾部元素:back(), 头部元素：front(); 头指针：begin() 尾部之后迭代器：end()
                cache.pop_back(); //list head or tail pop: pop_back() / pop_front();
                hash.erase(del_key); //map delete key
                size --;

            }else{
                //直接将 capcity+1 这样写有bug啊， 这个size变动，搞死我了；
                // ++ size;
            }
            auto insert_itor = cache.insert(cache.begin(), LNode(key, value));
            size ++;
            hash.insert(std::make_pair(key, insert_itor));
        }
    }

    /*
     * 打印 cache 块中 key 和 value 内容
     */

    void print_cache(){
        for (auto e : cache){
            std::cout << "key:value " << e.key << " : " << e.value << std::endl;
        }
    }

};

void lru_cache_test(){

    LRU<std::string, uint32_t> lru(3); //cache的容量为3

    lru.set("wang", 10);
    lru.set("wei", 11);
    lru.set("ni", 12);
    lru.set("hao", 13);

    uint32_t val;
    if (lru.get("wei", val)){
        std::cout << "get the key wei val:" << val << std::endl;
    }else{
        std::cout << "not get the key wei val:" << std::endl;
    }

    if (lru.get("wang", val)){
        std::cout << "get the key wang val:" << val << std::endl;
    }else{
        std::cout << "not get the key wang val:" << std::endl;
    }

    std::list<std::string>::iterator key_head;
    std::list<std::string>::iterator key_end;
    if (lru.get_key_list(key_head, key_end)){
        for (;key_head != key_end; key_head ++){
            std::cout << "key:  " << *(key_head) << std::endl;
        }
    }

    //version 2
    LRU2 lru2(3);
    lru2.set(1, 10);
    lru2.set(2, 20);
    lru2.set(3, 30);
    lru2.set(4, 40);
    
    std::cout << "get lru cache22222-----------: " << std::endl;

    int value = lru2.get(2);
    std::cout << "get lru cache: " << value << std::endl;
    value = lru2.get(1);
    std::cout << "get lru cache: " << value << std::endl;
    lru2.print_cache();

    //version 3



}

