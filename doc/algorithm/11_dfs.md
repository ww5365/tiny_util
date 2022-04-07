# DFS

## DFS 介绍

深度优先搜索算法（英语：Depth-First-Search，DFS）是一种用于遍历或搜索树或图的算法。这个算法会尽可能深的搜索树的分支。深度优先搜索是图论中的经典算法，利用深度优先搜索算法可以产生目标图的拓扑排序表，利用拓扑排序表可以方便的解决很多相关的图论问题，如无权最长路径问题等等。DFS基于递归思想，DFS实质就是一种枚举，不过借助递归实现；
回溯搜索是深度优先搜索（DFS）的一种。对于某一个搜索树来说（搜索树是起记录路径和状态判断的作用），回溯和DFS，其主要的区别是，回溯法在求解过程中不保留完整的树结构，而深度优先搜索则记下完整的搜索树。回溯就是通过不同的尝试来生成问题的解，有点类似于穷举，但是和穷举不同的是回溯会“剪枝”。为了减少存储空间，在深度优先搜索中，用标志的方法记录访问过的状态，这种处理方法使得深度优先搜索法与回溯法没什么区别了。




## 算法模板



``` C++

// 数据结构为矩阵时，进行DFS的模板 

vector<int> direction = {-1,0,1,0,-1};
void dfs(const vector<vector>& matrix,vector<vector>& can_reach,int row,int col)
{
        //如果为true
        if(can_reach[row][col])
        {
                return;
        }
        can_reach[row][col]=true;
        int x,y;
        //遍历上下左右节点
        for(int i=0;i<4;++i)
        {
            x=row+direction[i],y=col+direction[i+1];
            if(x>=0 && y<matrix.size() && matrix[r][c] <=matrix[x][y])
            {
                dfs(matrix,can_reach,x,y);
            }
        }
}


```





































