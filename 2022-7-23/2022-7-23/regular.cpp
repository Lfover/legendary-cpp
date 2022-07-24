/*#include <iostream>
#include <iterator>
#include <string>
#include <regex>

int main()
{
	std::string s = "Some people, when confronted with a problem, think "
        "\"I know, I'll use regular expressions.\" "
        "Now they have two problems.";
    std::regex self_regex("REGULAR EXPRESSIONS", std::regex_constants::ECMAScript | std::regex_constants::icase);
    if (std::regex_search(s, self_regex)) {
        std::cout << "Text contains the phrase 'regular expressions'\n";
    }

    std::regex word_regex("(\\w+)");
    auto words_begin = std::sregex_iterator(s.begin(), s.end(), word_regex);
    auto words_end = std::sregex_iterator();

    std::cout << "Found "
              << std::distance(words_begin, words_end)
              << " words\n";

    const int N = 6;
    std::cout << "Words longer than " << N << " characters:\n";
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        std::string match_str = match.str();
        if (match_str.size() > N) {//找到所有字符串长度大于6的
            std::cout << "  " << match_str << '\n';
        }
    }

    std::regex long_word_regex("(\\w{1,})");
    std::string new_s = std::regex_replace(s, long_word_regex, "[$&]");
    std::cout << new_s << '\n';
}*/
/*
#include <iostream>
#include <vector>
using namespace std;
const int PI = 3.1415927;
double mycos(double x)
{
    double sum = 1, x_pow = 1, item;
    int n = 0, fact = 1, sign = -1;

    fact = fact * (n + 1) * (n + 2);
    item = x_pow / fact * sign;
    x_pow *= x * x;
    sum += item;
    sign = -sign;
    n += 2;
    return sum;
}
int main()
{
    int N = 0; 
    cin >> N;
    vector<int> num(N, 0);
    vector<int> res(N, 0);
    for (int i = 0; i < N; i++)
    {
        int x = 0;
        cin >> x;
        num[i] = x;
    }
    for (int i = 0; i < N; i++)
    {
        res[i] = num[i] * (0.5 * (1 - mycos(2 * PI * i / N)));
    }
    for (int i = 0; i < N; i++)
    {
        cout << (int)res[i] << " ";
    }
    return 0;
}
*/
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;
double dis(double x1, double y1, double x2, double y2)
{
    return (sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
}
int main()
{
    int N = 0;
    cin >> N;
    int res = 0;
    vector<double> num(N);
    for (int i = 0; i < 2 * N; i++)
    {
        double x = 0;
        cin >> x;
        num[i] = x;
    }
    for (int i = 0; i < 2 * N - 4; i += 2)
    {
        for (int j = 2; j < 2 * N - 2; j += 2)
        {
            for (int k = 4; k < 2 * N; k += 2)
            {
                double x1x2 = dis(num[i], num[i + 1], num[j], num[j + 1]);
                double x1x3 = dis(num[i], num[i + 1], num[k], num[k + 1]);
                double x2x3 = dis(num[j], num[j + 1], num[k], num[k + 1]);
                if ((x1x2 * x1x2 + x1x3 * x1x3 == x2x3 * x2x3) || (x1x2 * x1x2 + x2x3 * x2x3 == x1x3 * x1x3) || (x1x3 * x1x3 + x2x3 * x2x3 == x1x2 * x1x2))
                {
                    res++;
                }
            }
        }
    }
    cout << res << endl;
    return 0;
}