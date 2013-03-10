#ifndef BEN_STRINGREF_1004
#define BEN_STRINGREF_1004

#include <string>
#include <ostream>
#include <cstring>
#include <algorithm>
#include <array>
#include <vector>
#include <cctype>

namespace ben {

class StringRef
{
public:
    typedef char value_type;
    typedef const char * const_iterator;
    typedef char * iterator;
    typedef size_t size_type;
    
    StringRef() :beg_(nullptr), end_(nullptr) {}
    
    explicit StringRef(char * str)
        :beg_(str),
        end_(str + strlen(str))
    {}
    
    StringRef(char * str, size_t sz)
        :beg_(str),
        end_(str + sz)
    {}
    
    StringRef(char * beg, char * end)
        :beg_(beg),
        end_(end)
    {}
    
    explicit StringRef(std::string & str)
        :beg_(&str[0]),
        end_(beg_ + str.size())
    {}
    
    StringRef(std::string & str, size_t sz)
        :beg_(&str[0]),
        end_(beg_ + sz)
    {}
    
    iterator begin() const { return beg_; }
    // const_iterator begin() const { return beg_; }
    const_iterator cbegin() const { return beg_; }
    iterator end() const { return end_; }
    // const_iterator end() const { return end_; }
    const_iterator cend() const { return end_; }
    
    size_type size() const { return end_ - beg_; }
    size_type length() const { return size(); }
    bool empty() const { return size() == 0; }
    
    char& operator[](size_type index) const { return beg_[index]; }
    // char const & operator[](size_type index) const { return beg_[index]; }
    char& front() const { return *beg_; }
    // char front() const { return *beg_; }
    char& back() const { return *(end_ - 1); }
    // char back() const { return *(end_ - 1); }
    
    std::string str() const { return std::string(beg_,end_); }
    
    StringRef substr(size_type pos, size_type count) const {
		return StringRef(beg_ + pos, beg_ + pos + count);
	}
	
	StringRef substr(size_type pos) const {
		return StringRef(beg_ + pos, end_);
	}
	
	void pop_back() { --end_; }
	void pop_front() { ++beg_; }
private:
    iterator beg_, end_;
}; 

class const_StringRef
{
public:
    typedef char value_type;
    typedef const char * const_iterator;
    typedef const_iterator iterator;
    typedef size_t size_type;
    
    const_StringRef() :beg_(nullptr), end_(nullptr) {}
    
    explicit const_StringRef(const char * str)
        :beg_(str),
        end_(str + strlen(str))
    {}
    
    const_StringRef(const char * str, size_t sz)
        :beg_(str),
        end_(str + sz)
    {}
    
    const_StringRef(const char * beg, const char * end)
        :beg_(beg),
        end_(end)
    {}
    
    explicit const_StringRef(const std::string & str)
        :beg_(str.c_str()),
        end_(beg_ + str.size())
    {}
    
    const_StringRef(const std::string & str, size_t sz)
        :beg_(str.c_str()),
        end_(beg_ + sz)
    {}

    const_StringRef(const StringRef& sref)
        :beg_(sref.cbegin()),
        end_(sref.cend())
    {}
    
    iterator begin() { return beg_; }
    const_iterator begin() const { return beg_; }
    const_iterator cbegin() const { return beg_; }
    iterator end() { return end_; }
    const_iterator end() const { return end_; }
    const_iterator cend() const { return end_; }
    
    size_type size() const { return end_ - beg_; }
    size_type length() const { return size(); }
    bool empty() const { return size() == 0; }
    
    char operator[](size_type index) const { return beg_[index]; }
    char front() const { return *beg_; }
    char back() const { return *(end_ - 1); }
    
    std::string str() const { return std::string(beg_,end_); }
    
    const_StringRef substr(size_type pos, size_type count) const {
		return const_StringRef(beg_ + pos, beg_ + pos + count);
	}
	
	const_StringRef substr(size_type pos) const {
		return const_StringRef(beg_ + pos, end_);
	}
	
	void pop_back() { --end_; }
	void pop_front() { ++beg_; }
private:
    iterator beg_, end_;
};

inline std::ostream & operator<<(std::ostream & os, const const_StringRef & str) {
	os.write(str.begin(), str.size());
	return os;
}

inline std::string & operator+=(std::string & lhs, const const_StringRef & rhs) {
	return lhs.append(rhs.begin(), rhs.end());
}

inline std::string operator+(const const_StringRef & lhs, const const_StringRef & rhs) {
	std::string str;
	// minimize allocations
	str.reserve(lhs.size() + rhs.size());
	str += lhs;
	str += rhs;
	return str;
}

inline bool operator==(const const_StringRef & lhs, const const_StringRef & rhs) {
	if (lhs.size() != rhs.size()) return false;
	if (lhs.begin() == rhs.begin()) return true;
	return std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

inline bool operator!=(const const_StringRef & lhs, const const_StringRef & rhs) {
	return !(lhs == rhs);
}

inline bool operator<(const const_StringRef & lhs, const const_StringRef & rhs) {
	return std::lexicographical_compare(
	    lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}


inline bool operator>(const const_StringRef & lhs, const const_StringRef & rhs) {
	return std::lexicographical_compare(
	    rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
}

inline bool operator<=(const const_StringRef & lhs, const const_StringRef & rhs) {
	return !(lhs > rhs);	
}

inline bool operator>=(const const_StringRef & lhs, const const_StringRef & rhs) {
	return !(lhs < rhs);	
}

inline void TrimLeft(ben::StringRef & sref)
{
    auto NotSpace = [](char c) -> bool { return !std::isspace(c); };
    auto first = std::find_if(sref.begin(), sref.end(), NotSpace);
    sref = ben::StringRef(first, sref.end());
}

inline void TrimRight(ben::StringRef & sref)
{
    auto NotSpace = [](char c) -> bool { return !std::isspace(c); };

    typedef std::reverse_iterator<ben::StringRef::iterator> revit;
    auto revlast = std::find_if(revit(sref.end()), revit(sref.begin()), NotSpace);
    auto last = revlast.base();
    sref = ben::StringRef(sref.begin(), last);
}

inline void Trim(ben::StringRef & sref)
{
    TrimLeft(sref);
    TrimRight(sref);
}

inline std::array<ben::StringRef, 2> SplitFirst(ben::StringRef sref)
{
    std::array<ben::StringRef, 2> arr;
    auto IsSpace = [](char c) -> bool { return std::isspace(c) != 0; };
    auto NotSpace = [](char c) -> bool { return std::isspace(c) == 0; };

    auto first_non_space = std::find_if(sref.begin(), sref.end(), NotSpace);
    auto next_space = std::find_if(first_non_space, sref.end(), IsSpace);
    arr[0] = ben::StringRef(sref.begin(), next_space);
    arr[1] = ben::StringRef(next_space, sref.end());
    return arr;
}

inline std::vector<ben::StringRef> Split(ben::StringRef sref)
{
    std::vector<ben::StringRef> vec;
    while (!sref.empty())
    {
        auto p = SplitFirst(sref);
        Trim(p[0]);
        Trim(p[1]);
        vec.push_back(p[0]);
        sref = p[1];
    }
    return vec;
}

}

#endif // #ifndef BEN_STRINGREF_1004
