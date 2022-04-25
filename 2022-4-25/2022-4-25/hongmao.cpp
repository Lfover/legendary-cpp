#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


int main()
{
	vector<int> num;
	for (int i = 0; i < 10; i++)
	{
		cin >> num[i];
	}
	int n = num.size();
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i; j < n; j++)
		{
			if (num[j] > num[j + 1])
			{
				int tem = num[j + 1];
				num[j + 1] = num[j];
				num[j] = tem;
				
			}
		}
	}
	int k = 0;
	while (k < n - 1)
	{
		if (num[k] == num[k + 1])
		{
			k++;
			continue;
		}
		else
		{
			cout << num[k + 1];
			break;
		}
	}
	if (k == n - 1)
		cout << "NULL" << endl;
	return 0;
}