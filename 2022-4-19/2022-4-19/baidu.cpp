//#include <iostream>
//#include <vector>
//using namespace std;
//int N, M;
//int c;
//const int n = 200010;
//int t[n];
//int main()
//{
//	cin >> N >> M;
//	for (int i = 0; i < N; i++) cin >> t[i];
//	int sum = 0;
//	while (M)
//	{
//		int m;
//		cin >> m;
//		for (int i = 0; i < N; i++)
//		{
//			sum += t[i];
//			if (m >= sum)
//			{
//				c++;
//			}
//			else
//			{
//				break;
//			}
//
//		}
//		cout << c << endl;
//		sum = 0;
//		c = 0;
//		M--;
//	}
//	system("pause");
//	return 0;
//}


//#include <iostream>
//using namespace std;
//int N;
//int num[1025][1025];
//long long sum;
//int main()
//{
//	cin >> N;
//	for (int i = 0; i < N; i++)
//	{
//		for (int j = 0; j < N; j++)
//		{
//			cin >> num[i][j];
//			sum += num[i][j];
//		}
//	}
//	cout << sum << endl;
//	system("pause");
//	return 0;
//}


#include <iostream>
#include <algorithm>
using namespace std;
int N, P;
int h[200010];
int sum;
int main()
{
	int i;
	cin >> N >> P;
	for (i = 1; i <= N; i++) cin >> h[i];
	i = 1;
	while (i < N)
	{
		if (h[i] >= h[i + 1])
			i++;
		else
			break;
	}
	int l = i, r = N;
	int mid = (l + r) >> 1;
	while (l < N)
	{
		while (l < r)
		{
			if (h[mid] >= h[mid - 1])
				l = mid;
			else
			{
				r = mid;
			}
		}
		sum += min(P, h[l] - h[l - 1]);
	}
	cout << sum << endl;
	system("pause");
	return 0;
}