#pragma once

#include <string>
#include <sstream>

class pstring : public std::wstring
{
public:
    pstring(): std::wstring() {}

    template<typename T>
    pstring(const T v): std::wstring(v) {}

    template<typename T>
    pstring& operator<<(const T s)
	{
		std::wstringstream stream;
		stream << *this;
		stream << s;
		*this = stream.str();
		return *this;
    }
	
	pstring& operator+(const unsigned int i) // literally not that hard to do in vanilla - string(i) + myString
	{
		std::wstringstream stream;
		stream << *this;
		stream << i;
		*this = stream.str();
		return *this;
	}
};
