# DFS

## DFS 介绍

深度优先搜索算法（英语：Depth-First-Search，DFS）是一种用于遍历或搜索树或图的算法。这个算法会尽可能深的搜索树的分支。深度优先搜索是图论中的经典算法，利用深度优先搜索算法可以产生目标图的拓扑排序表，利用拓扑排序表可以方便的解决很多相关的图论问题，如无权最长路径问题等等。DFS基于递归思想，DFS实质就是一种枚举，不过借助递归实现；
回溯搜索是深度优先搜索（DFS）的一种。对于某一个搜索树来说（搜索树是起记录路径和状态判断的作用），回溯和DFS，其主要的区别是，回溯法在求解过程中不保留完整的树结构，而深度优先搜索则记下完整的搜索树。回溯就是通过不同的尝试来生成问题的解，有点类似于穷举，但是和穷举不同的是回溯会“剪枝”。为了减少存储空间，在深度优先搜索中，用标志的方法记录访问过的状态，这种处理方法使得深度优先搜索法与回溯法没什么区别了。


补充参考：src\leetcode\cpp\chapater_nine\basic_5_dfs.cpp



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

```
模板2：

vector<vector<int>> res;

vector<vector<int>> subsets(vector<int>& nums) {
    // 记录走过的路径
    vector<int> track;
    backtrack(nums, 0, track);
    return res;
}

void backtrack(vector<int>& nums, int start, vector<int>& track) {
    res.push_back(track);
    // 注意 i 从 start 开始递增
    for (int i = start; i < nums.size(); i++) {
        // 做选择
        track.push_back(nums[i]);
        // 回溯
        backtrack(nums, i + 1, track);
        // 撤销选择
        track.pop_back();
    }
}

```


## 题目


* 570 · 寻找丢失的数 II
给一个由 1 - n 的整数随机排列组成的一个字符串序列，其中丢失了一个整数，请找到它。

输入: n = 6 和 s = 56412
输出: 3
解释:
5'6'4'1'2

参考：https://www.lintcode.com/problem/570



* 其它题目
  回溯？
LeetCode	力扣	难度
1.   Combination Sum III	216. 组合总和 III	🟠
2.  Combination Sum	39. 组合总和	🟠
3.  Combination Sum II	40. 组合总和 II	🟠
4.  Permutations	46. 全排列	🟠
5.  Permutations II	47. 全排列 II	🟠
6.  Combinations	77. 组合	🟠
7.  Subsets	78. 子集	🟠
8.  Subsets II	90. 子集 II	🟠
-	剑指 Offer II 079. 所有子集	🟠
-	剑指 Offer II 080. 含有 k 个元素的组合	🟠
-	剑指 Offer II 081. 允许重复选择元素的组合	🟠
-	剑指 Offer II 082. 含有重复元素集合的组合	🟠
-	剑指 Offer II 083. 没有重复元素集合的全排列	🟠
-	剑指 Offer II 084. 含有重复元素集合的全排列	🟠

































