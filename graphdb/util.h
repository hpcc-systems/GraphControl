#pragma once

#include "Unknown.h"

GRAPHDB_API std::wstring StringToWString(const std::string& s);
GRAPHDB_API std::string WStringToString(const std::wstring& s);

GRAPHDB_API unsigned int WStringToUInt(const std::wstring& s);
GRAPHDB_API unsigned int StringToUInt(const std::string& s);

GRAPHDB_API std::wstring UIntToWString(unsigned int i);
GRAPHDB_API std::string UIntToString(unsigned int i);
