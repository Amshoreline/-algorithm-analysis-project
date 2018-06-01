/*这是一个提取API名称的程序*/
/*
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
using namespace std;

string readApiLines(string line);
set<string> allapis;

int main()
{
	const int maxLineLength = 50000;
	vector<string> whitelist;
	set<string> apis;

	string apiPath = "D:\\mydata\\a_output\\apilist_for_apk\\";
	string whitePath = "D:\\mydata\\a_output\\white.txt";
	string newwhitePath = "D:\\mydata\\a_output\\newwhite.txt";
	string outputPath = "D:\\mydata\\a_output\\api.txt";
	string apicalledPath = "D:\\mydata\\a_output\\apicalled.txt";

	fstream fout(outputPath, ios::out);
	fstream readWhite(whitePath, ios::in);
	fstream writeWhite(newwhitePath, ios::out);
	fstream writeapi(apicalledPath, ios::out);

	if (!readWhite.is_open() || !fout.is_open() | !writeWhite.is_open())
	{
		cout << "打开文件错误";
		system("pause");
		exit(0);
	}

	int length = 0;
	char line[maxLineLength];
	while (readWhite.getline(line, maxLineLength))
	{
		whitelist.insert(whitelist.end(), line);
		length++;
	}
	cout << "whitellist一共" << length << "行" << endl;
	//读取whitelist
	fstream fread;
	vector<string>::iterator i;
	vector<string>::iterator j;
	int n = 0; //计算写入了几个应用
	for (i = whitelist.begin(); i != whitelist.end(); i++)
	{
		fread.open(apiPath + *i + ".apk.txt", ios::in);
		if (!fread.is_open())
		{
			cout << "找不到指定文件:" << endl;
			cout << apiPath + *i + ".apk.txt"<< endl;
			system("pause");
			exit(0);
		}
		int linecnt = 0;
		while (fread.getline(line, maxLineLength))
		{
			//过滤空行
			if (strlen(line) > 1)
			{
				linecnt++;
				string apiName = readApiLines(line);
				apis.insert(apiName);
				allapis.insert(apiName);
			}
		}
		if (linecnt <= 1)
		{
			cout << *i << "只有" << linecnt << "行" << endl;
			j = i;
			j--;
			whitelist.erase(i);
			i = j;
			apis.clear();
			fread.close();
			continue;
		}
		n++;
	//	cout << "API文件一共" << linecnt << "行" << endl;
		//读取apis并写入fout
		fout << *i << ',';
		set<string>::iterator k;
		int cnt = apis.size();
		fout << cnt << ',';
		for (k = apis.begin(); k != apis.end(); ++k)
		{
			fout << *k << ',';
		}
		//cout << whitelist[i] << "调用了" << cnt << "个API" << endl;
		fout << endl;

		apis.clear();
		fread.close();
	}
	cout << "写入了" << n << "个应用数据" << endl;
	cout << "一共有" << allapis.size() << "种API" << endl;
	set<string>::iterator k;
	for (k = allapis.begin(); k != allapis.end(); ++k)
		writeapi << *k << endl;
	//更新whitelist
	for (i = whitelist.begin(); i != whitelist.end(); ++i)
		writeWhite << *i << endl;

	readWhite.close();
	writeWhite.close();
	fout.close();
	system("pause");
}
string readApiLines(string line)
{
	int start = line.find("android");
	int end = line.find(' ', start);
	if (start < end)
		return line.substr(start, end - start);
	else
		return " ";
}
*/

/*我是一个分隔符——————————————————————————————————————————————*/

/*这是一个检测api文件是否相同的程序*/
/*

#include <iostream>
#include <fstream>
#include <cstring>
#include <string> 
#include <vector>
using namespace std;

const int row = 1000;
const int column = 10000;
vector<string> txt;
vector<string> whitelist;

int main()
{
	string filePath = "D:\\mydata\\a_output\\apilist_for_apk\\";
	string sampleFile = "air.jp.globalgear.kaihi.apk.txt";
	string whitePath = "D:\\mydata\\a_output\\white.txt";
	fstream readSample(filePath + sampleFile, ios::in);
	fstream readWhite(whitePath, ios::in);
	if (!readWhite.is_open() || !readSample.is_open())
	{
		cout << "打开文件错误";
		system("pause");
		exit(0);
	}

	char line[column];
	int len;
	int linecnt = 0;
	while (readSample.getline(line, column))
	{
		len = strlen(line);
		txt.insert(txt.end(), string(line));
		linecnt++;
	}
	cout << linecnt << endl;
	int length = 0;
	while (readWhite.getline(line, column))
	{
		whitelist.insert(whitelist.end(), line);
		length++;
	}
	cout << "whitellist一共" << length << "行" << endl;
	//读取whitelist
	fstream fread;
	for (int i = 0; i < length; i++)
	{
		fread.open(filePath + whitelist[i] + ".apk.txt", ios::in);
		if (!fread.is_open())
		{
			cout << "找不到指定文件:" << endl;
			cout << filePath + whitelist[i] + ".apk.txt" << endl;
			system("pause");
			exit(0);
		}
		int cntline = 0;
		while (fread.getline(line, column))
		{
			if (cntline < linecnt)
			{
				if (txt[cntline] != line)
				{
					cout << "文件内容不同:" << whitelist[i] << endl;
				}
			}
			cntline++;
		}
		if (cntline != linecnt)
		{
			cout << "文件行数不同:" << whitelist[i] << endl;
		}

		fread.close();
	}

	readWhite.close();
	readSample.close();
	system("pause");
}
*/

/*我是一个分隔符——————————————————————————————————————————————*/

/*统计各个API被调用的情况*/
/*
#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

class Api
{
public:
	string name; //api的名字
	int cnt; //api被调用的次数
	Api(string name_)
	{
		name = name_;
		cnt = 0;
	}
	bool operator < (const Api& c) const
	{
		return cnt > c.cnt;
	}
};
//不是我想用全局变量的，是因为怕内存不够啊→_→
vector<string> apis;
vector<Api> sum;  //统计调用某个api的app个数
const int maxlinelength = 100000;
char line[maxlinelength];

int getindex(string name);
int main()
{
	int cnt;
	string eachapp;

	string apicalledpath = "D:\\mydata\\a_output\\apicalled.txt";
	string apipath = "D:\\mydata\\a_output\\api.txt";
	string apifeatpath = "D:\\mydata\\a_output\\apifeat.txt";
	fstream apicalledreader(apicalledpath, ios::in);
	fstream apireader(apipath, ios::in);
	fstream apifeatwriter(apifeatpath, ios::out);

	if (!apicalledreader.is_open() || !apireader.is_open() || !apifeatwriter.is_open())
	{
		cout << "打开文件失败" << endl;
		exit(0);
	}

	cnt = 0;
	while (apicalledreader.getline(line, maxlinelength))
	{
		apis.push_back(line);
		sum.push_back(*(new Api(line))); //构建一下统计表
		cnt++;
	}
	cout << "一共有" << cnt << "种API" << endl;

	//检查逆序
	vector<string>::iterator i__;
	vector<string>::iterator myend = apis.end();
	myend--;
	for (i__ = apis.begin(); i__ != myend; ++i__)
	{
		if (*i__ > *(i__ + 1))
		{
			cout << "逆序" << endl;
			system("pause");
			exit(0);
		}
	}

//	map<string, int>::iterator i_;
//	for (i_ = mapping.begin(); i_ != mapping.end(); ++i_)
//		cout << (*i_).first << " " << (*i_).second << endl;

	int offset, index;
	int start, end;
	int num, size;
	cnt = 0;
	while (apireader.getline(line, maxlinelength))
	{
		eachapp = string(line);
		size = eachapp.size();
		//先读数字
		start = eachapp.find(',') + 1;
		end = eachapp.find(',', start);
		num = atoi(eachapp.substr(start, end).c_str());

		//开始读取该app的调用api列表
		start = end + 1;
		for (int i = 0; i < num; i++)
		{
			end = eachapp.find(',', start);
			index = getindex(eachapp.substr(start, end - start));
			if (index == -1)
			{
				cout << "出错了！" << endl;
				system("pause");
				exit(0);
			}
			else
			{
				sum[index].cnt++;
			}
			start = end + 1;
		}
		cnt++;
		eachapp.clear();
	}
	cout << "一共有" << cnt << "种APP" << endl;

	vector<Api>::iterator k;
	sort(sum.begin(), sum.end());
	cnt = 0;
	int filtersize = 9; //这里可以调整一下过滤大小
	for (k = sum.begin(); k != sum.end(); ++k)
	{
		cnt++;
		if ((*k).cnt <= filtersize) 
			break;
		apifeatwriter << (*k).name << ',' << (*k).cnt << endl;;
	}
	cout << "一共有" << cnt << "种被调用次数不少于" << filtersize + 1 << "的api" << endl;

	sum.clear();
	apireader.close();
	apicalledreader.close();
	apifeatwriter.close();
	system("pause");
}
//二分查找下标
int getindex(string name)
{
	int left = 0, right = apis.size();
	int mid;
	while (left < right)
	{
		mid = (left + right) / 2;
		if (name == apis[mid])
			return mid;
		else if (name < apis[mid])
			right = mid;
		else
			left = mid + 1;
	}
	return -1;
}
*/

/*我是一个分隔符——————————————————————————————————————————————*/
/*生成每个app的特征向量（关于API调用的）*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

vector<string> apis;
vector<int> apivector;
const int maxlinelength = 100000;
char line[maxlinelength];
int getindex(string name);

int main()
{
	string apipath = "D:\\mydata\\a_output\\api.txt";
	string apifeatpath = "D:\\mydata\\a_output\\apifeat.txt";
	string trainApipath = "D:\\mydata\\a_output\\train\\trainApi.txt";
	string apiVectorpath = "D:\\mydata\\a_output\\train\\apiVector.txt";

	fstream apireader(apipath, ios::in);
	fstream apifeatreader(apifeatpath, ios::in);
	fstream trainApiwriter(trainApipath, ios::out);
	fstream apiVectorwriter(apiVectorpath, ios::out);

	if (!apireader.is_open() || !apifeatreader.is_open() || !trainApiwriter.is_open() || !apiVectorwriter.is_open())
	{
		cout << "打开文件失败" << endl;
		system("pause");
		exit(0);
	}
	//先获取api列表
	int cnt = 0, size;
	while (apifeatreader.getline(line, maxlinelength))
	{
		cnt++;
		size = strlen(line);
		int i;
		for (i = 0; i < size; ++i)
		{
			if (line[i] == ',')
				break;
		}
		apis.push_back(string(line).substr(0, i));
	}
	cout << "一共参考了" << cnt << "个API" << endl;
	sort(apis.begin(), apis.end());
	//检查逆序
	vector<string>::iterator i__;
	vector<string>::iterator myend = apis.end();
	myend--;
	for (i__ = apis.begin(); i__ != myend; ++i__)
	{
		if (*i__ > *(i__ + 1))
		{
			cout << "逆序" << endl;
			system("pause");
			exit(0);
		}
	}

	size = apis.size();
	apiVectorwriter << size;
	//读取app的api调用数据

	for (int i = 0; i < size; i++)
		apivector.push_back(0);

	cnt = 0;
	string eachapp, name;
	int start, end, num, index;
	while (apireader.getline(line, maxlinelength))
	{
		for (int i = 0; i < size; i++)
			apivector[i] = 0;

		eachapp = string(line);

		//读名字
		start = 0;
		end = eachapp.find(',');
		name = eachapp.substr(start, end - start);
		//读数字
		start = end + 1;
		end = eachapp.find(',', start);
		num = atoi(eachapp.substr(start, end - start).c_str());
		
		//开始读取该app的调用api列表
		start = end + 1;
		for (int i = 0; i < num; i++)
		{
			end = eachapp.find(',', start);
			index = getindex(eachapp.substr(start, end - start));
			if (index != -1)
			{
				apivector[index] = 1;
			}
			start = end + 1;
		}
		trainApiwriter << name << ',';
		for (int i = 0; i < size - 1; i++)
			trainApiwriter << apivector[i] << ',';
		trainApiwriter << apivector[size - 1] << endl;

		cnt++;
		eachapp.clear();
	}
	cout << "一共有" << cnt << "个app" << endl;

	apireader.close();
	apifeatreader.close();
	trainApiwriter.close();
	apiVectorwriter.close();
	system("pause");
	return 0;
}

//二分查找下标
int getindex(string name)
{
	int left = 0, right = apis.size();
	int mid;
	while (left < right)
	{
		mid = (left + right) / 2;
		if (name == apis[mid])
			return mid;
		else if (name < apis[mid])
			right = mid;
		else
			left = mid + 1;
	}
	return -1;
}
