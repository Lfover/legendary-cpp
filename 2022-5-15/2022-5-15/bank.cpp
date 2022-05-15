/*
#include <iostream>
#include <string>
using namespace std;
int N = 0;
int tem;
char c;
string s;
int res = 0;
int main()
{

    cin >> N;
    while(N)
    {
        tem = N % 16;
        if (tem < 10)
        {
            c = tem + '0';
        }
        else
        {
            c = tem + 'A' - 10;
        }
        s = c + s;
        N = N / 16;
    }
    if (s == "")
        cout << 0 << endl;
    else
    {
        int n = s.size();
        for (int i = 0; i < n; i++)
        {
            if (s[i] >= 'A' && s[i] <= 'F')
                res++;
        }
    }
    cout << res << endl;
    return 0;
}
*/
/*
#include <iostream>
#include <vector>
using namespace std;
const int N = 100010;
vector<int> f;
int n, x, y;
int main()
{
    cin >> n >> x >> y;
    for (int i = 0; i < n; i++)
    {
        int tem = 0;
        cin >> tem;
        f.push_back(tem);
    }
        for (int i = 0; i < n; i++)
        {
            int a = 1, b = 1;
            if (i + y > f.size())y = f.size() - i;
            while (b <= y)
            {
                if (f[i] < f[i + b])
                    b++;
                else break;
            }
            if (i <= x) x = i;
            else x = i;
            while (a <= x)
            {
                if (f[i] < f[i - a])
                    a++;
                else break;
            }
            if (x <= a && y <= b)
            {
                cout << i + 1 << endl;
                return 0;
            }
        }
    return 0;
}
*/

#include <iostream>
#include <string>
using namespace std;
int n;
int k;
char x;
string s;
int tem;
int res;
string str;
int main()
{
    cin >> n >> k >> x;
    cin >> s;
    
    for (int i = 0; i < n; i++)
    {
        string s1 = (str);
        for (int j = i; j < n; j++)
        {
            char c = s[j];
            s1 += c;
            for (int q = 0; q < s1.size(); q++)
            {
                if (s1[q] == x)
                    tem++;
            }
            if (tem >= k)
            {
                res++;
                break;
            }
        }
    }
    cout << res << endl;
    return 0;
}