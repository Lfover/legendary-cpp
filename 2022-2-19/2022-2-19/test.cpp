#include <iostream>
#include <vector>
using namespace std;


	void quick_sort(vector<int>& nums, int l, int r)
	{
		if (l >= r) return;
		int x = nums[l], i = l - 1, j = r + 1;
		while (i < j)
		{
			do i++; while (nums[i] < x);
			do j--; while (nums[j] > x);
			if (i < j) swap(nums[i], nums[j]);
		}
		quick_sort(nums, l, j);
		quick_sort(nums, j + 1, r);
	}
	int findKthLargest(vector<int>& nums, int k)
	{
		int size = nums.size();
		quick_sort(nums, 0, size - 1);
		return nums[size - k];

	}

	int main()
	{
		vector<int> nums = { 3, 2, 3, 1, 2, 4, 5, 5, 6 };
		int n = findKthLargest(nums, 4);
			return 0;
	}