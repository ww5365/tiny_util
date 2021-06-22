/*
 * basic_4_bfs.cpp
 *
 *  Created on: Sep 16, 2019
 *      Author: wangwei69
 */
#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <set>

using namespace std;

/*
 * 图如何存储？
 * 邻接表
 *
 * 有向图：
 * 输入:n*2纬的数组或有序对： (1,2) : 1->2  节点1指向节点2
 *
 */

struct DirectGraphNode{
   int label;
   std::vector<DirectGraphNode*> neighbors;
   DirectGraphNode(int x): label(x){}
};

/*
 * 输入：有序对 （0->1）,（1->2）,(3,2)
 * 输出：邻接表存储
 *
 * 存储方式的理解：
 * 1、每个DirectedGraphNode * 能标识一个从入度为0的节点开始的有向连通图；
 * 2、因为有向图可能有多个入度为0的点,所以使用vector来存多个起点；
 *
 *
 */

 //v1:这种实现方式，有问题。。
void create_graph(vector<pair<int,int>> matrix, vector<DirectGraphNode>& graph){

    if (matrix.size() <= 0) return;
    cout << "matrix: " << matrix.size() << endl;
    //先创建图节点
    for(auto e: matrix){
        DirectGraphNode node(e.first); //ulgy 想法
        //node.label = e.first;
        cout << "graph insert1111: " << e.first << endl;
        vector<DirectGraphNode>::iterator it = graph.begin();
        it += e.first;
        graph.insert(it, node); // vector是空的情况下，能向位置2插入元素吗？ ulgy
        cout << "graph insert: " << e.first << endl;
    }

    cout << "graph size: " << graph.size() << endl;
    //添加图的边 先点后边，原因？ 邻接点的地址，需要先定下来。。
    for(auto e : matrix){
        int label = e.first;
        DirectGraphNode *ptr = &graph[e.second]; // 获取vector中某个元素的地址，ugly ugly
        graph[label].neighbors.push_back(ptr);
    }
}

/*
 * v2:
 * 功能：通过有序对来创建一个图
 * 返回：图的邻接链表
 */

vector<DirectGraphNode*> create_graph(vector<pair<int, int>> &matrix){

    vector<DirectGraphNode*> result;
    unordered_map<int, DirectGraphNode*> node_map; //记录每个节点所在的内存地址
    unordered_map<int, int> node_indegree; //记录每个节点的入度

    if (matrix.size() <= 0){
        return result;
    }

    //cout << "begin to parse matrix size: " << matrix.size()<<endl;
    for (auto e :  matrix){
        //对于每个有序对，创建新的图节点

        //有序对第1个元素
        if (node_map.find(e.first) == node_map.end()){
            DirectGraphNode *node = new DirectGraphNode(e.first);
            node_map[e.first] = node;
            node_indegree[e.first] = 0;
            //cout << "begin to parse matrix first new node: " << node->label << endl;
        }
        //有序对第二个元素
        auto it = node_map.find(e.second);
        if (it == node_map.end()){
            DirectGraphNode *nb_node = new DirectGraphNode(e.second);
            node_map[e.second] = nb_node;
            node_indegree[e.second] = 1;
            node_map[e.first]->neighbors.push_back(nb_node);
        }else{
            node_map[e.first]->neighbors.push_back(it->second);
            node_indegree[e.second] += 1;
        }
    }

   //入度为0的节点，认为是图中起始节点

//    for (auto it = node_indegree.begin(); it != node_indegree.end(); ++it){
//
//        if (it->second == 0){
//            result.push_back(node_map[it->first]);
//
//        }
//        cout << "the start node: " << it->first << endl;
//    }

    //以邻接表的方式返回图的所有顶点
    for (auto it = node_map.begin(); it != node_map.end(); ++it){
        result.push_back(it->second);
    }
    return result;
}

struct hash_fun{

    template<class T1, class T2>
    size_t operator()(std::pair<T1, T2> const &val)const{
        size_t h1 = std::hash<T1>()(val.first); //hash<T1>() 定义一个临时对象
        size_t h2 = std::hash<T2>()(val.second); //hash<T1>() 定义一个临时对象

        return h1 ^ h2;
    }

};

//遍历图中每个顶点
void travsel_graph(vector<DirectGraphNode*> &graph){

    if (graph.size() <= 0) return;

    queue<DirectGraphNode*> qu;
    //注意使用unordered_set存储pair，需要提供hash函数(可调用对象)
    //unordered_set<pair<int, int>, hash_fun> visit_set;
    std::set<pair<int, int>> visit_set;
    int vetex_cnt = 0;

    for (int i = 0; i< graph.size(); ++i){
        qu.push(graph[i]);
        cout << "test111111111111 :  " << graph[i]->label << endl;
        while(!qu.empty()){
            //出队访问这个顶点及所有临接点
            DirectGraphNode* node = qu.front();
            qu.pop();
            ++vetex_cnt;
            for (auto elem : node->neighbors){
                pair<int, int> edge(node->label, elem->label);
                if (visit_set.find(edge) == visit_set.end()){
                    cout << "edge: " << node->label << " -> " << elem->label << endl;
                    visit_set.insert(edge); //访问过的边，不再次访问
                }
                if (vetex_cnt <= graph.size())
                    qu.push(elem);
            }
        }//end while
    } //end for
}

/*
 * 拓扑排序：
 * 输入：graph 邻接链表存储的图
 * 返回：result 一中拓扑排序方式
 *
 *
 */

bool top_sort(const vector<DirectGraphNode*> &graph, vector<DirectGraphNode*> &result){

    if (graph.size() <= 0) return false;

    //计算图中每个节点的入度
    unordered_map<DirectGraphNode*, int> node_indegree;
    for (auto node : graph){
        if (node_indegree.count(node) == 0){
            node_indegree[node] = 0;
        }
        for (auto nb_node : node->neighbors){
            if (node_indegree.count(nb_node) == 0){
                node_indegree[nb_node] = 1;
            }else{
                node_indegree[nb_node] += 1;
            }
        }
    }

    //初始：入度为0的顶点，入队
    queue<DirectGraphNode*> qu;
    for (auto it = node_indegree.begin(); it != node_indegree.end(); ++it){
        if (it->second == 0){
            qu.push(it->first);
        }
    }

    cout << "the size of 0 indegree: " << qu.size() << endl;

    //按照BFS思想，选择入度为0的顶点，进入到拓扑序列
    while (!qu.empty()){
        DirectGraphNode* vetex = qu.front();
        qu.pop();
        result.push_back(vetex);
        for (auto nb_vetex : vetex->neighbors){
            if (node_indegree.count(nb_vetex) != 0){
                node_indegree[nb_vetex] -= 1;  //起点输出后，邻接点入度减1
                if (node_indegree[nb_vetex] == 0){
                    qu.push(nb_vetex);
                }
            }
        }//end for
    }//end while

    return result.size() == graph.size();    //如果存在环，不存在topsort序列
}

/*
 * 矩阵： BFS
 *
 *
 */


void test_base_4_bfs(){

    //创建一个图: 0->1 0->2 1->2 4->1
    std::pair<int, int> node0(0, 1);
    std::pair<int, int> node1(1, 4);
    std::pair<int, int> node2(4, 0);
    std::pair<int, int> node3(0, 2);
    std::pair<int, int> node4(2, 3);



    vector<std::pair<int, int>> matrix;
    matrix.reserve(4);
    matrix.push_back(node0);
    matrix.push_back(node1);
    matrix.push_back(node2);
    matrix.push_back(node3);
    matrix.push_back(node4);


    vector<DirectGraphNode*> graph;

    cout << "create graph size: " << graph.size() << endl;
    //创建一个有向图
    graph = create_graph(matrix);
    cout << "create graph size: " << graph.size() << endl;
    //遍历有向图
    travsel_graph(graph);


    //拓扑排序
    vector<DirectGraphNode*> top_result; //一种拓扑排序的方式
    bool is_exist = top_sort(graph, top_result);

    if (is_exist){
        cout << "top result size: " << top_result.size() << endl;
        cout << "top sort sequece: " << endl;
        for (auto vetex : top_result){

            cout << vetex->label << " ";
        }

        cout << endl;
    }else{
        cout << "exist loop subgraph" << endl;
    }


}


