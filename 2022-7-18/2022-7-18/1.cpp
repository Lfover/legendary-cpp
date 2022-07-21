#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
vector<int> find_disappeard_num(vector<int>& nums) {
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
}