'''
这是一个读取googleplay应用的description(eng).txt的程序，并且提取其中的主题，"主函数"的filePath表示应用的路径
对于非英文description的应用直接舍弃，并将其名字写入filter.txt文档中，其余参与聚类的应用写入white.txt中
该程序最终生成一个Desc.txt文件，表示每个应用程序description的语法分析结果:
Desc.txt条目的样例：
  air.bv.fc2.live:::(0, '0.055*"live" + 0.047*"broadcast" + 0.047*"program")
  ir.com.coworkdream.PicrossLUNA:::(0, '0.034*"moon" + 0.028*"time")
'''

from nltk.tokenize import RegexpTokenizer
from stopwords import get_stopwords
from nltk.stem.porter import PorterStemmer
from gensim import corpora, models
import langid
import numpy as np
import csv
from matplotlib import pyplot as plt
import math
import gensim
import os
import sys

tokenizer = RegexpTokenizer(r'\w+')
end_stop = get_stopwords('en')
my_stopwords = {'www', 'http', 'com', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'}
p_stemmer = PorterStemmer()
outputFile = "D:\mydata\\a_output\Desc.txt"
whiteFile = "D:\mydata\\a_output\\white.txt"
filterFile = "D:\mydata\\a_output\\filter.txt"
output = open(outputFile, 'w', encoding='utf-8')
filterList = open(filterFile, 'w', encoding='utf-8')
whiteList = open(whiteFile, 'w', encoding='utf-8')
texts = []
cnten = 0
cntother = 0

def readDesc(filePath):
    pathDir = os.listdir(filePath)
    for smallItem in pathDir:
        smallPath = os.path.join('%s\%s' % (filePath, smallItem))
        if os.path.isfile(smallPath):
            print("There exists a single file in the direct subpackage")
            sys.exit()
        smallDir = os.listdir(smallPath)
        count = 0
        for miniItem in smallDir:
            if str(miniItem)[0] == '[':
                count = count + 1
                if count > 1:
                        print("There exists more than one Description folder")
                        sys.exit()
                miniPath = os.path.join('%s\%s' % (smallPath, miniItem))
                miniDir = os.listdir(miniPath)
                for microItem in miniDir:
                    if str(microItem) == 'Description(eng).txt':
                        microPath = os.path.join('%s\%s' % (miniPath, microItem))
                        readFile(microPath, smallItem)

def readFile(filename, appname):
    fopen = open(filename, 'rb')
    lower = fopen.read().decode('utf-8').lower()
    if translate(lower, appname) == 0:       #识别语言，如果不是英文则直接返回
        return

    output.write(appname + ":::")
    tokenization = tokenizer.tokenize(lower)                             #进行分词
    stopped_standard = [i for i in tokenization if i not in end_stop]    #过滤停用词 standard
    stopped = [i for i in stopped_standard if i not in my_stopwords]     #过滤自定义停用词
    stemmed = [p_stemmer.stem(i) for i in stopped]                       #提取主干
    smalltexts = []
    smalltexts.append(stemmed)
    smalldictionary = corpora.Dictionary(smalltexts)
    smallcorpus = [smalldictionary.doc2bow(smalltext) for smalltext in smalltexts]
    smallldamodel = gensim.models.ldamodel.LdaModel(smallcorpus, num_topics=1, id2word=smalldictionary, passes=1)
    for i in smallldamodel.print_topics(num_topics=1, num_words=10):
        output.write(str(i).encode().decode(encoding='UTF-8', errors='strict'))
    output.write('\n')
#    print(smallldamodel.print_topics(num_topics=1, num_words=4))
    texts.append(stemmed)

    fopen.close()

def translate(line, appname):
    global cnten
    global cntother
    lineTuple = langid.classify(line)
    if lineTuple[0] != 'en': #如果不是英文则将该app名写到filterlist,并返回false
        filterList.write(appname + '\n')
        cntother = cntother + 1
        return 0
    whiteList.write(appname + '\n')
    cnten = cnten + 1
    return 1


if __name__ == '__main__':

    filePath = "D:\mydata\googleplay_apks\googleplay"
    readDesc(filePath)

    #dictionary = corpora.Dictionary(texts)                  #将结果转化为 (id, term) 的词典
    #print(dictionary.token2id)
    #corpus = [dictionary.doc2bow(text) for text in texts]   #整理成矩阵



    #ldamodel = gensim.models.ldamodel.LdaModel(corpus, num_topics=30, id2word=dictionary, passes=1)

    #print(ldamodel.print_topics(num_topics=30, num_words=8))
    #output.write('\n')
    #print(str(cnten) + " versus " + str(cntother))


whiteList.close();
output.close();
filterList.close();

