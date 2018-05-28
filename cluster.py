'''
这里用python实现，对readDesc产生的trainSet.txt进行训练和聚类，Kmeans是一个无监督的聚类，也就是说，没有测试集
'''
import numpy as np
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans

name = []
clusterFile = "D:\mydata\\a_output\\cluster.txt"
clusterWriter = open(clusterFile, 'w', encoding='utf-8')

x = []
f = open("D:\mydata\\a_output\\train\\trainSet.txt")
num = 1268
cnt = 0
for v in f:
    name.append(v.split(',')[0])
    y = []
    for i in range(num):
        y.append(float(v.split(',')[i + 1]))
    x.append(y)
    cnt = cnt + 1
print(cnt)
#转换成numpy array
x = np.array(x)
#聚类的数量
n_clusters = 120
#把数据和对应的分类放入聚类函数中进行聚类
cls = KMeans(n_clusters).fit(x)
#x中每项所属分类的一个列表
print("test")

i = 0
for eachline in name:
    clusterWriter.write(eachline + ":::")
    clusterWriter.write(str(cls.labels_[i]) + '\n')
    print(eachline, end=' ')
    print(str(cls.labels_[i]))
    i = i + 1

'''
#画图
markers = ['^', 'x', 'o', '*', '+']
for i in range(n_clusters):
    members = cls.labels_ == i
    plt.scatter(x[members, 0], x[members, 1], s=60, marker=markers[i], c='b', alpha=0.5)
plt.title(' ')
plt.show()
'''
