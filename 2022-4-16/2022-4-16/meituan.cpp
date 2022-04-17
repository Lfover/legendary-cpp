#include <iostream>
#include <math.h>
#include <string>
#include <algorithm>
using namespace std;
const int N = 1010;
int u[N], v[N], w[N];
int minrode;
int main()
{
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++) cin >> u[i];
	for (int i = 0; i < m; i++) cin >> v[i];
	for (int i = 0; i < m; i++) cin >> w[i];

	int i = 0;
	while (i < n)
	{
		if (u[i] != v[i])
		{
			minrode += w[i];
			minrode = min(minrode, w[i]);
		}
		i++;
	}
	cout << minrode << endl;
	return 0;
}