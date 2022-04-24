//#include <iostream>
//using namespace std;
//int n;//六宫格数量
//int c = 0;//最终的结果
//int main()
//{
//	int i, j;
//	cin >> n;
//	int nums[30 * 6][6];
//	for (i = 0; i < n * 6; i++)
//	{
//		for (j = 0; j < 6; j++)
//		{
//			cin >> nums[i][j];
//		}
//	}
//	int sum = 0;
//	int m = 0;
//	i = 0;
//	j = 0;
//	while (n)
//	{
//		i = m * 6;
//		for (i; i < (m + 1) * 6; i++)
//		{
//			for (j = 0; j < 6; j++)
//			{
//				sum += nums[i][j];
//			}
//			if (sum != 21)
//			{
//				sum = 0;
//				break;
//			}
//			else
//			{
//				sum = 0;
//				continue;
//			}
//		}
//		sum = 0;
//		if (i == (m + 1) * 6)
//		{
//			
//			for (j = 0; j < 6; j++)
//			{  
//				i = m * 6;
//				for (i; i < (m + 1) * 6; i++)
//				{
//					sum += nums[i][j];
//				}
//				if (sum != 21)
//				{
//					sum = 0;
//					break;
//				}
//				else
//				{
//					sum = 0;
//					continue;
//				}
//			}
//			if (j == 6)
//			{
//				c++;
//			}
//			else
//			{
//				m++;
//			}
//		}
//		else
//			m++;
//		n--;
//	}
//	cout << c << endl;
//	system("pause");
//	return 0;
//}

#include <iostream>
using namespace std;
int M;//M个数据
int hp, Low, Up, N;
int NP[10];
int main()
{
	cin >> M;
	while (M--)
	{
		cin >> hp >> Low >> Up >> N;
		for (int i = 0; i < N; i++)
		{
			cin >> NP[i];
		}
		int UUP = hp - Low;
		int LOW = hp - Up;
		int c = UUP / NP[N - 1];
		cout << c + 1 << endl;
	}
	return 0;
}