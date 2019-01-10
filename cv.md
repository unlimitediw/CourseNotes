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
      
      
      
> city prediction

* 为什么选这个题目呢，之前看gan的时候觉得很好玩，然后kaggle上小的竞赛基本都是看看别人的kernel然后写一写就完事了，而且kaggle方面的数据都是很完备的。就想着能不能自己做一个纯独立设计项目达到什么成果。最初的目标设定的比较大，用rnn，lstm之类的技术结合GAN，pixel2pixel去做一个未来城市地图的预测，同时用rcnn做一个全球地形搜索工具，寻找世界上宜居但还没开发的地方。但现实是非常残酷的。
* 首先面对的问题是缺乏数据集，不像kaggle上公司给你提供好了几万条非常干净的数据，想单纯从互联网上抓取想要的数据还是比较困难的。最困难的一块是数值数据，比如我想做监督学习，假如用gdp或人口来判定一个城市的发展状况，我很难获得同年分准确的数据，那个时候是搜了很多网站最后还是在OCED和一个？网站获得了相对准确的标签。大概有200+条城市gdp和4000+条人口吧，非常幸运的是都是2014年统计的。后面还有一些Wiki的数据智能用regex来处理了。对于csv文件我编写了自己的api做相关数据预处理工作，比如根据数据内容删行删列，根据特定公式创造缺失数值等。 在特征分析方面，因为数据获取困难，真的是一条特征都不想丢，就做了一些bagging的操作，希望能扩大自己的数据集，在城市预测上降低variance还是有一定效果的。剩下的就是一些normalization的操作，不同的数据有各自的处理办法，比如实在没相关性的类别数据那就one hard encoding了，能变成continuous型的我都尽量让他变成那种，大部分都是用standarization处理的，效果比minmax norm好很多，个别数据如经纬度就除以一个特定的数值吧，比如180。过程中也尝试了一些数据merging 效果不太好我就不用了。
* 图像数据那块，我看了google static map api，挺好用的，分别提取了单独路线图，大致地形图，我们正常看的地图（去字）和卫星地图，当初是拿这个来预测验证城市人口的。
* 小数据，我的目标又是做regression。就用了svm了，用的是自己的smo，但是后来还是有点慢就调用sklearn api了，’rbf‘的表现还是比较好的，能达到69%。mlp以前数据量大的时候一直表现很好，这次数据集太小了，就表现的有点差，设多层的时候还遇到了梯度弥散，因为完全是我自己写的mlp，中间检查了各个层的输出，很多activation function都直接归零了。改城relu效果也不太好，因为模型本身不太适合，就没深究调整了。
* 这一块也咨询了我的教授caliskan，她给了很多有关数据预处理的指导吧，比如政府数据是否可信之类的。

* 用地图预测人口那块表现其实没那么好，最初的时候还失误把randomseed动了一下，打乱了训练集和测试集，不过还是又效果的。最初迷信vgg16，在以前做过的2类问题上表现很好，但是到了10类分类的时候就差很多了。我咨询导师robert pless。他当时的建议是，一定要控制好数据集的scale size之类的，还有地图照片的状况。以防止cnn直接识别某些没有意义的特征了。同时建议我做内层的可视化。后来换了小点的cnn模型效果也还行把。

* 在后面gan那块我读了很多文献，并用cuda做了一次地图生成，不过完全是基于jun cyclegan的原作者github上的源码做的

> PIMA疾病预测

* 这本身是一个小项目，其实还做过很多别的，比如猫狗分类，各种模型下的mnist，工资预测。用了比如pca。pima这块主要当时也自己写了C45 kdtree。用了knn做，也用了kmeans。后来发现居然还有kmknn，两者的结合，也做了一下。

* 说到pca，做mnist的时候就发现非常好用，提速很多，还能降噪。可惜cnn的架构导致不能用，不过cnn本身也是非线性模型，能直接用activation完成这些。

> GAME AI游戏平台

* 这个其实是和朋友一起做的项目，我主要负责的是所有的算法设计和网络部署，我那个朋友是做平台页面设计之类的。、
* 非常好玩，那个时候蒙特卡洛树很好，我小时候也很喜欢下围棋，就设计了很多独特的evaluation function。找朋友来下基本都下不过设计的ai。虽然只是五子棋的拓展，但其中minmax ab剪枝本质和深蓝做的事情是没区别的。那个时候蒙特卡洛的增强学习就没有细致了解了。只是知道棋盘太大搜索不玩，只能尽力完成，用概率去做，有点像udp吧。
* N-puzzle的时候专门去看了heuristic library，有很多好玩的限制方程，最后还是选择了线冲突和局布数据库的启发式。

> AWS主要做了一些网络部署的工作。
* Kinesis 

> Branch prediction
































