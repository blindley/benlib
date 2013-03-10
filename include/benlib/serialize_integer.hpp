#pragma once

#include <string>

namespace ben {

    template<typename OutIt, typename Int_T>
    size_t serialize_integer(Int_T n, OutIt o_begin)
    {
        size_t num_chars = 0;
        Int_T const Zero = Int_T();
        Int_T const Ten = static_cast<Int_T>(10);

        if (n == Zero) {
            *o_begin++ = '0';
            return ++num_chars;
        }

        char buffer[std::numeric_limits<Int_T>::digits10 + 1];
        char* p = buffer;
        if (n < Zero) {
            *o_begin++ = '-';            
            ++num_chars;

            if (n == std::numeric_limits<Int_T>::min()) {
                ++n;
                n = -n;                
                *p = ((static_cast<int>(n % Ten) + 1) % 10) + '0';
                n /= Ten;
                ++p;
            } else {
                n = -n;
            }
        }

        while (n > Zero) {
            *p++ = static_cast<int>(n % Ten) + '0';
            n /= Ten;            
        }

        do {            
            *o_begin++ = *--p;
            ++o_begin;
            ++num_chars;
        } while (p > buffer);

        return num_chars;
    }

    template<typename Int_T>
    inline std::string integer_to_string(Int_T x)
    {
        char buffer[std::numeric_limits<Int_T>::digits10 + 1];
        size_t sz = serialize_integer(x, buffer);
        return std::string(buffer,sz);
    }

    template<typename Int_T, typename InIt>
    inline InIt deserialize_integer(InIt begin, InIt end, Int_T& x)
    {
        x = Int_T();
        if (begin == end)
            return begin;

        bool positive = true;
        if (*begin == '-') {
            positive = false;
            ++begin;
        }

        while ( (begin != end) && (*begin >= '0' && *begin <= '9') ) {
            x *= 10;
            x -= (*begin - '0');
            ++begin;
        }

        if (positive)
            x = -x;

        return begin;
    }
}
