#include "BitZip.h"

#include <iostream>
using namespace std;


void menu()
{
	cout << "*************************************************" << endl;
	cout << "***             ���ܲ�����                    ***" << endl;
	cout << "***             1. ѹ��                       ***" << endl;
	cout << "***             2. ��ѹ��                     ***" << endl;
	cout << "***             3. �˳�                       ***" << endl;
	cout << "*************************************************" << endl;
}

int main()
{
	int input = 0;
	string fileName;
	while (input != 3)
	{
		menu();
		cout << "������Ҫ���еĲ���> ";
		cin >> input;
		switch (input)
		{
		case 1:
		{
			cout << "������Ҫѹ���ļ���·��>";
			cin >> fileName;
			BitZip bz;
			bz.Deflate(fileName);
			break;
		}
		case 2:
		{
			cout << "������Ҫ��ѹ���ļ���·��>";
			cin >> fileName;
			BitZip bz;
			bz.unDeflate(fileName);
			break;
		}
		case 3:
			break;
		default:
			cout << "����Ƿ�������ȷѡ��!!!" << endl;
			break;
		}
	}

	return 0;
}
