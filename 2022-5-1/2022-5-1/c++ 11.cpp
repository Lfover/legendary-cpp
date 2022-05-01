#include <iostream>
#include <initializer_list>
using namespace std;
#if 0
namespace bite
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
			vector()
				: _start(nullptr)
				, _finish(nullptr)
				, _endofstorage(nullptr)
			{}
			vector(initializer_list<T> L)
				:_start(new T[L.size()])
				, _finish(_start)
			{
				for (auto& e : L)
				{
					*_finish++ = e;
				}
				_endofstorage = _finish;
			}
			vector<T>& operator=(const vector<T>& v)
			{
				if (this != &v)
				{
					//完成赋值操作
				}
			}
			vector<int>& operator=(initializer_list<T> L)
			{
				//完成赋值的操作

				return *this;
			}
			~vector()
			{
				if (_start) 
				{
					delete[] _start;
					_start = _finish = _endofstorage = nullptr;
				}
			}
	private:
		iterator _start;
		iterator _finish;
		iterator _endofstorage;
	};
	
}
int main()
{
	bite::vector<int> v1;
	bite::vector<int> v2 = { 4, 5, 6, 7 };
	v2 = { 1, 2, 3, 4 };
	system("pause");
	return 0;
}
#endif
#if 0
#include <map>
#include <string>
int main()
{
	auto a = 10;

	std::map<std::string, std::string> m;
	//需要对map进行遍历

}
#endif

#include <iostream>
#include <vector>
using namespace std;
void quck_sort(vector<int>& num)
{	
	int left = 0, right = num.size() - 1;
	while (left < right)
	{
		int tem = num[0];
		if (num[left] <= tem) left++;

		if (num[right] >= tem) right--;

		if (left < right && num[left] > tem && num[right] < tem)
		{
			swap(num[left], num[right]);
			num[left + 1] = tem;
		}
	}
}

int main()
{
	vector<int> num = { 2, 4, 1, 3, 7, 5 };
	quck_sort(num);
	system("pause");
	return 0;

}
