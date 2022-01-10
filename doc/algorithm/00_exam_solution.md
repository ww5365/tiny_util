## problem 1

### 描述
有一个二叉树状的计算图，叶子节点表示数字（下图的橙色节点），非叶子节点表示运算符号：`+、-、*、/`（下图的蓝色节点），蓝色节点运算完了后用运行结果（数字）代替原来的运算符号（相当于蓝色变橙色）。完成整个计算过程需要从叶子节点一路运算到根节点。

![图](../img/9d6e85b20a03aea1ff2585322a4be228_511x419.jpg@900-0-90-f.jpg)

并行运算：比如上图 第三层的左边第一个蓝色节点和第四层的蓝色节点是可以并行计算的。

现在有一个n核的CPU，每个CPU时钟周期可以进行n个运算操作，问完成整颗树的运算**最少需要多少个周期**？

```
题目提示：层次遍历可以借助队列构建二叉树
```

### 思路


第一步处理输入，根据层次遍历构建出二叉树。

第二步，解题。

分析1：运算过程一定是下层节点优先于上层节点。因为假如是一颗不平衡的二叉树，右子树比左子树高很多，如果先运行完了左子树的蓝色节点，根节点还是需要等待右子树的运行。所以要使用层次遍历。

分析2：非叶子节点在哪个CPU周期运行，有两个影响因素：

左右子树所在的运行周期最大的那个+1 和 CPU该周期核的使用情况

第一个因素使用 递归 + 回溯 。第二个因素使用一个 数组记录每个CPU周期核的使用 情况，当根据第一个因素求出的周期里CPU核数使用满了的话，就线性往后寻找第一个有空闲的周期。

综合：先建树，然后使用递归的方式进行层次遍历，每层进入一次递归，递归的深度就是树的高度。再回溯，根据左右子树所在的运算周期以及CPU目前的运行情况，计算出非叶子节点所在的CPU运算周期





## problem 2

### 2.1 题目描述
一个编解码系统采用一种编解码策略，一个数字后面跟相应数目个字符，比如118computer1a,可以拆成11 +“ 8computer1a”，也可以拆成1+“1”+8+“computer”+1+“a”，这种情况称为歧义。

给一个字符串，如果按编码策略只有一种解码方式即无歧义则返回去掉数字后的长度，否则返回-1。

### 解题思路

2.2 解题思路
这道题第一眼的想法，肯定需要回溯去拿到所有的可能解，如果有唯一解，去掉数字后的长度就是答案，如果没有解或者多个解则返回-1；

分析题目可以想到，没有必要每次逐个的扫描字符串中的每个字符。可以生成一个字符串中数字所在位置及值的索引数组，索引数组的长度就是字符串的长度。

1、查看当前位置是否是字符串结束位置，若是字符串结束位置，则将数字列表添加到可能解列表中，若不是，进入步骤2

2、从起始位置第一个数字开始，拿到数字对应的值，往后跳，跳到下一个位置，同时将当前数字维护进数字列表中，进入下一次回溯，回溯结束后进入步骤3

3、判断当前位置下一个位置是不是也是数字，如果是，则与当前位置数字拼成一个更大的数字，并计算下次起始位置，重新进入步骤1

回溯结束后，就拿到了所有的可能解，唯一解返回去掉数字后的字符串长度，无解或者多解返回-1即可

2.3 题解
public class Solution {
    public int getLength(String encodedString) {
        int length = encodedString.length();
        // 维护单个数字位置及值的索引数组
        Character[] digits = new Character[length];
        for (int i = 0; i < length; i++) {
            if (Character.isDigit(encodedString.charAt(i))) {
                digits[i] = encodedString.charAt(i);
            }
        }
        // 单个解的数字列表
        List<String> codes = new ArrayList<>();
        // 所有可能解的列表
        List<List<String>> allResults = new ArrayList<>();
        // 回溯遍历
        checkBack(0, length, digits, codes, allResults);

        // 查看解列表数量，构造返回值
        if (allResults.size() == 1) {
            // 唯一解返回去除数字列表中数字后的字符串长度
            int countCodesLength = 0;
            codes = allResults.get(0);
            for (String code : codes) {
                countCodesLength += code.length();
            }
            return length - countCodesLength;
        } else {
            // 多个解或无解返回-1
            return -1;
        }
    }
    
    public void checkBack(int begin, int sourceLength, Character[] digits, List<String> codes,
        List<List<String>> allResults) {
        // 到达字符串末尾，说明是解，加入解列表中
        if (begin == sourceLength) {
            allResults.add(new ArrayList<>(codes));
        }
        //未到达字符串末尾，继续判断
        if (begin < sourceLength && digits[begin] != null) {
            //temp维护当前位置起连续数字的位置索引
            int temp = begin;
            String tempNumStr = "";
            while (digits[temp] != null) {
                //拼接数字字符串，比如第一个位置是“1”，第二个位置是"1",拼接为11
                tempNumStr += digits[temp];
                //进入下一次检查前，将数字加入数字列表
                codes.add(tempNumStr);
                //进入下一次检查要跳跃的步数
                int jump = Integer.parseInt(tempNumStr);
                checkBack(temp + jump + 1, sourceLength, digits, codes, allResults);
                //上一个可能数字检查完毕，连续数字位置索引后移一位，移除上次的数字，进入下一次回溯
                temp++;
                codes.remove(codes.size() - 1);
            }
        }
    }
}
可能不太好理解，手笨，不会画动图，可以debug一把看看codes和allResults列表的内容，帮助理解。以“118computer1a”为例，程序回溯得到的解为

Connected to the target VM, address: '127.0.0.1:49218', transport: 'socket'
回溯共得到解 2 个
回溯共得到解 [[1, 8, 1], [11]]
最终结果为：-1
Disconnected from the target VM, address: '127.0.0.1:49218', transport: 'socket'
2.4 思考及优化：
这种方法应该不是最优解，因为虽然回溯到了所有解。以“118computer1a118computer1a”为例，得到的解为

Connected to the target VM, address: '127.0.0.1:49178', transport: 'socket'
回溯共得到解 4 个
回溯共得到解 [[1, 8, 1, 1, 8, 1], [1, 8, 1, 11], [11, 1, 8, 1], [11, 11]]
最终结果为：-1
Disconnected from the target VM, address: '127.0.0.1:49178', transport: 'socket'
但是实际题目并不需要所有解，当判断到解列表中有多个解就可以结束回溯了，修改如下。

public class Solution {
    public int getLength(String encodedString) {
        int length = encodedString.length();
        // 维护单个数字位置及值的索引数组
        Character[] digits = new Character[length];
        for (int i = 0; i < length; i++) {
            if (Character.isDigit(encodedString.charAt(i))) {
                digits[i] = encodedString.charAt(i);
            }
        }
        // 单个解的数字列表
        List<String> codes = new ArrayList<>();
        // 所有可能解的列表
        List<List<String>> allResults = new ArrayList<>();
        // 回溯遍历
        checkBack(0, length, digits, codes, allResults);

        // 查看解列表数量，构造返回值
        if (allResults.size() == 1) {
            // 唯一解返回去除数字列表中数字后的字符串长度
            int countCodesLength = 0;
            codes = allResults.get(0);
            for (String code : codes) {
                countCodesLength += code.length();
            }
            return length - countCodesLength;
        } else {
            // 多个解或无解返回-1
            return -1;
        }
    }
    
    public void checkBack(int begin, int sourceLength, Character[] digits, List<String> codes,
        List<List<String>> allResults) {
        // 到达字符串末尾，说明是解，加入解列表中
        if (begin == sourceLength) {
            allResults.add(new ArrayList<>(codes));
            // 检查到多个解的时候，结束回溯。
            if (allResults.size() > 1) {
                return;
            }
        }
        // 未到达字符串末尾，继续判断
        if (begin < sourceLength && digits[begin] != null) {
            // temp维护当前位置起连续数字的位置索引
            int temp = begin;
            String tempNumStr = "";
            while (digits[temp] != null) {
                // 拼接数字字符串，比如第一个位置是“1”，第二个位置是"1",拼接为11
                tempNumStr += digits[temp];
                // 进入下一次检查前，将数字加入数字列表
                codes.add(tempNumStr);
                // 进入下一次检查要跳跃的步数
                int jump = Integer.parseInt(tempNumStr);
                checkBack(temp + jump + 1, sourceLength, digits, codes, allResults);
                // 检查到多个解的时候，结束回溯。
                if (allResults.size() > 1) {
                    return;
                }
                // 上一个可能数字检查完毕，连续数字位置索引后移一位，移除上次的数字，进入下一次回溯
                temp++;
                codes.remove(codes.size() - 1);
            }
        }
    }
}
以“118computer1a118computer1a”为例，运行之后得到的解及最终输出结果为

Connected to the target VM, address: '127.0.0.1:65459', transport: 'socket'
回溯共得到解 2 个
回溯共得到解 [[1, 8, 1, 1, 8, 1], [1, 8, 1, 11]]
最终结果为：-1
Disconnected from the target VM, address: '127.0.0.1:65459', transport: 'socket'


## problem 3


1、商品折购
给定一个商品价格列表，下标代表商品，值代表商品的单价。
如： price[6] = {10,5,8,8,6,3}; // 商品 0 单价10， 商品1 单价5

给定折扣规则列表及折扣值:
```
pro[][] = {
         {0， 7}，
         {4， 10}，
         {2, 6，1,  9}，
         {5，2}
};
dis[] = {4, 3, 5, 1};
上面共有4个折扣规则，1.  0号商品买7个，可以减4元，2. 4号商品买10个可以减3元。 3.  2号商品买6个 && 1号商品买9个可以减5元
```

顾客需要买的商品列表:
```
order[] = {2,17,3,10,1,27,5,2,4,9}；
```
问： 按最大折扣后，用户最终需要支付多少？

```c++

	#include <vector>
	#include <unordered_map>
	#include <cassert>
	#include <iostream>
	 
	using namespace std;
	 
	class Solution {
	public:
	    bool canDis(vector<int> &pro, unordered_map<int, int> &orders) {
	        for (int j = 1; j < pro.size(); j += 2) {
	            if (pro[j] > orders[pro[j - 1]]) {
	                return false;
	            }
	        }
	        return true;
	    }
	 
	    void dfs(int idx, vector<vector<int>> &pro, vector<int> &dis, unordered_map<int, int> &orders, int &maxDisc,
	             int curDis) {
	        if (maxDisc < curDis) {
	            maxDisc = curDis;
	        }
	 
	        if (idx >= pro.size()) {
	            return;
	        }
	 
	        for (int i = idx; i < pro.size(); ++i) {
	            if (canDis(pro[i], orders)) {
	                for (int j = 0; j < pro[i].size(); ++j) {
	                    int num = pro[i][j];
	                    int cnt = pro[i][++j];
	                    orders[num] -= cnt;
	                }
	                dfs(i + 1, pro, dis, orders, maxDisc, curDis + dis[i]);
	                for (int j = 0; j < pro[i].size(); ++j) {
	                    int num = pro[i][j];
	                    int cnt = pro[i][++j];
	                    orders[num] += cnt;
	                }
	            }
	        }
	    }
	 
	    int solve(vector<int> &price, vector<vector<int>> &pro, vector<int> &dis, vector<int> &order) {
	        int res = 0;
	        unordered_map<int, int> orders;
	        for (int i = 0; i < order.size(); i += 2) {
	            res += price[order[i]] * order[i + 1];
	            orders.insert({order[i], order[i + 1]});
	        }
	 
	        int maxDisc = 0;
	        dfs(0, pro, dis, orders, maxDisc, 0);
	 
	        return res - maxDisc;
	    }
	};
	 
	int main() {
	    vector<int> price = {10, 5, 8, 8, 6, 3};
	    vector<vector<int>> pro = {
	            {0, 7},
	            {4, 10},
	            {2, 6, 1, 9},
	            {5, 2}
	    };
	    vector<int> dis = {4, 3, 5, 1};
	    vector<int> order = {2, 17, 3, 10, 1, 27, 5, 2, 4, 9};
	 
	    Solution solution;
	    int res = solution.solve(price, pro, dis, order);
	    cout << res << endl;
	    assert(res == 405);
	}

```



