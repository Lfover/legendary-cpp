#include <iostream>
using namespace std;

#if 0
template<class T>
T Add(const T& left, const T& right)
{
	return left + right;
}

int main()
{
	return 0;
}
#endif

int g_a = 10;
int g_b = 20;


namespace bite
{
	//非类型的模板参数
	template<class T, size_t N = g_a + g_b>
	class array
	{
	public:
		array()
			: _size(0)
		{}
	private:
		T _array[N];
		size_t _size;
	};

}

int main()
{
	bite::array<int, 10> arr;
	return 0;
}