 /***************************************************************************
  *
  * Copyright (c) 2018 Baidu.com, Inc. All Rights Reserved
  *
  **************************************************************************/


#include "area2_trie.h"
#include "test_main.h"
#include <iostream>

DistrictTrie::DistrictTrie(){
    m_root = nullptr;
}

DistrictTrie::~DistrictTrie(){

    //按层次遍历的思想，释放每个节点空间
    if (m_root){
        std::queue<TrieNode*> que;
        que.push(m_root);
        while(!que.empty()){
            TrieNode* p = que.front();
            que.pop();
            for (auto it = p->next.begin(); it != p->next.end(); it++){
                if (it->second){
                    que.push(it->second);
                }
            }
            delete p; //直接delete掉树节点
            p = nullptr;
        }
    }//end while
}


int DistrictTrie::Init(){

    if (!m_root){
        m_root = new TrieNode();
    }
    return 0;
}

int DistrictTrie::Insert(const char *str, DistrictInfo* &district_info){

    TrieNode* node = m_root;
    char *p = const_cast<char*>(str);
    uint16_t label = 0;
    while (*p) {
        if (*p < 0) {
            label = *((uint16_t *)p);
            p += 2;//gbk编码一个汉字
        }
        else {
            label = *p++;  //一个字母
        }

        std::map<uint16_t, TrieNode*>::iterator node_iter = node->next.find(label);
        if( node_iter == node->next.end() ){
            TrieNode *tmp = new TrieNode();
            tmp->name = *p;
            tmp->datas.push_back(district_info);
            node->next.insert(std::make_pair(label, tmp));
            node = tmp;
        }
        else{
            node = node_iter->second;
            node->datas.push_back(district_info);
        }
    }
    if (!node->leaf) {
        node->leaf = true;
    }
    return 0;
}


bool DistrictTrie::Search(const char *str,std::vector<DistrictInfo*> &res){

    TrieNode *node = m_root;
    TrieNode *last_match_node = NULL;
    uint16_t label = 0;
    bool success = true;
    char *p = const_cast<char*>(str);
    res.clear();
    while( *p ){
        if (*p < 0) {
            label = *((uint16_t *)p);
            p += 2;
        }else {
            label = *p++;
        }

        std::map<uint16_t, TrieNode*>::iterator node_iter = node->next.find(label);
        if( node_iter == node->next.end() ){
            success = false;
            break;
        }
        last_match_node = node;
        node = node_iter->second;
    }

    if( !success ){
        return false;
    }else{

        res.assign(last_match_node->datas.begin(),last_match_node->datas.end());
        return true;
    }

}

void test_area2_trie(){

    std::string str("北京市");
    std::string str2("上海市");
    std::string str3("北京市海淀区");

    DistrictInfo* ptr = new DistrictInfo(131,2,str);
    DistrictInfo* ptr2 = new DistrictInfo(118,2,str);
    DistrictInfo* ptr3 = new DistrictInfo(132,3,str);


    DistrictTrie trie_test;
    trie_test.Init();
    trie_test.Insert(str.c_str(),ptr);
    trie_test.Insert(str2.c_str(),ptr2);
    trie_test.Insert(str3.c_str(),ptr3);


    std::string ser = "北京";
    std::vector<DistrictInfo*> res;

    if(trie_test.Search(ser.c_str(), res)){

        std::cout << "sucess, size:" << res.size() << std::endl;

        for (auto it = res.begin();it != res.end(); it++){
            std::cout << (*it)->cid << "\t" << (*it)->level << "\t" << (*it)->level_name << std::endl;
        }

    }else{
        std::cout << "search failed!" << std::endl;
    }





}




