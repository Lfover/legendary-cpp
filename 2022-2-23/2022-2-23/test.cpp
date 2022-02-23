#include <iostream>
#include <vector>
using namespace std;


int reversePairs(vector<int>& nums) {
		int left = 0, right = 1;
		int size = nums.size() - 1;
		int count = 0;
		if (size == 0 || size == 1) return 0;
		for (left = 0; left <= size - 1; left++){
			for (right = 1; right <= size; right++){
				if (nums[left] > nums[right])
					count++;
				else
					continue;
			}
		}
		return count;
}
int main()
{
	vector<int> nums = { 7, 5, 6, 4 };
	reversePairs(nums);
	return 0;


}