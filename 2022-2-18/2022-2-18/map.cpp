#include <iostream>
#include <map>
#include <string>
using namespace std;



void TestMap()
{
	map<int, string> m1;
	//列表的构造方式
	map<string, string> m2{ { "orange", "橘子" }, { "apple", "苹果" }, { "peach", "桃子" } };
	//迭代器只要是用力啊对容器的元素来进行遍历，配合算吗进行使用
	//采用正向迭代器进行遍历
	//std::map<std::string, std::string>::iterator it = m2.begin(); 
	auto it = m2.begin();
	while(it != m2.end())
	{
		cout << "[" << (*it).first << "," << it->second << "]" << endl;
		++it;
	}
	cout << endl;
	//采用反向迭代器进行遍历
	auto rit = m2.rbegin();
	while (rit != m2.rend())
	{
		cout << "[" << rit->first << "," << rit->second << "]" << endl;
		++rit;
	}
	cout << endl;
	//范围for
	for (auto& e : m2)
	{
		cout << "[" << e.first << "," << e.second << "]" << endl;
	}
	cout << endl;
}

void TestMap2()
{
	map<string, string> m;
	//需要像map中插入元素
	m.insert(pair<string, string>("orange", "橘子"));
	m.insert(make_pair("apple", "苹果"));
	auto ret = m.insert(make_pair("peach", "桃子"));
	//ret:<itertor, bool>
	cout << (*(ret.first)).first << endl;
	cout << (*(ret.first)).second << endl;
	cout << ret.second << endl;

	cout << m.size() << endl;
	//m[key]结果：与key锁对用的value
	cout << m["apple"] << endl;
	//[]也可以用来插入
	m["banana"] = "香蕉";
	cout << m["banana"] << endl;
	ret = m.insert(make_pair("peach", "桃子"));
	//ret:<itertor, bool>
	cout << (*(ret.first)).first << endl;
	cout << (*(ret.first)).second << endl;
	cout << ret.second << endl;
}
#include <queue>
#include <vector>
#include <set>
#if 0
class Com
{
public:
	bool operator()(const pair<string, size_t>& left, const pair<string, size_t>& right)
	{
		return left.second > right.second;
	}
};

void TestMap()
{
	//top-k问题，用到优先级队列
	string Fruits[] = { "苹果", "苹果", "香蕉", "香蕉", "辣条", "辣条", "橘子", "猕猴桃", "苹果" };
	//统计每个水果出现的次数
	map<string, size_t> m;
	for (auto& e : Fruits)
		m[e] ++;
	//通过优先级队列找tip-k
	priority_queue<pair<string, size_t>, vector<pair<string, size_t>>, Com> p;
	//如果需要前k个最大的元素，应该建立一个小堆，前k个元素建立小堆
	int k = 0;
	for (auto& e : m)
	{
		if (k < 3)
		{
			//用前k个元素建立一个小堆
			p.push(e);
			k++;
		}
		else
		{
			//剩余的水果次数每次与堆顶比较，比堆顶大，即替换堆顶，小，舍弃
			if (e.second > p.top().second)
			{
				p.pop();
				p.push(e);
			}
		}
	}
	//数量最多的三个水果都在这个堆里，堆中只有三个
	//vector<string> vret;
	//while (!p.empty()) 
	//{
	//	vret.push_back(p.top().first);
	//	p.pop();
	//}
	set<string> vret;
	while (!p.empty())
	{
		vret.insert(p.top().first);
		p.pop();
	}
	for (auto& e :  vret)
	{
		cout << e << " ";
	}
	cout << endl;
}
int main()
{
	//TestMap();
	TestMap2();
	return 0;
}
#endif
int main()
{
	//set的作用，去重，排序
	int arrary[] = { 1, 2, 3, 4, 5, 0, 9, 6, 2, 5, 1, 5 };
	set<int> s;
	for (auto e : arrary)
		s.insert(e);
	cout << s.size() << endl;
	auto it = s.begin();
	while (it != s.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
	it = s.find(5);
	if (it != s.end())
		s.erase(it);
	s.erase(0);
	for (auto e : s)
	{
		cout << e << " ";
	}
	cout << endl;
	s.clear();
	cout << s.empty() << endl;
	return 0;
}