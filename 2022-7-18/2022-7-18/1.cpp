#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;
/*vector<int> find_disappeard_num(vector<int>& nums) {
	vector<int> res;
	int n = nums.size();
	vector<int> temp(n, 0);
	for (int i = 0; i < n; i++)
	{
		temp[nums[i] - 1] = 2;
	}
	for (int i = 0; i < n; i++)
	{
		if (nums[i] == 0)
			res.push_back(nums[i]);
	}
	return res;
}
int main()
{
	return 0;
}*/
class animal
{
public:
	animal(int mname = 1, int mage = 12)
	{
		name = mname;
		age = mage;
	}
	~animal() {}
	 void speak()
	{
		cout << "我是动物" << endl;
	}
	int name;
	int age;

};

class cat : public animal
{
public:
	
	cat(int mname , int mage, string mm)
	{
		name = mname;
		age = mage;
		m = mm;

	}
	~cat() {}
	void speak()
	{
		cout << "我是猫" << endl;
	}
	void ss() {
		cout << "hhahha" << endl;
	}
	int name;
	int age;
	string m;
};
int main() {	
	cat c(1, 2, "1");
	animal* a;
	a = &c;
	a->speak();
	(* a).speak();
	c.speak();
	return 0;
 }