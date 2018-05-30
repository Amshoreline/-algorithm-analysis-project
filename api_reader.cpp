/*这是一个提取API名称的程序*/
/*

#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <set>
using namespace std;

string readApiLines(string line);

int main()
{
	const int maxLineLength = 50000;
	vector<string> whitelist;
	set<string> apis;

	string apiPath = "D:\\mydata\\a_output\\apilist_for_apk\\";
	string whitePath = "D:\\mydata\\a_output\\white.txt";
	string outputPath = "D:\\mydata\\a_output\\api.txt";
	fstream fout(outputPath, ios::out);
	fstream readWhite(whitePath, ios::in);
	if (!readWhite.is_open() || !fout.is_open())
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
	int linecnt;
	for (int i = 0; i < length; i++)
	{
		fread.open(apiPath + whitelist[i] + ".apk.txt", ios::in);
		if (!fread.is_open())
		{
			cout << "找不到指定文件:" << endl;
			cout << apiPath + whitelist[i] + ".apk.txt"<< endl;
			system("pause");
			exit(0);
		}
		linecnt = 0;
		while (fread.getline(line, maxLineLength))
		{
			//过滤空行
			if (strlen(line) > 1)
			{
				linecnt++;
				apis.insert(readApiLines(line));
			}
		}
	//	cout << "API文件一共" << linecnt << "行" << endl;
		//读取apis并写入fout
		fout << whitelist[i] << ',';
		set<string>::iterator k;
		for (k = apis.begin(); k != apis.end(); ++k)
		{
			fout << *k << ',';
		}
		fout << endl;

		apis.clear();
		fread.close();
	}

	fout.close();
	readWhite.close();
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
