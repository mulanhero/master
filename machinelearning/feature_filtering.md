#特征过滤
##背景
对于一个日志处理系统，为了保证高大全，特征可能达到千亿级；然而，对某些模型来说，可能存在较多的特征是无用特征(或者是贡献非常低的)；因此如何进行特征过滤就显得非常有必要。

##日志处理阶段的特征过滤
对日志extract成instance之后，每个特征一列，因此，一个instance可能就有很多列。采用一定的规则过滤一些无用特征，将会减少instance的长度。 例如，可能的过滤规则有：

* 对于广告系统来说，根据show来过滤特征，比如show < 4 的特征可以过滤掉；在通常情况下，可以过滤掉甚至95%的特征。 具体做法为：在extract日志的时候，同时输出fea和show，最后汇总 fea的show，将show <４的特征列入blacklist, 然后扫描每一条instance的特征，如果在blacklist中，则可以去除掉。

#在模型训练阶段过滤特征
其基本原理是，比如batch-lr需要很多轮迭代，先进行一轮训练，先根据产生的初步模型(feature:weight)对把某些feature过滤掉；后面的多轮迭代，这些feature就不出现在instance中，从而大大减少训练数据，提高时效性。 (比如platform中的KKT模块)。