#include <iostream>
#include <Windows.h>

using namespace std;

template <typename T>
T Add(T& a, T& b)
{
	return a + b;
}
int main()
{
	int a = 2;
	int b = 3;
	cout << Add(a, b) << endl;
	system("pause");
	return 0;
}