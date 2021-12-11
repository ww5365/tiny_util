# 图相关经典算法






## Dijkstra算法 - 单源点最短路径算法

### 算法思想

G = <V, E>  S:找到从源点到当前节点最短路径的点集合  U:剩下未待加入节点集合  dist[v]：从源点到节点v的最短路径 visited[v]: 节点v被访问了，或者说已经加入S找到了最短路径
- 初始化：S = {v0}  U = {V - v0}  dist[v0] = 0;
- 计算：从节点v0到其它节点的最短路径的节点u; 本质是排序找最小值的index的过程;
- S = {v0, u} 将u加入S,即：visited[u] = true, 知道dist[u] = MINDIST;
- 更新源点到和节点u关联的节点x,y..的最短路径：dist[x] = min{dist[u] + E(u,x), dist[x]}  //松弛
- 重复从第2步开始的步骤，直到所有节点都在S中。

本质是：贪心算法，每步都选择当前路径最短的点加入到S中。不是遍历思路。

### 算法证明
u->...->x ->..->y->...->v
　　
前提：u到v是最短路径。
假设：x到y不是最短路径，那么存在一条更短的路径从x到y（假设下面有弯箭头从x直接指向y），这样，删去原路径中从x到y的路径，用新找到的路径替代（弯箭头），那么就得到了一条比u到v的权值更短的路径，这与前提u到v是最短路径相矛盾，因而x到y是最短路径，即最短路径满足最优子结构性质。



### 算法伪代码(优先队列)

```c
Dijkstra(G, W, s)　　　　　　//G表示图，W表示权值函数，s表示源顶点
　　d[s] ←0　　　　　　　　　　//源点到源点最短路为0
　　for each v ∈ V - {s}　　//3-8行均为初始化操作
　　　　　do d[v]←∞
　 　　　　  parent[v]←NIL
　　S←∅
　　Q←V　　　　　　　　//此处Q为优先队列，存储未进入S的各顶点以及从源点到这些顶点的估算距离，采用二叉堆（最小堆）实现，越小越优先
　　while Q≠∅
　　 do u←Extract-Min(Q)　　//提取估算距离最小的顶点，在优先队列中位于顶部，出队列，放入集合S中
　　　  S←S∪{u}
　　　　for each v ∈ Adj(u)　　//松弛操作，对与u相邻的每个顶点v，进行维持三角不等式成立的松弛操作。
　　　　　　do if d[v] > d[u] + w(u, v)
　　　　　　　　then d[v] = d[u] + w(u, v)　　//这一步隐含了更新优先队列中的值，DECREASE。
　　　　　　　　　　  parent[v]←u　　　　　　//置v的前驱结点为u
```


### 算法演示

- 初始情况

![img](../img/070223400041868.png)

- 第一次松弛，选择顶点A

  ![img](../img/070226303324937.png)

- 第二次松弛，选择顶点c

  ![img](../img/070228224898033.png)

- 第三次松弛， 选择顶点E

  ![img](../img/070231121295961.png)

  

- 第四次松弛，选择顶点B

  ![img](../img/070232258323145.png)

- 第五次松弛：(最后一个点，完成)

  ![img](../img/070233193799369.png)
  
  经过所有的松弛操作之后，我们就得到了所有顶点的最短路径（表格中红字部分）。如果加上对parent[]进行的操作，还可以得到一棵最短路径树。

### 算法实现

- 通用思路

``` c++
class Solution {
public:
    //实现基于矩阵存储的dijkstra算法: 单源点的最短路径
    bool Dijkstra(vector<vector<int>> &graph, vector<int> &path)
    {

        if (graph.size() <= 0) {
            return false;
        }

        int nodes = graph.size();
        vector<bool> visited(nodes, false);
        visited[0] = true;
        path[0] = 0; 
        
        //初始化，源点0到各个顶点的距离
        for (int i = 1; i < nodes; ++i) {
            path[i] = graph[0][i]; 
        }
    
        int v = -1;
        for (int i = 1; i < nodes; ++i) {
            // 针对剩余所有顶点，逐步加入到S结合
            int minDist = std::numeric_limits<int>::max();
            for (int j = 1; j < nodes; ++j) {
                // 寻找当前集合U中节点的最短路径
                if (path[j] < minDist && !visited[j]) {
                    minDist = path[j];
                    v = j;
                }
            }
            std::cout << "the " << i << " v: " << v << std::endl;
            if (v == -1) break;
            visited[v] = true;
            // 更新，经过节点v, 到各个节点的距离更新
            for (int j = 1; j < nodes; ++j) {
                // 不加第2个条件，会溢出
                if (!visited[j] && graph[v][j] != numeric_limits<int>::max() &&((path[v] + graph[v][j]) < path[j])) {
                    path[j] = path[v] + graph[v][j];
                }
            }
        }
        if (v == -1) {
            std::cout << "graph not connection!" << std::endl;
            return false;
        }
        return true;
    }
};
```


- 堆优化思路



### 算法应用

leetcode
743 网络延迟时间
787 K站中转内最便宜的航班
1334 阈值距离内邻居最少的城市

概率最大的路径





### 参考

0、[图算法 单源最短路径 Dijkstra算法（邻接表/邻接矩阵+优先队列STL)](https://www.cnblogs.com/dzkang2011/p/sp_dijkstra.html)  这篇文章理论，演示，代码都讲解的比较透彻，推荐看
1、[图最短路径算法之迪杰斯特拉算法](https://houbb.github.io/2020/01/23/data-struct-learn-03-graph-dijkstra)
2、[算法 7：Dijkstra 最短路算法](https://wiki.jikexueyuan.com/project/easy-learn-algorithm/dijkstra.html)

3、[leetcode 图的最短路径问题 优先队列实现dijkstra算法](https://www.codeleading.com/article/80502848318/)

4、[LeetCode-概率最大的路径-题解](https://juejin.cn/post/7026249509663424525)





