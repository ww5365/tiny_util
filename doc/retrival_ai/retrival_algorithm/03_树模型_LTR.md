# 

cart -> gdbt -> Gbrank  landmart  -> deepFM

xgboost

lightGBM





损失函数类型 : 支持gbrank loss、lambdamart dcg loss、lambdamart ndcg loss及regression loss类型。[出自链接](https://www.alibabacloud.com/help/zh/machine-learning-platform-for-ai/latest/gbdt-regression)






## reference

算法知识点——（5）集成算法—GBDT详解  : https://blog.csdn.net/Lynqwest/article/details/101540952

GBDT C++ 实现代码：https://github.com/yarny/gbdt  
    GBDT implements various pointwise, pairwise, listingwis loss functions including mse, logloss, huberized hinge loss, pairwise logloss, GBRank and LambdaMart. It supports easily addition of your own custom loss functions.

Learning to Rank算法学习之GBRank: https://www.biaodianfu.com/gbrank.html

GBrank 代码： https://github.com/szdr/my-gbrank  

GBRank的问题列表 ： https://daimajiaoliu.com/daima/47dd2271c9003fc

gbrank排序为什么会造成预测值为负的原因 : https://blog.csdn.net/a1066196847/article/details/83382708

[搜索排序算法] (https://octopuscoder.github.io/2020/01/19/%E6%90%9C%E7%B4%A2%E6%8E%92%E5%BA%8F%E7%AE%97%E6%B3%95/)  
    LambdaRank，基于xgboost实现，参考：https://github.com/dmlc/xgboost/tree/master/demo/rank
    LambdaMART，基于LightGBM实现，参考：https://github.com/jiangnanboy/learning_to_rank
    Wide&Deep基于TensorFlow实现，参考：https://github.com/tensorflow/ranking

利用lightgbm做learning to rank 排序 : https://github.com/jiangnanboy/learning_to_rank 




一篇文章搞定GBDT、Xgboost和LightGBM的面试  :  https://zhuanlan.zhihu.com/p/148050748


 GBDT和XGBoost对比
1)GBDT是机器学习算法，XGBoost是该算法的工程实现。
2)在使用CART作为基分类器时，XGBoost显式地加入了正则项来控制模型的复杂度，有利于防止过拟合，从而提高模型的泛化能力。
3)GBDT在模型训练时只使用了代价函数的一阶导数信息，XGBoost对代价函数进行二阶泰勒展开，可以同时使用一阶和二阶导数。
4)传统的GBDT采用CART作为基分类器，XGBoost支持多种类型的基分类器，比如线性分类器。
5)传统的GBDT在每轮迭代时使用全部的数据，XGBoost则采用了与随机森林相似的策略，支持对数据进行采样，支持列抽样，不仅能降低过拟合，还能减少计算，这也是xgboost异于传统gbdt的一个特性。
6)传统的GBDT没有设计对缺失值进行处理，XGBoost可以自动学习出它的分裂方向。XGBoost对于确实值能预先学习一个默认的分裂方向。
7)Shrinkage（缩减），相当于学习速率（xgboost中的eta）。xgboost在进行完一次迭代后，会将叶子节点的权重乘上该系数，主要是为了削弱每棵树的影响，让后面有更大的学习空间。实际应用中，一般把eta设置得小一点，然后迭代次数设置得大一点。（补充：传统GBDT的实现也有学习速率）


LightGBM和XGBoost对比

1)XGBoost使用基于预排序的决策树算法，每遍历一个特征就需要计算一次特征的增益，时间复杂度为O(datafeature)。
而LightGBM使用基于直方图的决策树算法，直方图的优化算法只需要计算K次，时间复杂度为O(Kfeature)
2)XGBoost使用按层生长(level-wise)的决策树生长策略，LightGBM则采用带有深度限制的按叶子节点(leaf-wise)算法。在分裂次数相同的情况下，leaf-wise可以降低更多的误差，得到更好的精度。leaf-wise的缺点在于会产生较深的决策树，产生过拟合。
3)支持类别特征，不需要进行独热编码处理
4)优化了特征并行和数据并行算法，除此之外还添加了投票并行方案
5)采用基于梯度的单边采样来保持数据分布，减少模型因数据分布发生变化而造成的模型精度下降
6)特征捆绑转化为图着色问题，减少特征数量

