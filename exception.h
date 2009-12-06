#ifndef EXCEPTION_H
#define EXCEPTION_H

/////////////////////////////////////////////////////////////////////////////
/// @file exception.h
/// @author Doug Kelly - CS153 Sec. B
/// @brief Generic exception handling class header.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
/// @class Exception
/// @brief Generic exception storage/handling class.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
/// @fn error_code
/// @brief Return numeric error code associated with exception
/// @pre none
/// @post none
/// @param none
/// @return int of error code (from when Exception was created)
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
/// @fn error_message
/// @brief Return string error message associated with exception
/// @pre none
/// @post none
/// @param none
/// @return string of error message (from when Exception was created)
/////////////////////////////////////////////////////////////////////////////

class Exception
{
	public:
		Exception(int _error_code, const std::string& _error_message);
		int error_code();
		std::string error_message();
	private:
		int m_error_code;
		std::string m_error_message;
};

#endif

