#ifndef BEN_NUMBER_TO_NAME_604
#define BEN_NUMBER_TO_NAME_604

#include <string>
#include <boost/algorithm/string.hpp>
#include <ben/container_algo.hpp>

namespace ben {
	
	namespace NumberToName_Helpers
	{

		inline std::string HandleDigit(unsigned int n)
		{
			switch(n)
			{
				case 1: return " one ";
				case 2: return " two ";
				case 3: return " three ";
				case 4: return " four ";
				case 5: return " five ";
				case 6: return " six ";
				case 7: return " seven ";
				case 8: return " eight ";
				case 9: return " nine ";
			}
			return "";
		}

		inline std::string HandleTeens(unsigned int n)
		{
			switch(n)
			{
				case 10: return " ten ";
				case 11: return " eleven ";
				case 12: return " twelve ";
				case 13: return " thirteen ";
				case 14: return " fourteen ";
				case 15: return " fifteen ";
				case 16: return " sixteen ";
				case 17: return " seventeen ";
				case 18: return " eighteen ";
				case 19: return " nineteen ";
			}
			return "";
		}

		inline std::string HandleTens(unsigned int n)
		{	
			switch(n/10)
			{
				case 0: return HandleDigit(n);
				case 1: return HandleTeens(n);
				case 2: return " twenty " + HandleDigit(n % 10);
				case 3: return " thirty " + HandleDigit(n % 10);
				case 4: return " forty " + HandleDigit(n % 10);
				case 5: return " fifty " + HandleDigit(n % 10);
				case 6: return " sixty " + HandleDigit(n % 10);
				case 7: return " seventy " + HandleDigit(n % 10);
				case 8: return " eighty " + HandleDigit(n % 10);
				case 9: return " ninety " + HandleDigit(n % 10);
			}
			return "";
		}

		inline std::string HandleHundreds(unsigned int n)
		{
			unsigned int tens = n % 100;
			std::string ret;
			if (n >= 100)
				ret = HandleDigit(n/100) + " hundred ";
			if (tens == 0) return ret;
			if (ret.empty())
				return HandleTens(tens);
			return ret + " and " + HandleTens(tens);
		}

		inline std::string HandleToName(unsigned int n)
		{
			if (n == 1000) return " one thousand ";
			if (n == 0) return " zero ";
			if (n >= 100) return HandleHundreds(n);
			if (n >= 10) return HandleTens(n);
			return HandleDigit(n);
		}
	}

	inline std::string NumberToName(unsigned int n)
	{
		using namespace NumberToName_Helpers;
		auto name = HandleToName(n);
		boost::trim(name);
		
		auto BothAreSpaces = [](char a, char b) {
			return (a == b) && (a == ' '); };
		
		name.erase(
			std::unique(name.begin(), name.end(), BothAreSpaces),
			name.end());
		return name;
	}

}

#endif // #ifndef BEN_NUMBER_TO_NAME_604
