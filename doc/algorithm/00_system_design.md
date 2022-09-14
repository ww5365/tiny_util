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

### 磁盘管理系统

设计实现一个磁盘管理系统 DiskSystem，初始化时指定磁盘容量 capacity

add(fileId, fileSize)

存储一个编号为fileId，大小为fileSize的文件
如果剩余空间足够，存储成功，返回存储完成后最大的存储地址的编号
如果剩余空间不够，存储失败，返回 - 1
注：先从小的地址开始存储，不要求地址空间连续
remove(fileId)

删除磁盘中编号为 fileId 的文件
文件存在，释放文件占用的存储空间，返回 1
文件不存在，返回 -1
defrag()

文件碎片整理
将文件编号一样的文件存储在连续的磁盘空间里，并案文件编号从小到大排序
返回磁盘里有多少个文件

```java

// 参考一
import java.util.*;

/**
 * 文件磁盘系统
 *  @method: construct: 初始化磁盘容量
 *  @method: add: 向里面写文件，优先读取磁盘空间编号较小的位置，位置不要求连续，返回文件最后的index，若位置不够返回-1
 *  @method: remove: 删除文件 不存在的话返回-1，否则返回剩余空间大小
 *  @method: defrag: 整理空间
 */
public class DiskSystem {

    // 实际存储空间
    private Integer[] space;
    // 剩余空间大小，性能优化，每次遍历获取剩余大小效率太低
    private int restSpace;

    /**
     * Construct: 初始化磁盘容量
     * @param capacity 磁盘初始容量大小
     */
    public DiskSystem(int capacity) {
        space = new Integer[capacity];
        restSpace = capacity;
    }

    /**
     * 向里面写文件，优先读取磁盘空间编号较小的位置，位置不要求连续，返回文件最后的index，若位置不够返回-1
     * @param fileId 文件id
     * @param fileSize 当前文件大小
     * @return 文件存储的最大编号位置
     */
    public int add(int fileId, int fileSize) {
        if (fileSize > restSpace) {
            return -1;
        }
        for (int i = 0; i < space.length; i++) {
            if (space[i] == null) {
                space[i] = fileId;
                fileSize--;
                restSpace--;
            }
            if (fileSize == 0) {
                return i;
            }
        }
        return -1;
    }

    /**
     * 删除文件 不存在的话返回-1，否则返回剩余空间大小
     * @param fileId 待删除的文件id
     * @return 剩余空间大小:restSpace
     */
    public int remove(int fileId) {
        boolean isExist = false;
        for (int i = 0; i < space.length; i++) {
            if (space[i] != null && space[i]==fileId) {
                space[i] = null;
                isExist = true;
                restSpace++;
            }
        }
        if (!isExist) {
            return -1;
        }

        return restSpace;
    }

    /**
     * 整理空间
     * @return 磁盘空间中文件的个数
     */
    public int defrag() {
        // 构造新空间
        Integer[] newSpace = new Integer[space.length];
        // 数组转list，为了利用List.sort方法
        List<Integer> fileIds = new ArrayList<>();
        for (Integer s : space) {
            if (s != null) {
                fileIds.add(s);
            }
        }
        // 空间整理，重排序
        fileIds.toArray(newSpace);
        fileIds.sort(Integer::compareTo);
        space = newSpace;
        // 用于获取文件数量
        Set<Integer> set = new HashSet<>(fileIds);
        return set.size();
    }
}

```


``` c++  
// 参考2
	public class DiskSystem {
	    private final int size;
	 
	    private PriorityQueue<Integer> storageQueue;
	 
	    private TreeMap<Integer, List<Integer>> fileMap;
	 
	    public DiskSystem(int capacity) {
	        size = capacity;
	        fileMap = new TreeMap<>();
	        storageQueue = new PriorityQueue<>(capacity);
	        for (int i = 0; i < capacity; i++) {
	            storageQueue.offer(i);
	        }
	    }
	 
	    public int add(int fileId, int fileSize) {
	        if (fileSize > storageQueue.size()) {
	            return -1;
	        }
	        List<Integer> ids = new ArrayList<>(fileSize);
	        for (int i = 0; i < fileSize; i++) {
	            Integer id = storageQueue.poll();
	            ids.add(id);
	        }
	        fileMap.put(fileId, ids);
	        return ids.get(fileSize - 1);
	    }
	 
	    public int remove(int fileId) {
	        if (!fileMap.containsKey(fileId)) {
	            return -1;
	        }
	        List<Integer> ids = fileMap.remove(fileId);
	        for (Integer id : ids) {
	            storageQueue.offer(id);
	        }
	        return storageQueue.size();
	    }
	 
	    public int defrag() {
	        storageQueue = new PriorityQueue<>(size);
	        for (int i = 0; i < size; i++) {
	            storageQueue.offer(i);
	        }
	        Set<Integer> records = fileMap.keySet();
	        TreeMap<Integer, List<Integer>> tmpMap = new TreeMap<>();
	        for (Integer fileId : records) {
	            int fileSize = fileMap.get(fileId).size();
	            ArrayList<Integer> ids = new ArrayList<>();
	            for (int i = 0; i < fileSize; i++) {
	                Integer id = storageQueue.poll();
	                ids.add(id);
	            }
	            tmpMap.put(fileId, ids);
	        }
	        fileMap = tmpMap;
	        return records.size();
	    }
	}
```

``` python

class DiskSystem:

    disk = [1001 for _ in range(1000)]
    disk_file = 0

    def __init__(self, capacity: int):

        print ("init %d :" % (capacity))

        DiskSystem.disk = [1001 for _ in range(capacity)]

        DiskSystem.disk_file = 0

        print (DiskSystem.disk)

    def add(self, file_id: int, file_size: int) -> int:

        print ('file_id %d,file_size %d' % (file_id, file_size))

        if DiskSystem.disk.count(1001) < file_size :

            print ('空间不够')

            return -1

        index = 0

        while file_size > 0 :

            index = DiskSystem.disk.index(1001)

            DiskSystem.disk[index] = file_id

            file_size -= 1 

        DiskSystem.disk_file += 1

        return index

 

    def remove(self, file_id: int) -> int:

        print ("remove：%d" % (file_id))

        remove_size = DiskSystem.disk.count(file_id)

        if remove_size == 0 :

            print ("没有：%d" % (file_id))

            return -1

        index = 0

        while remove_size > 0 :

            index = DiskSystem.disk.index(file_id)

            DiskSystem.disk[index] = 1001

            remove_size -= 1

        DiskSystem.disk_file -= 1

        return DiskSystem.disk.count(1001)



    def defrag(self) -> int:

        DiskSystem.disk.sort()

        return DiskSystem.disk_file

```



### 模拟闹钟


闹钟（设置闹钟、删除闹钟、闹钟提醒等功能）





