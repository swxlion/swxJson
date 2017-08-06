#include <stdarg.h>
#include <sstream>
#include "swxJsonUtils.h"

using namespace swxJson;

JsonError::JsonError(const char *filename, const char* function, int32_t lineNumber, const std::string& message):
	_filename(filename), _function(function), _lineNumber(lineNumber), _message(message)
{
	std::stringstream ss;
	ss << "Exception";

	if (_function && _function[0])
		ss << " at " << _function;

	if (_filename && _filename[0])
		ss << " in " << _filename << ':' << _lineNumber;
	
	if (!_message.empty())
		ss << " --- " << _message;

	_what = ss.str();
}

std::string JsonError::format(const char *fmt, ...)
{
	if (fmt)
	{
		va_list ap; 
		va_start(ap, fmt);
		char buf[1024];
		vsnprintf(buf, sizeof(buf), fmt, ap);
		va_end(ap);
		return std::string(buf);
	}

	return std::string();
}
