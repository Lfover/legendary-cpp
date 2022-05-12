#include <iostream>
#include <vector>
using namespace std;
const int N = 1000;
int main()
{
	vector<int> A;
	vector<int> B;
	for (int i = 0; i < N; i++) cin >> A[i];
	for (int i = 0; i < N; i++) cin >> B[i];
	vector<int> C;
	vector<int> D;//结果
	int n = A.size();
	int m = B.size();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (A[i] == B[j])
			{
				C.push_back(A[i]);
			}
		}
	}
	//去重
	int num = C.size();
	for (int i = num - 1; i > 0;)
	{
		if (C[i] == C[i - 1])
			i--;
		else
		{
			D.push_back(C[i]);
			i--;
		}		
	}
	for (int i = 0; i < D.size() - 1; i++)
	{
		cout << D[i] << ' ';
	}
	cout << endl;
	system("pause");
	return 0;
}