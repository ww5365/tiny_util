#include "01_all.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>

#include <unordered_map>

#include <list>
#include <unordered_set>


using namespace std;

/*

355. 设计推特 : https://leetcode.cn/problems/design-twitter/
设计一个简化版的推特(Twitter)，可以让用户实现发送推文，关注/取消关注其他用户，能够看见关注人（包括自己）的最近 10 条推文。

实现 Twitter 类：

* Twitter() 初始化简易版推特对象
* void postTweet(int userId, int tweetId) 根据给定的 tweetId 和 userId 创建一条新推文。每次调用此函数都会使用一个不同的 tweetId 。
* List<Integer> getNewsFeed(int userId) 检索当前用户新闻推送中最近  10 条推文的 ID 。新闻推送中的每一项都必须是由用户关注的人或者是用户自己发布的推文。推文必须 按照时间顺序由最近到最远排序 。
* void follow(int followerId, int followeeId) ID 为 followerId 的用户开始关注 ID 为 followeeId 的用户。
* void unfollow(int followerId, int followeeId) ID 为 followerId 的用户不再关注 ID 为 followeeId 的用户。


思路：

1. 设计两个数结构，来承载用户的关注信息和用户发表的内容信息
   
   用户关注列表 :  unordered_map<int, set<int>>   userid : 被关注userids
   用户发表内容信息： unordered_map<int, list<Content>>  : 通过头插方法，保持按照时间从近及远; 用list代替了单链表

   Tweet  {
       tweetId,
       timeStamp //发表tweet时的时间戳，用来全局化按照时间顺序进行排序
   };

2.  整体难点：
    getNewsFeed时，自身和被关注用户，最多10条推文，按照时间顺序进行倒叙排序设计；
    多个人的top10的推文合并；
     

*/


struct Tweet {
    int tweetId;
    int timestamp;
    Tweet(int twId = 0, int ts = 0): tweetId(twId), timestamp(ts){}
};


class Twitter {
public:
    Twitter() {
        timestamp = 0;
    }
    
    void postTweet(int userId, int tweetId) {
        Tweet *tw = new Tweet(tweetId, ++timestamp);  // 每次生成新的递增的时间戳
        tweets[userId].push_front(tw);
    }
    
    vector<int> getNewsFeed(int userId) {

        // 取自己及关注的人的tweet，按照时间进行归并

        using TweetIter = list<Tweet*>::iterator;

        auto cmp = [](list<Tweet*>::iterator &left, list<Tweet*>::iterator &right){
            return ((*left)->timestamp < (*right)->timestamp);  //  小顶堆
        };
        priority_queue<TweetIter, vector<TweetIter>, decltype(cmp)> qu(cmp);
        const int N = 10;
        int count = 0;
        // 自己的推特内容
        for(auto iter = tweets[userId].begin(); iter != tweets[userId].end() && count < N; ++iter, ++count) {
            qu.push(iter);
        }
        
        // 关注者的推特内容
        for(const int &followeeid:followIds[userId]) {
            count = 0;
            for(auto iter = tweets[followeeid].begin(); iter != tweets[followeeid].end() && count < N; ++iter, ++count) {
            qu.push(iter);
            }
        }

        vector<int> result;
        count = 0;
        while(!qu.empty() && count < N) {
            auto it = qu.top();
            qu.pop();
            result.push_back((*it)-> tweetId);
            ++count;
        }
        return result;
    }
    
    void follow(int followerId, int followeeId) {
        followIds[followerId].insert(followeeId);
    }
    
    void unfollow(int followerId, int followeeId) {
        followIds[followerId].erase(followeeId);
    }

private:

    unordered_map<int, unordered_set<int>> followIds;
    unordered_map<int, list<Tweet*>> tweets;
    int timestamp;
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */

void TestTwitter()
{
    cout << "-----------TestTwitter----------------" << endl;
}

