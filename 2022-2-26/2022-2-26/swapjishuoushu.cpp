#include <iostream>
#include <vector>
using namespace std;


	vector<int> exchange(vector<int>& nums) {
		int size = nums.size() - 1;
		for (int i = 0, j = size; i < size, j > 0;){
			while (nums[i] % 2 == 0){
				swap(nums[i], nums[j]);
				j--;
			}
			i++;
		}
		return nums;
	}
int main()
{
	vector<int> nums = { 1, 2, 3, 4 };
	exchange(nums);
	return 0;
}