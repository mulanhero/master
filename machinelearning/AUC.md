#AUC

让我们从头说起，首先AUC是一种用来度量分类模型好坏的一个标准。这样的标准其实有很多，例如：大约10年前在machine learning文献中一统天下的标准：分类精度；在信息检索(IR)领域中常用的recall和precision，等等。其实，度量反应了人们对” 好”的分类结果的追求，同一时期的不同的度量反映了人们对什么是”好”这个最根本问题的不同认识，而不同时期流行的度量则反映了人们认识事物的深度的变 化。近年来，随着machine learning的相关技术从实验室走向实际应用，一些实际的问题对度量标准提出了新的需求。特别的，现实中样本在不同类别上的不均衡分布(class distribution imbalance problem)。使得accuracy这样的传统的度量标准不能恰当的反应分类器的performance。举个例子：测试样本中有A类样本90个，B 类样本10个。分类器C1把所有的测试样本都分成了A类，分类器C2把A类的90个样本分对了70个，B类的10个样本分对了5个。则C1的分类精度为 90%，C2的分类精度为75%。但是，显然C2更有用些。另外，在一些分类问题中犯不同的错误代价是不同的(cost sensitive learning)。这样，默认0.5为分类阈值的传统做法也显得不恰当了。

为了解决上述问题，人们从医疗分析领域引入了一种新的分类模型performance评判方法——ROC分析。ROC分析本身就是一个很丰富的内容，有兴趣的读者可以自行Google。由于我自己对ROC分析的内容了解还不深刻，所以这里只做些简单的概念性的介绍。

ROC的全名叫做Receiver Operating Characteristic，其主要分析工具是一个画在二维平面上的曲线——ROC curve。平面的横坐标是false positive rate(FPR)，纵坐标是true positive rate(TPR)。对某个分类器而言，我们可以根据其在测试样本上的表现得到一个TPR和FPR点对。这样，此分类器就可以映射成ROC平面上的一个点。调整这个分类器分类时候使用的阈值，我们就可以得到一个经过(0, 0)，(1, 1)的曲线，这就是此分类器的ROC曲线。一般情况下，这个曲线都应该处于(0, 0)和(1, 1)连线的上方。因为(0, 0)和(1, 1)连线形成的ROC曲线实际上代表的是一个随机分类器。如果很不幸，你得到一个位于此直线下方的分类器的话，一个直观的补救办法就是把所有的预测结果反向，即：分类器输出结果为正类，则最终分类的结果为负类，反之，则为正类。虽然，用ROC curve来表示分类器的performance很直观好用。可是，人们总是希望能有一个数值来标志分类器的好坏。于是Area Under roc Curve(AUC)就出现了。顾名思义，AUC的值就是处于ROC curve下方的那部分面积的大小。通常，AUC的值介于0.5到1.0之间，较大的AUC代表了较好的performance。好了，到此为止，所有的 前续介绍部分结束，下面进入本篇帖子的主题：AUC的计算方法总结。

 

最直观的，根据AUC这个名称，我们知道，计算出ROC曲线下面的面积，就是AUC的值。事实上，这也是在早期Machine Learning文献中常见的AUC计算方法。由于我们的测试样本是有限的。我们得到的AUC曲线必然是一个阶梯状的。因此，计算的AUC也就是这些阶梯下面的面积之和。这样，我们先把score排序(假设score越大，此样本属于正类的概率越大)，然后一边扫描就可以得到我们想要的AUC。但是，这么 做有个缺点，就是当多个测试样本的score相等的时候，我们调整一下阈值，得到的不是曲线一个阶梯往上或者往右的延展，而是斜着向上形成一个梯形。此时，我们就需要计算这个梯形的面积。由此，我们可以看到，用这种方法计算AUC实际上是比较麻烦的。

 

一个关于AUC的很有趣的性质是，它和Wilcoxon-Mann-Witney Test是等价的。这个等价关系的证明留在下篇帖子中给出。而Wilcoxon-Mann-Witney Test就是测试任意给一个正类样本和一个负类样本，正类样本的score有多大的概率大于负类样本的score。有了这个定义，我们就得到了另外一中计算AUC的办法：得到这个概率。我们知道，在有限样本中我们常用的得到概率的办法就是通过频率来估计之。这种估计随着样本规模的扩大而逐渐逼近真实值。这 和上面的方法中，样本数越多，计算的AUC越准确类似，也和计算积分的时候，小区间划分的越细，计算的越准确是同样的道理。具体来说就是统计一下所有的 M×N(M为正类样本的数目，N为负类样本的数目)个正负样本对中，有多少个组中的正样本的score大于负样本的score。当二元组中正负样本的 score相等的时候，按照0.5计算。然后除以MN。实现这个方法的复杂度为O(n^2)。n为样本数（即n=M+N）

 

第三种方法实际上和上述第二种方法是一样的，但是复杂度减小了。它也是首先对score从大到小排序，然后令最大score对应的sample 的rank为n，第二大score对应sample的rank为n-1，以此类推。然后把所有的正类样本的rank相加，再减去正类样本的score为最 小的那M个值的情况。得到的就是所有的样本中有多少对正类样本的score大于负类样本的score。然后再除以M×N。即

 

AUC=((所有的正例位置相加)-M*(M+1))/(M*N)

![](http://i.imgur.com/jZRSdE5.jpg)

 

另外，特别需要注意的是，再存在score相等的情况时，对相等score的样本，需要 赋予相同的rank(无论这个相等的score是出现在同类样本还是不同类的样本之间，都需要这样处理)。具体操作就是再把所有这些score相等的样本 的rank取平均。然后再使用上述公式。