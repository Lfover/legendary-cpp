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
#if 0
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

# endif
	//函数指针变量

	//void* (*pFun)(size_t size);
	////pF是一个类型
	//typedef void* (*pF)(size_t size);
	////所以decltype的用法就是推导出函数的类型
	//typedef decltype(GetMemory) pF;
	//pF fun;
	/*
	* fun:是函数的名字，也是函数的地址
	* 函数也是有类型的，void* _cdecl(size_t)   
	* 函数指针类型：void* (*_cdecl)(size_t)
	* 函数指针变量：void* (*p_cdecl)(size_t);p是函数指针变量，可以指向任意的返回值为void* 且参数是size_t类型的函数
	* decltype(fun)推演出来的是函数的类型
	* decltype(&fun)推演出来的是函数指针的类型
	* 
	*/
	//int main()
	//{
	//	cout << typeid(CF).name() << endl;
	//	cout << typeid(CPPF).name() << endl;
	//	system("pause");
	//	return 0;
	//}
#if 0
#include <iostream>
#include <string>
using namespace std;
class Student;
class Person
{
public:
	Person() { ++_count; }
protected:
	string _name;
public:
	static int _count;
};
int Person::_count = 0;//设置_count的值为0
class Student : public Person
{
protected:
	int _stuNo;
};	
class Graduate : public Student
{
protected:
	string _sem;//研究项目
};
void test()
{
	Student s1;//创建Student类的对象，先调用基类Person的构造函数，_count加一， _count = 1;
	Student s2;//_count = 2
	Student s3;//_count = 3
	Graduate s4;//_count = 4
	cout << "人数" << Person::_count << endl;
	Student::_count = 0;//再将静态变量_count的值变为0；
	cout << "人数" << Person::_count << endl;
}
int main()
{
	test();
	system("pause");
	return 0;
}
#endif
//#include <iostream>
//#include <string>
//using namespace std;
//class Person
//{
//public:
//	string _name;//姓名
//};
//class Student : virtual public Person
//{
//public:
//	int _stuNo;//学生学号
//};
//class Teacher : virtual public Person
//{
//public:
//	int _id;//职工编号
//};
//class Graduate : public Student, public Teacher
//{
//public:
//	string _sem;//研究项目
//};
//int main()
//{
//	Graduate d;
//	d.Student::_name = 1;
//	d.Teacher::_name = 2;
//	d._stuNo = 3;
//	d._id = 4;
//	d._sem = 5;
//	system("pause");
//	return 0;
//}
//class Person
//{
//protected:
//	string _name;//名字
//	string _face;//脸
//};
//class Student : public Person
//{
//public:
//	void eat() { cout << "吃美食" << endl; }
//};
//
//class Person
//{
//protected:
//	string _name;//名字
//	string _face;//脸
//};
//class Student
//{
//protected:
//	double height;//身高
//	double weight;//体重
//	Person _p;
//};

//class Person
//{
//public:
//	virtual void fun1()
//	{
//		cout << "Person::fun1()" << endl;
//	}
//	virtual void fun2()
//	{
//		cout << "Person::fun2()" << endl;
//	}
//	void fun3()
//	{
//		cout << "Person::fun3()" << endl;
//	}
//private:
//	int _a = 1;
//};
//class Student : public Person
//{
//public:
//	virtual void fun1()
//	{
//		cout << "Student::fun()" << endl;
//	}
//	virtual void fun()
//	{
//		cout << "fun()" << endl;
//	}
//private:
//	int _b = 2;
//};
//int main()
//{
//	Person p;
//	Student s;
//	system("pause");
//	return 0;
//}

//写一个快排
#include <iostream>
#include <string>
#include <vector>
using namespace std;
//void quck_sort(vector<int>& num, int l, int r)
//{
//	int n = num.size();
//	if (l >= r) return;
//	int tem = num[0];
//	while (l < r)
//	{
//		if (num[r] > tem)
//		{
//			r--;
//			continue;
//		}
//		else
//		{
//			num[l] = num[r];
//			l++;
//		}
//		if (num[l] < tem)
//		{
//			l++;
//			continue;
//		}
//		else
//		{
//			num[r] = num[l];
//			r--;
//		}
//	}
//	num[l] = tem;
//	quck_sort(num, 0, l - 1);
//	quck_sort(num, r + 1, n - 1);
//
//}
void quick_sort(int q[], int l, int r)
{
	//递归的终止情况
	if (l >= r) return;
	//第一步：分成子问题
	int i = l - 1, j = r + 1, x = q[l + r >> 1];
	while (i < j)
	{
		do i++; while (q[i] < x);
		do j--; while (q[j] > x);
		if (i < j) swap(q[i], q[j]);
	}
	//第二步：递归处理子问题
	quick_sort(q, l, j), quick_sort(q, j + 1, r);
	//第三步：子问题合并.快排这一步不需要操作，但归并排序的核心在这一步骤
}
int num[5] = {3, 2, 5, 1, 4};
int main()
{
	
	quick_sort(num, 0, 4);


}
