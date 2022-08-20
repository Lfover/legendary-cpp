#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;
double goodgrade(vector<double>& pre, vector<double>& gra, int n, int m)
{
    double good = 0.0;
    for (int i = 0; i < n; i++)
    {
        good += pre[i] * gra[i] / 100;
    }
    if (m == 0)
    {
        return good;
    }
    vector<double> temp(n);
    for (int i = 0; i < n; i++)
    {
        temp[i] = gra[i] * (100 - pre[i]) / 100;
    }
    sort(temp.begin(), temp.end());
    while (m--)
    {
        good += temp[--n];
    }
    return good;
}
int main()
{
    int n, m;
    cin >> n >> m;
    vector<double> precent(n);//做对概率
    vector<double> grade(n);//每一题分值
    for (int i = 0; i < n; i++)
    {
        cin >> precent[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> grade[i];
    }
    double res = goodgrade(precent, grade, n, m);
    cout << res << setprecision(2);
    return 0;
}