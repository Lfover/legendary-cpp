#include <iostream>
#include <string>

using namespace std;

//int main()
//{
//	string s1;
//	string s2("hello");
//	string s3(10, 'a');
//	string s4(s2);
//	string s5(s2, 0, 3);
//	string s6("world", 4);
//	cout << s1 << endl;
//	cout << s2 << endl;
//	cout << s3 << endl;
//	cout << s4 << endl;
//	cout << s5 << endl;
//	cout << s6 << endl;
//
//	return 0;
//}

int main()
{
	string s("hello world");
	cout << s[0] << endl;
	s[0] = 'H';
	cout << s << endl;
	return 0;
}