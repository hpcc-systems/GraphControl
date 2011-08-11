#include "Platform.h"

#include "util.h"

#include <boost/lexical_cast.hpp>

std::wstring StringToWString(const std::string& s)
{
	std::wstring temp(s.length(), L' ');
	std::copy(s.begin(), s.end(), temp.begin());
	return temp;
}

std::string WStringToString(const std::wstring& s)
{
	std::string temp(s.length(), ' ');
	std::copy(s.begin(), s.end(), temp.begin());
	return temp;
}

unsigned int StringToUInt(const std::wstring& s)
{
	return boost::lexical_cast<unsigned int>(s);
}

unsigned int StringToUInt(const std::string& s)
{
	return boost::lexical_cast<unsigned int>(s);
}

std::wstring UIntToWString(unsigned int i)
{
	return boost::lexical_cast<std::wstring>(i);
}

std::string UIntToString(unsigned int i)
{
	return boost::lexical_cast<std::string>(i);
}
