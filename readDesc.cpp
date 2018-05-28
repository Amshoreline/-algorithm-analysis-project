/*
 这里采用C++读取第一步产生Desc.txt文件，并生成指定的训练集
*/
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <cstdio>
#include <vector>
#include <map>
#include <set>
using namespace std;

const int maxLineLength = 500;
const int numoftopic = 10;
int cnt = 0;  //cnt表示所有的单词数
set<string> words;
map<string, int> dictionary;
vector<string> index2string;
fstream writeTrain;

void parseLine(string attribute, int topoicnum);
void extractWord(string attribute, int topicnum);
int main()
{
	string filePath = "D:\\mydata\\a_output\\Desc.txt";
	string trainPath = "D:\\mydata\\a_output\\train\\trainSet.txt";
	fstream reader(filePath, ios::in);
	writeTrain.open(trainPath, ios::out);
	if (!reader.is_open() || !writeTrain.is_open())
	{
		cout << "读取文件失败，请重试" << endl;
		system("pause");
		exit(0);
	}

	char readline[maxLineLength];
	//第一遍确认所有的单词
	while (reader.getline(readline, maxLineLength))
	{
		extractWord(readline, numoftopic);
	}

	//得出字典的对应表
	set<string>::iterator i;
	for (i = words.begin(); i != words.end(); ++i)
	{
		dictionary[*i] = cnt;
		index2string.insert(index2string.end(), *i);
		++cnt;
	}


	//第二遍得出训练集
	reader.close();
	reader.open(filePath, ios::in);
	while (reader.getline(readline, maxLineLength))
	{
		parseLine(readline, numoftopic);
	}
	cout << cnt << endl;
	system("pause");
}
void extractWord(string attribute, int topicnum)
{
	int len = attribute.length();
	int offset = attribute.find(":::");
	int tmps, tmpe;
	string word;
	map<string, float> *tmpattribute = new map<string, float>();

	offset += 8;
	while (--topicnum)
	{
		tmps = attribute.find_first_of('*', offset);
		tmpe = attribute.find_first_of('+', tmps + 2);
		word = attribute.substr(tmps + 2, tmpe - tmps - 4);
		words.insert(word);
		offset = tmpe + 2;
	}
	tmps = attribute.find_first_of('*', offset);
	tmpe = len - 1;
	word = attribute.substr(tmps + 2, tmpe - tmps - 4);
	words.insert(word);
}
void parseLine(string attribute, int topicnum)
{
	int len = attribute.length();
	int offset = attribute.find(":::");
	int tmps, tmpe;
	float num;
	string word;
	map<int, float> *tmpattribute = new map<int, float>();
	string name = attribute.substr(0, offset);
	
	offset += 8;
	while (--topicnum)
	{
		tmps = attribute.find_first_of('*', offset);
		num = atof(attribute.substr(offset, tmps - offset).c_str());
		tmpe = attribute.find_first_of('+', tmps + 2);
		word = attribute.substr(tmps + 2, tmpe - tmps - 4);
		offset = tmpe + 2;
		(*tmpattribute).insert(make_pair(dictionary[word], num));
	}
	tmps = attribute.find_first_of('*', offset);
	num = atof(attribute.substr(offset, tmps - offset).c_str());
	tmpe = len - 1;
	word = attribute.substr(tmps + 2, tmpe - tmps - 4);
	(*tmpattribute).insert(make_pair(dictionary[word], num));
	map<int, float>::iterator i;
	//开始写入训练集
	writeTrain << name << ',';
	//二次利用offset环保
	offset = 0;
	for (i = (*tmpattribute).begin(); i != (*tmpattribute).end(); ++i)
	{
		for (int j = offset; j < (*i).first; ++j)
			writeTrain << 0 << ',';
		writeTrain << (*i).second << ',';
		offset = (*i).first + 1;
	}
	for (int j = offset; j < cnt; ++j)
	{
		writeTrain << 0;
		if (j == cnt - 1)
			writeTrain << '\n';
		else
			writeTrain << ',';
	}

	tmpattribute->clear();
}
