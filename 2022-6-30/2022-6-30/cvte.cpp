#include <iostream>
#include <vector>
using namespace std;

double MyFunc(const std::vector<int>& data)
{
	int n = data.size();
	if (n % 2 == 0)
	{
		return ((double)data[n / 2] + (double)data[n / 2 - 1]) / 2;
	}
	else
	{
		return (double)data[n / 2];
	}
}
int main()
{
	const vector<int> data = {1, 2};
	double x = MyFunc(data);
	cout << x << endl;
	return 0;
}