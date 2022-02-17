
#if 0
#include <iostream>
using namespace std;

class Person
{
public:

protected:
	string _name;
	string _gender;
	int _age;
};

class Student : public Person
{ 

};

int main()
{
	return 0;

}
#endif

#include <iostream>
#include <vector>
using namespace std;



/*
int hammingDistance(int x, int y) {
	//首先异或，得到的结果就是位置对应不同的位置，置为1
	//ret用来记录数量
	int s = x ^ y, ret = 0, tem = 1;
	while (s & tem) {
		ret += 1;
		tem <<= 1;
	}
	return ret;
}
*/

//
//vector<int> countBits(int n) {
//	vector<int> res(n + 1, 0);
//	for (int i = 0; i <= n; i++)
//	{
//		int tem = 0, temp = i;
//		while (temp)
//		{
//			tem += temp & 1;
//			temp >>= 1;
//		}
//		res[i] = tem;
//	}
//	return res;
//}


int main()
{

	vector<int> a = { 1, 2, 3, 4, 5 };
	int n = a.size();
	return 0;
}