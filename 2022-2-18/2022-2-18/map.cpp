#include <iostream>
#include <map>
#include <string>
using namespace std;



void TestMap()
{
	map<int, string> m1;
	//�б�Ĺ��췽ʽ
	map<string, string> m2{ { "orange", "����" }, { "apple", "ƻ��" }, { "peach", "����" } };
	//������ֻҪ����������������Ԫ�������б���������������ʹ��
	//����������������б���
	//std::map<std::string, std::string>::iterator it = m2.begin(); 
	auto it = m2.begin();
	while(it != m2.end())
	{
		cout << "[" << (*it).first << "," << it->second << "]" << endl;
		++it;
	}
	cout << endl;
	//���÷�����������б���
	auto rit = m2.rbegin();
	while (rit != m2.rend())
	{
		cout << "[" << rit->first << "," << rit->second << "]" << endl;
		++rit;
	}
	cout << endl;
	//��Χfor
	for (auto& e : m2)
	{
		cout << "[" << e.first << "," << e.second << "]" << endl;
	}
	cout << endl;
}

void TestMap2()
{
	map<string, string> m;
	//��Ҫ��map�в���Ԫ��
	m.insert(pair<string, string>("orange", "����"));
	m.insert(make_pair("apple", "ƻ��"));
	auto ret = m.insert(make_pair("peach", "����"));
	//ret:<itertor, bool>
	cout << (*(ret.first)).first << endl;
	cout << (*(ret.first)).second << endl;
	cout << ret.second << endl;

	cout << m.size() << endl;
	//m[key]�������key�����õ�value
	cout << m["apple"] << endl;
	//[]Ҳ������������
	m["banana"] = "�㽶";
	cout << m["banana"] << endl;
	ret = m.insert(make_pair("peach", "����"));
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
	//top-k���⣬�õ����ȼ�����
	string Fruits[] = { "ƻ��", "ƻ��", "�㽶", "�㽶", "����", "����", "����", "⨺���", "ƻ��" };
	//ͳ��ÿ��ˮ�����ֵĴ���
	map<string, size_t> m;
	for (auto& e : Fruits)
		m[e] ++;
	//ͨ�����ȼ�������tip-k
	priority_queue<pair<string, size_t>, vector<pair<string, size_t>>, Com> p;
	//�����Ҫǰk������Ԫ�أ�Ӧ�ý���һ��С�ѣ�ǰk��Ԫ�ؽ���С��
	int k = 0;
	for (auto& e : m)
	{
		if (k < 3)
		{
			//��ǰk��Ԫ�ؽ���һ��С��
			p.push(e);
			k++;
		}
		else
		{
			//ʣ���ˮ������ÿ����Ѷ��Ƚϣ��ȶѶ��󣬼��滻�Ѷ���С������
			if (e.second > p.top().second)
			{
				p.pop();
				p.push(e);
			}
		}
	}
	//������������ˮ����������������ֻ������
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
	//set�����ã�ȥ�أ�����
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