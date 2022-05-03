#include <iostream>
using namespace std;
class String
{
public:
	String(const char* str = "")
	{
		if (nullptr == str) str = "";
		_str = new char[strlen(str) + 1];
		strcpy(_str, str);
	}
	~String()
	{
		if (_str)
		{
			delete[] _str;
			_str = nullptr;
		}
	}
	String(const String& s)
		: _str(new char[strlen(s._str) + 1])
	{
		strcpy(_str, s._str);
	}
	String& operator=(const String& s)
	{
		if (this != &s)
		{
			char* temp = new char[strlen(s._str) + 1];
			strcpy(temp, s._str);
			delete[] _str;
			_str = temp;
		}
		return *this;
	}
	String& operator=(String&& s)
	{
		delete[] _str;
		_str = s._str;
		s._str = nullptr;
		return *this;
	}
	String operator+(const String& s)const
	{
		char* str = new char[strlen(_str) + strlen(s._str) + 1];
		strcpy(str, _str);
		strcat(str, s._str);
		String ret(str);
		delete[] str;
		return ret;
	}
	String(String&& s)
		: _str(s._str)
	{
		s._str = nullptr;
	}
private:
	char* _str;
};