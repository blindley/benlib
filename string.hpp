#ifndef BEN_STRING_717
#define BEN_STRING_717

#include <boost/lexical_cast.hpp>

namespace ben
{
	inline
	std::string BuildString()
	{
		return "";
	}
	
	template<typename T, typename... Args>
	std::string BuildString(const T & arg1, Args... args)
	{
		return boost::lexical_cast<std::string>(arg1)
		     + BuildString(args...);
	}
}

#endif // #ifndef BEN_STRING_717
