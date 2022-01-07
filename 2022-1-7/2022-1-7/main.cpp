#include <iostream>
using namespace std;
//¼Ó·¨
inline int Add(int left, int right)
	{
		return left + right;
	}
int main()
{
	int a = 10;
	int b = 20;

	int c = 0;
	c = Add(a, b);
	Add(a, b);
	Add(a, b);
	Add(a, b);
	Add(a, b);
	Add(a, b);
	Add(a, b);
	Add(a, b);
	cout << c << endl;
	return 0;
}