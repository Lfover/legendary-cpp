/*
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    long long count = 0;//ÊýÁ¿
    long long n, k;
    cin >> n >> k;
    vector<long long> num(n);
    for (int i = 0; i < n; i++)
    {
        cin >> num[i];
    }
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            long long temp = num[i] * num[j];
            if (temp >= k)
                count++;
        }
    }
    cout << count * 2 << endl;
    return 0;
}
*/
#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int count = 0;
    vector<int> num(n);
    for (int i = 0; i < n - 1; i++)
    {
        cin >> num[i];
    }
    map<int, int> map1;

    for (int i = 1; i <= n; i++)
    {
        map1[num[i - 1]] = i + 1;
    }
    for (map<int, int>::iterator it = map1.begin(); it != map1.end();)
    {
        int temp = it->second;
        count++;
        it++;
        for (map<int, int>::iterator i = it; i != map1.end(); )
        {
            if (i->first == temp)
                map1.erase(i++);
            i++;
        }
    }
    cout << count << endl;
    return 0;
}