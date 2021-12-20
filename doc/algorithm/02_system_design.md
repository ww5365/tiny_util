# 系统设计

## 系统设计题目


### 设计推特

设计一个简化版的推特(Twitter)，可以让用户实现发送推文，关注/取消关注其他用户，能够看见关注人（包括自己）的最近 10 条推文。

实现 Twitter 类：

- Twitter() 初始化简易版推特对象
- void postTweet(int userId, int tweetId) 根据给定的 tweetId 和 userId 创建一条新推文。每次调用此函数都会使用一个不同的 tweetId 。
- List<Integer> getNewsFeed(int userId) 检索当前用户新闻推送中最近  10 条推文的 ID 。新闻推送中的每一项都必须是由用户关注的人或者是用户自己发布的推文。推文必须按照时间顺序由最近到最远排序 。
- void follow(int followerId, int followeeId) ID 为 followerId 的用户开始关注 ID 为 followeeId 的用户。
- void unfollow(int followerId, int followeeId) ID 为 followerId 的用户不再关注 ID 为 followeeId 的用户。


设计关键点：

1、生成全局唯一的tweetId？
2、按照时间进行排序，时间怎么表示？时间戳？


``` c++

class Twitter {
public:
    Twitter() {

    }
    
    void postTweet(int userId, int tweetId) {

    }
    
    vector<int> getNewsFeed(int userId) {

    }
    
    void follow(int followerId, int followeeId) {

    }
    
    void unfollow(int followerId, int followeeId) {

    }
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */



```







