#ifndef BEN_IO_856
#define BEN_IO_856

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

namespace ben
{
	template<typename IT>
	void PrintRange(
	    std::ostream & os, IT first, IT last, const char * sep = "\n")
	{
		if (first == last)
		    return;
		os << *first;
		++first;
		while (first != last)
		{
			os << sep << *first;
			++first;
		}
	}
	
	template<typename C>
	void PrintAll(
	    std::ostream & os, const C & cont, const char * sep = "\n")
	{
		PrintRange(os, std::begin(cont), std::end(cont), sep);
	}
	
	// Prints directly to a string
	template<typename IT>
	PrintRange(
	    std::string & str, IT first, IT last, const char * sep = "\n")
	{
		std::ostringstream os;
		PrintRange(os, first, last, sep);
		str += os.str();
	}
	
	template<typename C>
	void PrintAll(
	    std::string & str, const C & cont, const char * sep = "\n")
	{
		PrintRange(str, std::begin(cont), std::end(cont), sep);
	}
	
	inline
	std::string LoadFileAsString(const std::string & fn)
	{
		std::ifstream fin(fn);
		std::ostringstream os;
		os << fin.rdbuf();
		return os.str();
	}
	
	inline
	std::vector<std::string> LoadFileLines(const std::string & fn)
	{
		std::ifstream fin(fn);
		std::vector<std::string> v;
		for (std::string line; std::getline(fin, line); )
		    v.push_back(line);
		return v;
	}
}

#endif // #ifndef BEN_IO_856
