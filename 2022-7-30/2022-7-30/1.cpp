/*
#include <iostream>
#include <vector>
#include <map>
#include <math.h>
#include <algorithm>
using namespace std;

int main()
{
    int n;
    int res = 0;
    cin >> n;
    vector<int> num(n);
    vector<vector<int>> nums(n - 1, vector<int>(2));
    for (int i = 0; i < n; i++)
    {
        cin >> num[i];
    }
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cin >> nums[i][j];
        }
    }
    vector<int> a(n - 1);
    for (int i = 0; i < n - 2; i++)
    {
        int temp = nums[i][1];

        for (int j = i + 1; j < n - 1; j++)
        {
            if (temp == nums[j][1])
            {
                res += num[nums[i][1] - 1];
                num[nums[i][1] - 1] = 0;
            }
        }
    }
    for (int i = 0; i < n - 2; i++)
    {
        int temp = nums[i][1];

        for (int j = i; j < n - 1; j++)
        {
            if (temp == nums[j][1])
            {
                a[i] += num[nums[j][0]];
                num[nums[j][0]] = 0;
            }
        }
    }
    vector<int> b(n - 1);
    for (int i = 0; i < n - 1; i++)
    {
        if (a[i] != 0)
        {
            b.push_back(a[i]);
        }
    }
    int si = b.size();
    sort(b.begin(), b.end());
    int mid = b[si / 2];
    for (int i = 0; i < si; i++)
    {
        res += abs(b[i] - mid);
    }
    cout << res;
    return 0;
}
*/
/*
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> num(n);
    vector<int> nums(n - 1);
    for (int i = 0; i < n; i++)
    {
        cin >> num[i];
    }
    vector<int> res(n);
    int k = 0;
    int temp = 0;
    for(int k = 0; k < n; k ++)
    {
        for (int i = 0; i < n; i++)
        {
            if (i != k)
            {
                nums[temp++] = num[i];
            }

        }
        int count = 0;
        for (int i = 0; i < n - 2; i++)
        {
            for (int j = i + 1; j < n - 1; j++)
            {
                if (nums[i] == nums[j])
                    count++;
            }
        }
        res[k] = count;
        temp = 0;
    }

    for (int i = 0; i < n; i++)
    {
        cout << res[i];
        if (i != n - 1)
            cout << " ";
    }
    return 0;
}
*/

#include <iostream>
#include <vector>
#include <deque>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> num(n);
    deque<int> nums(n);
    vector<int> numss(n);
    for (int i = 0; i < n; i++)
    {
        cin >> num[i];
    }
    int nn = n;
    for (int i = 0; i < n; i++)
    {
        int a = nums.front();
        nums.push_back(a);
        int b = nums.front();
        nums.push_back(b);
        nums.push_front(num[i]);
        if (nn > 2)
        {
            nums[nn - 2] = num[i];
            nn--;
        }
        else
        {
            int nnn = nn;
            nnn = nnn + 1;
            int temp = nnn % n;
            nums[temp] = num[i];
        }

    }
    for (int i = 0; i < n; i++)
    {
        cout << nums[i];
        if (i != n - 1)
            cout << " ";
    }
    return 0;
}