#ifndef SWX_JSON_UTILS_H
#define SWX_JSON_UTILS_H

#include <exception>
#include <strings.h>

namespace swxJson {

#define JSON_ERROR_MSG(Err, message)	Err(__FILE__, __FUNCTION__, __LINE__, (message))
#define JSON_ERROR_FMT(Err, ...)		Err(__FILE__, __FUNCTION__, __LINE__, JsonError::format(__VA_ARGS__))

	class JsonError: public std::exception
	{
		const char* const _filename;
		const char* const _function;
		int32_t _lineNumber;
		std::string _message;
		std::string _what;

	public:
		JsonError(const char *filename, const char* function, int32_t lineNumber, const std::string& message = "");
		virtual ~JsonError() noexcept {}

		virtual const char* what() const noexcept { return _what.c_str(); }

		const char* filename() const noexcept { return _filename; }
		const char* function() const noexcept { return _function; }
		int32_t lineNumber() const noexcept { return _lineNumber; }
		const std::string& message() const noexcept { return _message; }

		static std::string format(const char *fmt, ...); 
	};

#define DEFINE_ERROR(BASE, DERIVED)		\
class DERIVED: public BASE {			\
public:									\
	DERIVED(const char *filename, const char*function, int32_t lineNumber, const std::string& message = ""): \
	BASE(filename, function, lineNumber, message) {} 	\
};

	//===================================//

	class CharsChecker
	{
	private:
		bool _map[256];

	public:
		CharsChecker(const unsigned char *targets)
		{
			bzero(_map, sizeof(_map));
			for (unsigned char *p = (unsigned char *)targets; *p; p++)
				_map[*p] = true;
		}
		CharsChecker(const unsigned char *targets, int len)
		{
			bzero(_map, sizeof(_map));
			for (int i = 0; i < len; i++)
				_map[targets[i]] = true;
		}
		CharsChecker(const std::string& targets): CharsChecker((const unsigned char*)targets.data(), (int)targets.length()) {}

		inline bool operator[] (unsigned char c)
		{
			return _map[c];
		}
	};
}

#endif
