#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    vector<int> num;
    for (int i = 0; i < 4; i++)
    {
        int a = 0;
        cin >> a;
        num.push_back(a);
    }
    int n = num.size();
    int ma = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            int height = min(num[i], num[j]);
            int weight = j - i;
            ma = max(ma, height * weight);
        }
    }
    cout << ma;
    return 0;
}