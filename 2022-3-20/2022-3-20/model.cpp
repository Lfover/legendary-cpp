//大整数,高精度加法 模板
#if 0
#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int N = 1e6 + 10;//更加保险，安全

//C = A + B
vector<int> add(vector<int> &A, vector<int> &B)
{
	vector<int> C;//定义结果
	int t = 0;//进位
	for (int i = 0; i < A.size() || i < B.size(); i++)
	{
		if (i < A.size())
			t += A[i];
		if (i < B.size())
			t += B[i];
		C.push_back(t % 10);
		t /= 10;
	}
	if (t)
		C.push_back(1);
	return C;
}
int main()
{
	string a, b;//用字符串
	vector<int> A, B;
	cin >> a >> b;
	for (int i = a.size() - 1; i >= 0; i--)
		A.push_back(a[i] - '0');
	for (int i = b.size() - 1; i >= 0; i--)
		B.push_back(b[i] - '0');

	auto C = add(A, B);

	for (int i = C.size() - 1; i >= 0; i--)
		cout << C[i];
	return 0;
}
#endif

#if 0
//大整数，高精度减法模板
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//判断是否A >= B
bool cmp(vector<int> &A, vector<int> &B)
{
	if (A.size() != B.size())
		return A.size() > B.size();
	for (int i = A.size() - 1; i >= 0; i--)
		if (A[i] != B[i])
			return A[i] > B[i];
	return true;
}
vector<int> sub(vector<int> &A, vector<int> &B)
{
	vector<int> C;
	for (int i = 0, t = 0; i < A.size(); i++)
	{
		t = A[i] - t;
		if (i < B.size())
			t -= B[i];
		C.push_back((t + 10) % 10);
		if (t < 0)
			t = 1;
		else
			t = 0;
	}
	//前导0去掉
	while (C.size() > 1 && C.back() == 0)
		C.pop_back();
	return C;
}

int main()
{
	string a, b;
	vector<int> A, B;
	cin >> a >> b;
	for (int i = a.size() - 1; i >= 0; i--)
		A.push_back(a[i] - '0');
	for (int i = b.size() - 1; i >= 0; i --)
		B.push_back(b[i] - '0');
	if (cmp(A, B))
	{
		auto C = sub(A, B);
		for (int i = C.size() - 1; i >= 0; i--)
			cout << C[i];
	}
	else
	{
		auto C = sub(B, A);
		cout << "-";
		for (int i = C.size(); i >= 0; i--)
			cout << C[i];
	}
	return 0;
}
#endif
//高精度乘法模板
#if 0
#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> mul(vector<int> &A, int b)
{
	vector<int> C;
	int t = 0;
	for (int i = 0; i < A.size() || t; i++)
	{
		if (i < A.size())
			t += A[i] * b;
		C.push_back(t % 10);
		t /= 10;
	}
	return C;
}

int main()
{
	string a;
	int b;
	cin >> a >> b;

	vector<int> A;
	for (int i = a.size() - 1; i >= 0; i--)
		A.push_back(a[i] - '0');
	auto C = mul(A, b);
	for (int i = A.size() - 1; i >= 0; i--)
		cout << C[i];
	return 0;
}
#endif

//高精度除法
#if 0
#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> div(vector<int> &A, int b, int &r)
{
	vector<int> C;
	r = 0;
	for (int i = A.size(); i >= 0; i --)
	{
		r = r * 10 + A[i];
		C.push_back(r / b);
		r %= b;
	}
	reverse(C.begin(), C.end());
	while (C.size() > 1 && C.back() == 0) C.pop_back();
	return C;
}

int main()
{
	string a;
	int b;
	cin >> a >> b;

	vector<int> A;
	for (int i = a.size() - 1; i >= 0; i--)
		A.push_back(a[i] - '0');
	int r;
	auto C = div(A, b, r);
	for (int i = A.size() - 1; i >= 0; i--)
		cout << C[i];
	cout << endl;
	cout << r << endl;
	return 0;
}
#endif
#if 0
//一维前缀和模板
#include <iostream>
using namespace std;

const int N = 100010;

int n, m;
int a[N], s[N];

int main()
{
	ios::sync_with_stdio(false);//提高cin的速度，不可以在使用scanf了
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i <= n; i++)
		s[i] = s[i - 1] + a[i];//前缀和的初始化
	while (m --)
	{
		int l, r;
		cin >> l >> r;
		cout << s[r] - s[l - 1];//区间和的计算
	}
	return 0;
}
#endif
#if 0
//二维前缀和模板
#include <iostream>
using namespace std;
const int N = 1010;

int n, m, q;
int a[N][N], s[N][N];

int main()
{
	cin >> n >> m >> q;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> a[i][j];
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			s[i][j] = s[i - 1][j] + s[i][j - 1] + a[i][j];//求前缀和
	while (q--)
	{
		int x1, x2, y1, y2;
		cin >> x1 >> x2 >> y1 >> y2;
		cout << s[x2][y2] - s[x1 - 1][y2] - s[x2][y1 - 1] + a[x1 - 1][y1 - 1];//算子矩阵的和
	}
	return 0;
}
#endif

//一维差分模板 
# if 0
#include <iostream>

using namespace std;
const int N = 100010;

int n, m;
int a[N], b[N];

void insert(int l, int r, int c)
{
	b[l] += c;
	b[r + 1] -= c;
}
int main()
{
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i <= n; i++)
		insert(i, i, a[i]);
	while (m--)
	{
		int l, r, c;
		cin >> l >> r >> c;
		insert(l, r, c);
	}
	for (int i = 1; i <= n; i++)
		b[i] += b[i - 1];
	for (int i = 1; i <= n; i++)
		cout << b[i];
	return 0;
}
#endif

#include <iostream>
using namespace std;

const int N = 1010;

int n, m, q;
int a[N][N], b[N][N];
void insert(int x1, int y1, int x2, int y2, int c)
{
	b[x1][y1] += c;
	b[x2 + 1][y1] -= c;
	b[x1][y2 + 1] -= c;
	b[x2 + 1][y2 + 1] += c;
}

int main()
{
	cin >> n >> m >> q;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> a[i][j];
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			insert(i, j, i, j, a[i][j]);
	while (q --)
	{
		int x1, y1, x2, y2, c;
		cin >> x1 >> x2 >> y1 >> y2 >> c;
		insert(x1, y1, x2, y2, c);
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; i++)
			b[i][j] += b[i - 1][j] + b[i][j - 1] - b[i - 1][j - 1];
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cout << b[i][j];
	return 0;
}
