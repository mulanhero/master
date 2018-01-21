#LogicalRegression
##0 背景
回归(regression)是指拟合。通过回归建立的模型即就是构建一个模型去拟合已有的数据，这样的模型称为广义线性模型(generalized linear model)。

根据因变量分布的不同，又分为：

* 多重线性回归： 因变量连续分布
* logistic回归：因变量二项分布 (实质上，逻辑回归因变量可二项分布，也可以多分类，但二分类的最常见)
* Poission回归：因变量呈现Possion分布
* 负二项回归：因变量呈现负二项分布

Regression问题的常规步骤为：

1. 寻找h函数（即hypothesis）；
2. 构造J函数（损失函数）；
3. 想办法使得J函数最小并求得回归参数（θ）

##1 逻辑回归
逻辑回归与预测：根据模型，在不同自变量情况下，预测发生某种情况结果的可能性。 例如，以年龄、性别、饮食习惯、幽门螺杆菌感染做自变量，因变量为**Yes/No**胃癌。自变量可以是连续的(如年龄)，也可以是分类的(如性别)。

###1.1 构造预测函数h
Logistic回归实际上是一种分类方法，主要用于两分类问题，所以利用了Logistic函数(或称为Sigmoid函数)，结果处于[0,1], 函数形式为：

![](http://i.imgur.com/zzqajFQ.png)

Sigmoid 函数在有个很漂亮的“S”形，如下图所示（引自维基百科）

![](http://i.imgur.com/2G4QJt1.png)

下面左图是一个线性的决策边界，右图是非线性的决策边界:

![](http://i.imgur.com/sKsF6Lo.png)

对于线性边界的情况，线性函数如下，基于此函数，根据自变量(x1,x2)就可以判定因变量y为0或者1。

![](http://i.imgur.com/YPAQP7I.png)

该函数为线性的结论是线性的，而我们需要二分类的，因此，可以借用逻辑函数(sigmoid)进行转化，让其结果落在[0,1]之间，所以，让该函数做g函数的自变量，那么预测函数为：

![](http://i.imgur.com/vRqGSPh.png)

函数h(x)的值有特殊的含义，它表示结果取1的概率，因此对于输入x,分类结果为类别1和类别0的概率分别为：

![](http://i.imgur.com/CbnXqhr.png)

###1.2 构造构造损失函数J

Cost函数和J函数如下，它们是基于最大似然估计推导得到的:

![](http://i.imgur.com/HU0CguC.png)
![](http://i.imgur.com/RdkQQrs.png)

下面详细说明推导的过程：

(1)式综合起来可以写成：

![](http://i.imgur.com/ysJhBxK.png)

取似然函数为：

![](http://i.imgur.com/1RBXP2H.png)

对似然函数取对数为：
![](http://i.imgur.com/JlHiRWj.png)

则损失函数为：

![](http://i.imgur.com/M1lnn1w.png)

因为乘了一个负的系数-1/m，所以损失函数J取最小值时的θ为要求的最佳参数

###1.3 梯度下降法求损失函数J的最小值

让参数集每次下降一个梯度delta，逐渐让损失函数到达最小值。而梯度delta由步长alpha和损失函数J在该参数集的偏导乘积组成。

![](http://i.imgur.com/XkpJAJd.png)
![](http://i.imgur.com/1QwOLFz.png)

则更新过程可以写为：

![](http://i.imgur.com/La1dLVn.png)

###1.4 实施
上面公式中，**i** 表示某条instance(instance由一系列feature的签名sign构成)，当 **i** 确定，即instance确定时，根据当前的预测函数**h**的系数计算预测结果h(x),其值在[0-1]之间, 减去该instance的实际效果0或者1，然后乘以该instance在j上分量**x<sub>i</sub><sup>j</sup>**(即第j个feature的sign)

对每一个系数的梯度而言，需要把所有的m个instance都过一遍。对一个mini-batch中包含的m条instance计算，求和，求均值(1/m)。就得到在系数 **θ<sub>j</sub>** 上的delta。

用silta的j分量的系数 - 步长alpha * silta在j分量上delta；

可得到silta在j分量上的下一次的系统silta。

如果一个instance有n个feature(sign)，则就会有n+1个系数(常数系统可忽略)。 对于一个instance可能具有千亿级feature的应用来说，则也可能会有千亿级的系数。实在太庞大了，所以，需要降维。

##2 优化算法

上面的梯度下降法是一种可行的方法，可是对每一个系数**θ<sub>j</sub>**来说，每个mini-batch中每一条instance都需要过一遍。计算量太大，让我们看看一些其他的方法:

##2.1 向量化Vectorization

Vectorization是使用矩阵计算来代替for循环，以简化计算过程，提高效率。

向量化的过程如下：

约定训练数据的矩阵形式如下，x的每一行为一条训练样本，每个样本具有n个特征，而每一列为不同的特称取值： 

![](http://i.imgur.com/SKaXrii.png)

<font color=red>A</font>矩阵中每一行都是线性等式，而我们需要的是二分类的结果，因此，可以用g(A)对其进行变换。 

注意：在上公示中，A表示g(A)中的一列，**A<sub>i</sub>** 是一条instance与所有**参数**相乘的结果。

因此，上面的公式可变形为：

![](http://i.imgur.com/u7PaWTA.png)

综上所述，Vectorization后**θ**更新的步骤如下:

1. 求 A = x * θ     //以当前参数θ，用mini-batch的instance做乘积
2. 求 E = g(A) - y  //用g(A)转换为[0,1]之间的概率, 与真实的y(0或者1)求误差
3. 求 θ := θ - 1/m(alpha * x<sup>T</sup> * E)  //用学习率、误差、instance求梯度delta，更新模型参数

##2.2 正则化Regularization
**过拟合问题**

对于线性回归或逻辑回归的损失函数构成的模型，可能会有些权重很大，有些权重很小，导致过拟合（就是过分拟合了训练数据），使得模型的复杂度提高，泛化能力较差（对未知数据的预测能力）。

下面左图即为欠拟合，中图为合适的拟合，右图为过拟合。

![](http://i.imgur.com/LpNqAg1.png)

**问题的主因**

过拟合问题往往源自过多的特征

**解决方法**

1. 减少特征数量（减少特征会失去一些信息，即使特征选的很好）
	* 可用人工选择要保留的特征
	* 模型选择算法
2. 正则化（特征较多时比较有效）
	* 保留所有特征，但减少θ的大小

**正则化方法**

正则化是结构风险最小化策略的实现，是在经验风险上加一个正则化项或惩罚项。正则化项一般是模型复杂度的单调递增函数，模型越复杂，正则化项就越大。

从房价预测问题开始，这次采用的是多项式回归。左图是适当拟合，右图是过拟合。

![](http://i.imgur.com/PbsYRLq.png)

直观来看，如果我们想解决这个例子中的过拟合问题，最好能将**x<sup>3</sup>、x<sup>4</sup>**的影响消除，即让**θ<sub>3</sub>、θ<sub>4</sub>**均为0.假设对**θ<sub>3</sub>、θ<sub>4</sub>**进行惩罚，并且令其很小，一个简单的办法就是给原来的cost函数加上两个略大的惩罚项，例如：

![](http://i.imgur.com/nOvfNw6.png)

这样在最小化Cost函数的时候，就能够**θ<sub>3</sub>、θ<sub>4</sub>**约为0。

lambda是正则项系数：

* 如果它的值很大，说明对模型的复杂度惩罚大，对拟合数据的损失惩罚小，这样它就不会过分拟合数据，在训练数据上的偏差较大，在未知数据上的方差较小，但是可能出现欠拟合的现象；
* 如果它的值很小，说明比较注重对训练数据的拟合，在训练数据上的偏差会小，但是可能会导致过拟合。

正则化后的梯度下降算法θ的更新变为：
	
![](http://i.imgur.com/3AAFAXo.png)

正则化后的线性回归的Normal Equation的公式为：
	
![](http://i.imgur.com/u7xEsPZ.png)


其他优化算法

* Conjugate gradient method(共轭梯度法)
* Quasi-Newton method(拟牛顿法)
* BFGS method
* L-BFGS(Limited-memory BFGS)

后二者由拟牛顿法引申出来，与梯度下降算法相比，这些算法的优点是：

* 第一，不需要手动的选择步长；
* 第二，通常比梯度下降算法快；

但是缺点是更复杂。