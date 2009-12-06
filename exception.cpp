#include <iostream>
#include "exception.h"

/////////////////////////////////////////////////////////////////////////////
/// @file exception.cpp
/// @author Doug Kelly - CS153 Sec. B
/// @brief Exception class/error handling code.
/////////////////////////////////////////////////////////////////////////////

Exception::Exception(int _error_code, const std::string& _error_message)
{
	m_error_code = _error_code;
	m_error_message = std::string(_error_message);
}

int Exception::error_code()
{
	return m_error_code;
}

std::string Exception::error_message()
{
	return m_error_message;
}
