//2DAE07 - Vanden Heede, Pauline - 2019/2020
#include "EnginePCH.h"
#include "Exception.h"

Princess::Exception::Exception(const std::string& message)
	: m_Message{ message }
{
}

const char* Princess::Exception::what() const
{
	return m_Message.c_str(); // return internal cstring
}
