#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int n, x;
    cin >> n >> x;
    vector<int> num(n);
    for (int i = 0; i < n; i++)
    {
        cin >> num[i];
    }
    int ma = num[0];
    int mi = num[0];
    for (int i = 0; i < n; i++)
    {
        ma = max(ma, num[i]);
        mi = min(mi, num[i]);
    }
    if (ma - mi <= 2 * x)
    {
        cout << 0;
        return 0;
    }
    else {
        cout << 8;
        return 0;
    }
    return 0;
}