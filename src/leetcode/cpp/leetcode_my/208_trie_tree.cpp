/*
 * @lc app=leetcode.cn id=208 lang=cpp
 *
 * [208] 实现 Trie (前缀树)
 *
 * https://leetcode-cn.com/problems/implement-trie-prefix-tree/description/
 *
 * algorithms
 * Medium (66.10%)
 * Likes:    273
 * Dislikes: 0
 * Total Accepted:    33.4K
 * Total Submissions: 50.2K
 * Testcase Example:  '["Trie","insert","search","search","startsWith","insert","search"]\n' +
  '[[],["apple"],["apple"],["app"],["app"],["app"],["app"]]'
 *
 * 实现一个 Trie (前缀树)，包含 insert, search, 和 startsWith 这三个操作。
 * 
 * 示例:
 * 
 * Trie trie = new Trie();
 * 
 * trie.insert("apple");
 * trie.search("apple");   // 返回 true
 * trie.search("app");     // 返回 false
 * trie.startsWith("app"); // 返回 true
 * trie.insert("app");   
 * trie.search("app");     // 返回 true
 * 
 * 说明:
 * 
 * 
 * 你可以假设所有的输入都是由小写字母 a-z 构成的。
 * 保证所有输入均为非空字符串。
 * 
 * 
 */

// @lc code=start

#include <string>
using namespace std;

class Trie {
public:
    /** Initialize your data structure here. */
    Trie() {
        root = new TrieNode();
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        if (word.size() <= 0) return;
        TrieNode *ptr = root;
        //TrieNode *pre_ptr = nullptr;
        for (size_t i = 0; i < word.size(); ++i){
            size_t index = word[i] - 'a';
            if (!ptr->next[index]){
                //TrieNode *tmp = new TrieNode();
                ptr->next[index] = new TrieNode();
            }
            ptr = ptr->next[index];
        }
        ptr ->isString = true;
        return;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        TrieNode *ptr = root;
        if (word.size() <= 0 || !ptr) return false;

        //TrieNode *pre_ptr = nullptr;
        for (size_t i = 0; i < word.size(); ++i){
            size_t index = word[i] - 'a';
            if (!ptr->next[index]){
                return false;
            } else {
                ptr = ptr->next[index];
            }            
        }

        if (!ptr || !ptr->isString) return false;
        return true;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        TrieNode *ptr = root;
        if (prefix.size() <= 0 || !ptr) return false;
        TrieNode *pre_ptr = nullptr;
        for (size_t i = 0; i < prefix.size(); ++i){
            size_t index = prefix[i] - 'a';
            if (!ptr->next[index]){
                return false;
            } else {
                ptr = ptr->next[index];
            }            
        }

        return true;
    }


private:

    struct TrieNode{
        //这个节点上是否形成过完成的字符串? becasuse we have two search method
        bool isString;
        //因为全部字母，总共26个；可以不用map来实现，直接用数组，下标用字母-'a'来映射
        TrieNode* next[26];

        TrieNode():isString(false){
            for (int i = 0; i < 26; ++i){
                next[i] = nullptr;
            }
        }
    };

    TrieNode *root;
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
// @lc code=end

