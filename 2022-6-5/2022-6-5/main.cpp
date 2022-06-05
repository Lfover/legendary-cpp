#include "BitZip.h"

#include <iostream>
using namespace std;


void menu()
{
	cout << "*************************************************" << endl;
	cout << "***             功能操作：                    ***" << endl;
	cout << "***             1. 压缩                       ***" << endl;
	cout << "***             2. 解压缩                     ***" << endl;
	cout << "***             3. 退出                       ***" << endl;
	cout << "*************************************************" << endl;
}

int main()
{
	int input = 0;
	string fileName;
	while (input != 3)
	{
		menu();
		cout << "请输入要进行的操作> ";
		cin >> input;
		switch (input)
		{
		case 1:
		{
			cout << "请输入要压缩文件的路径>";
			cin >> fileName;
			BitZip bz;
			bz.Deflate(fileName);
			break;
		}
		case 2:
		{
			cout << "请输入要解压缩文件的路径>";
			cin >> fileName;
			BitZip bz;
			bz.unDeflate(fileName);
			break;
		}
		case 3:
			break;
		default:
			cout << "输入非法，请正确选择!!!" << endl;
			break;
		}
	}

	return 0;
}
