回顾下简历

> 职业技能
* python: lambda, numpy比较有特色吧，别的就那样了
* java:
  * jvm: class loader, jvm memory(heap gc, stack frame-data create for thread execute)
  * java thread: thread.join() to wait, synchronized to avoid overlap access. state: new, runnable, waiting, blocked, terminated.
* C++: 只会用，会用指针（引用等区别于java的类），上手很快
* C#: 基于.NET和unity docu的API🦐
* cmd还记得点
* 机器学习：
  * 数据预处理与特征工程： 
    * 对于csv格式的数据还是喜欢pandas用，批量操作标记都很方便。对图像数据的话就opencv吧。
    * Aggregation,bagging method， 在做城市预测的时候200+城市太少了，尝试过，但是svm上有微弱的提升但是不确定是不是样本太小导致的。
    * Sampling: 没怎么用过，我的数据集从来都是太小了不够用。
    * PCA的话非cnn图像识别工作下还是很喜欢用的，别的数值型数据一般直接用全特征就好了，因为也不多
    * feature subset，还是算一下信息熵增益就知道了。当然也可以用gini inpurity, gini我不太记得了，不过看一下公式应该就能写。
    * feature creation: 其实觉得意义不大，但是mapping data to new space在svm中还是很重要的，kernel trick用双拉格朗日算子的smo方法让o（n^d)问题编程了o(dn^2)好像。
    * discretization&binarization：非常重要，bin就one hard吧，能连续型的尽量做成连续型
    * 人在特征工程中更intuitive一点，但是深度学习中更需要的是渐进式的test。
  * 模型选择
    * 分类问题：
      逻辑回归，本质和感知机差不多：以前用贝叶斯求过梯度下降公式，和最大概率预计一样的 ylogy + （1-y）log（1-y）就是lossfunction，gd的话就是（h-y）*x 求和，和感知机是一样的，至于activation function的话一般用的是sigmoid function，tanh其实也可以。提到逻辑回归的0-1classification还是要说一下auc，在曲线下区域。在学习过程中会比较喜欢用0.5作为threshold，但是呢，工程验证过乘tp，fp在不同的threshold下表现完全不通，很玄学，看需求吧。
