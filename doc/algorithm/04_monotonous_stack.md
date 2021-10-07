## 1 单调栈介绍

（https://zhuanlan.zhihu.com/p/26465701）

单调栈是一种理解起来很容易，但是运用起来并不那么简单的数据结构。一句话解释单调栈，就是一个堆栈，里面的元素的大小按照他们所在栈内的位置，满足一定的单调性，说直白点，就是递增存储元素或者递减存储元素，当该单调性（递增性或者递减性）被打破时要进行适当出栈，这是该算法的关键。那么到底什么时候用这个单调栈，怎么用单调栈呢。下面我们来看几个例子。

### 1.1  开胃菜-谷歌面试题

先来分享一道非常简单的谷歌面试题目：

给一个数组，返回一个大小相同的数组。返回的数组的第i个位置的值应当是，对于原数组中的第i个元素，至少往右走多少步，才能遇到一个比自己大的元素（如果之后没有比自己大的元素，或者已经是最后一个元素，则在返回数组的对应位置放上-1）。

示例：
输入: 5, 3, 1, 2, 4
输出: -1  3  1  1  -1

解释: 对于第0个数字5，之后没有比它更大的数字，因此是-1，对于第1个数字3，需要走3步才能达到4（第一个比3大的元素），对于第2和第3个数字，都只需要走1步，就可以遇到比自己大的元素。对于最后一个数字4，因为之后没有更多的元素，所以是-1。

暴力做的结果就是O(n^2)的时间复杂度，例如对于一个单调递减的数组，每次都要走到数组的末尾。

``` java
//java暴力计算法    
public    int[] nextExceed(int[] input) {
    int[] result    = new int[input.length];
    Arrays.fill(result, -1);       
    for (int i = 0; i < input.length; i++) {         
        int anchor =    input[i];         
        for (int j = i + 1; j < input.length; j++) {           
            if (input[j]    > anchor) {             
                result[i] = j - i;           
             }         
        }       
     }       
    return result;     
}        
```

用单调栈怎么做呢？先来看代码：


``` java
//单调栈示例：  单调递减的栈
public static int[] nextExceed(int[] input) {
   int[] result = new int[input.length];
   Arrays.fill(result, -1);
   Deque<Integer> stack = new ArrayDeque<>(input.length);
   for (int i = 0; i < input.length; i++) {
     while (!stack.isEmpty() && input[i] > input[stack.peek()]) {
       int top = stack.pop();
       result[top] = i - top;
     }
     stack.push(i);
   }
   return result;
 }
```



```java
//示例：[5,3,1,2,4]

// step1. 第0个数值5栈空入栈 栈顶：索引0，数值：5
// step2. 第1个数值3比栈顶数值5小入栈 栈顶：索引1,数值：3
// step3. 第2个数值1比栈顶数值3小入栈 栈顶：索引2，数值：1
// step4. loop:
//      第3个数值2比栈顶数值1大，先计算后入栈；
//      计算索引2数值=result[2]=3-2=1，出栈删除索引2；
//     入栈；栈顶：索引3,数值：2
// step5. loop:
//      第4个数值4比栈顶数值2大，计算索引3数值=result[3]=4-3 = 1；
//         出栈删除索引3，栈顶：索引1，数值3。
//      第4个数值4比栈顶索引[1]=3大，计算索引1数值=result[1] = 4 - 1 =3
//         出栈删除索引1，栈顶：索引0，数值5。
//     入栈；栈顶：索引4, 数值：4
// step6. 堆栈剩余元素2个，游标i超出for循环边界，循环结束
```


我们维护这样一个单调递减的stack，stack内部存的是原数组的每个index。每当我们遇到一个比当前栈顶所对应的数（就是input[monoStack.top()]）大的数的时候，我们就遇到了一个“大数”。这个“大数”比它之前多少个数大我们不知道，但是至少比当前栈顶所对应的数大。我们弹出栈内所有对应数比这个数小的栈内元素，并更新它在返回数组中对应位置的值。因为这个栈本身的单调性，当我们栈顶元素所对应的数比这个元素大的时候，我们可以保证，栈内所有元素都比这个元素大。对于每一个元素，当它出栈的时候，说明它遇到了自己的next greater element，我们也就要更新return数组中的对应位置的值。如果一个元素一直不曾出栈，那么说明不存在next greater element，我们也就不用更新return数组了。

在这个例子中，对于每一个元素都只有一次入栈和出栈的操作，因此时间复杂度只有O(n)。

解决了这个开胃菜，我们来看一道稍微复杂一点的题目。

 

### 1.2 单调栈的性质

1.单调栈里的元素具有单调性，栈中元素只能是单调递增或者单调递减

2.元素加入栈前，会在栈顶端把破坏栈单调性的元素都删除；

3.使用单调栈可以找到元素向左遍历第一个比它小的元素，也可以找到元素向左遍历第一个比它大的元素。 

（原文链接：https://blog.csdn.net/liujian20150808/article/details/50752861）

 

单调栈分为单调递增栈和单调递减栈

* 单调递增栈即栈内元素保持单调递增的栈

* 同理单调递减栈即栈内元素保持单调递减的栈

操作规则（下面都以单调递增栈为例）

* 如果新的元素比栈顶元素大，就入栈

* 如果新的元素较小，那就一直把栈内元素弹出来，直到栈顶比新元素小

加入这样一个规则之后，会有什么效果

*  栈内的元素是递增的

*  **当元素出栈时，说明这个新元素是出栈元素向后找第一个比其小的元素**

*  **当元素出栈后，说明新栈顶元素是出栈元素向前找第一个比其小的元素**

 最后再总结一下单调栈。单调栈这种数据结构，通常应用在一维数组上。如果遇到的问题，和前后元素之间的大小关系有关系的话，（例如第一题中我们要找比某个元素大的元素，第二个题目中，前后的bar的高低影响了最终矩形的计算），我们可以试图用单调栈来解决。在思考如何使用单调栈的时候，可以回忆一下这两题的解题套路，然后想清楚，如果使用单调栈，每个元素出栈时候的意义。最后的时间复杂度，因为每个元素都出栈入栈各一次，所以是线性时间的复杂度。

 

## 2 代表题目

### 2.1 [柱状图中最大的矩形](https://leetcode-cn.com/problems/largest-rectangle-in-histogram/)([#84](https://leetcode-cn.com/problems/largest-rectangle-in-histogram/))

![image-20211007154226981](../img/image-20211007154226981.png)

方法一、暴力求解法
首先，我们可以想到，两个柱子间矩形的高由它们之间最矮的柱子决定。如下图所示：

![image-04-2](../img/04_2.png)


因此，我们可以考虑所有两两柱子之间形成的矩形面积，该矩形的高为它们之间最矮柱子的高度，宽为它们之间的距离，这样可以找到所要求的最大面积的矩形。代码参考如下：

 ```java
 //暴力求解：超时，94 / 96 个通过测试用例
 public    int largestRectangleArea(int[]    heights) {       
     if(heights.length == 0) {         
         return 0;       
     }       
     int maxArea =    Integer.*MIN_VALUE*;       
     for(int i = 0; i < heights.length; i++) {         
         for(int j = i; j < heights.length; j++) {           
             int minHeight    = Integer.*MAX_VALUE*;           
             for(int k = i; k <= j; k++) {             
                 minHeight = Math.*min*(heights[k],minHeight);           
             }           
             maxArea = Math.*max*(maxArea,(j-i+1) * minHeight);         
         }       
     }       
     return maxArea;     
 }             
 ```



   







 

 

单调栈是本次算法说明的重点，先看单调栈的代码实现：

​     

​        //Java 单调栈实现方法    `public int largestRectangleArea(int[] heights) {   if (heights.length == 0) {     return 0;   }   int maxArea = Integer.*MIN_VALUE*;   Deque<Integer> stack = new ArrayDeque<>();   //放置一个冗余元素方便计算   stack.push(-1);   for (int i = 0; i < heights.length; i++) {     while (stack.peek() != -1 && heights[i] < heights[stack.peek()]) {       int top = stack.pop();       int width = i - stack.peek() - 1;       maxArea = Math.*max*(maxArea, heights[top] * width);     }     stack.push(i);   }   while (stack.peek() != -1) {    int area = heights[stack.pop()] * (heights.length - stack.peek() - 1);        maxArea = Math.*max*(maxArea, area);`      }       return maxArea;     }             









一开始，把 -1 放进栈的顶部来表示开始。初始化时，按照从左到右的顺序，不断将柱子的序号放进栈中，直到遇到相邻柱子呈下降关系，也就是 a[i−1]>a[i] ，该解法维护了一个单调递增的栈。现在，开始将栈中的序号j弹出，直到遇到 stack[j] 满足a[stack[j]]≤a[i] 。每次弹出下标时，用弹出元素作为高，形成的最大面积矩形的宽是当前元素与stack[top-1]之间的那些柱子。

 

​         

到底为什么可以这么做？我们需要分析一下，每一个元素都要入栈一次，出栈一次。入栈的时候是for loop的iteration走到它的时候，那出栈的时候意味着什么呢。想清楚了这一点，我们也就理解了上面的答案。在开胃菜的谷歌面试题中，每个元素出栈，是说明它找到了它在原数组中的next greater element。那这道题呢？元素出栈，意味着，**我们已经计算了以它的顶为上边框的最大矩形（先出栈再计算也算计算过了）。** 

本题目中栈顶元素作为上边框很容易理解，宽度的计算比较难理解stack.size()=3时，i = 2, 出栈后stack.size()=2; 包含[6,-1]两个元素，stack.peek() = 0，width = 2-1-0= 1宽度为1个，也就是只计算了高度为7的一个柱子的面积。再次出栈之后，stack.size()=0，peek()=-1，width = 2-1- (-1) =2，宽度就变成2个，6和7两个柱子再乘以高度即可算出以6为顶的面积。 

因为i时for循环的指针，永远比stack的top指针大于1，所以i-1表示堆栈当前的最大索引，pop1个以后，再减去peek是中间间隔的矩形个数。

