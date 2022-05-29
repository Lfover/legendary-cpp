#include <iostream>
#include <string>
using namespace std;

/*
int main()
{
    string s;
    int a = 0, b = 0;
    while (cin >> s)
    {
        int size = s.size();

        int i = 0;
        for (i = 0; i < size; )
        {
            if (s[i] >= 'a' && s[i] <= 'z')
            {
                a += 20;
                i++;
            }
            while (s[i] == ',' || s[i] == '.')
            {
                a += 20;
                i++;
            }
            if (a >= 100)
            {
                a = 0;
                b += 1;
            }
        }
        if (a != 0)
        {
            b += 1;
            a = 0;
        }
    }
    cout << b * 20;
}
*/

int main()
{
    int a, b;
    cin >> a >> b;
    cout << a + b;
    return 0;
}