---
title: 学习文档1
date: 
description: 本文项目来自[Github](https://github.com/Determined22/zh-NER-TF)
categories: 学习记录
tags: 
  - Tensorflow
toc: false
# feature: 
widgets:
- search
- category
- tagcloud
- recent_posts
- links
mathjax: true
---
本文用于学习命名实体识别项目时所遇到的问题及学习过程的记录。


<!-- more -->
# tf.contrib.crf.crf_log_likelihood

# 交叉熵
交叉熵可用来衡量两个概率分布之间的相似性。给定两个概率分布p,q，通过q来表示p的交叉熵为：

$$H(p, q)=-\sum_{x} p(x) \log q(x)$$

概率分布函数满足\\(\sum_{n=1}^{N}p(x_{n})=1\\) 。但在tf.nn.softmax_cross_entropy_with_logits()中无需对logits进行归一化。因为Tensorflow内部机制会将其进行归一化操作以提高效率。原因详见[Pluskid的博客Softmax vs. Softmax-Loss: Numerical Stability](http://freemind.pluskid.org/machine-learning/softmax-vs-softmax-loss-numerical-stability/)

# mask机制

模型中在使用交叉熵计算loss函数的时候有如下两行代码：
``` python
mask = tf.sequence_mask(self.sequence_lengths)
losses = tf.boolean_mask(losses, mask)
```
对于**sequence_mask()**，查阅官方API，有如下示例：
```python
tf.sequence_mask([[1, 3],[2,0]])  # [[[True, False, False],
                                  #   [True, True, True]],
                                  #  [[True, True, False],
                                  #   [False, False, False]]]
```
可知sequence_mask函数将传入张量扩展一维，长度为参数中的最大值。参数值前标为True,反之为False。类似onehot。

而对于**boolean_mask()**，作用为将mask中标为False的参数全部从losses中剔除，即去除\<PAD>对loss的影响。