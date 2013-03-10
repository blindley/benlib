#ifndef BEN_STRINGREF_1004
#define BEN_STRINGREF_1004

#include <string>
#include <ostream>
#include <cstring>
#include <algorithm>

namespace ben {

class StringRef
{
public:
    typedef char value_type;
    typedef const char * const_iterator;
    typedef const_iterator iterator;
    typedef size_t size_type;
    
    StringRef() :beg_(nullptr), end_(nullptr) {}
    
    StringRef(const char * str)
        :beg_(str),
        end_(str + strlen(str))
    {}
    
    StringRef(const char * str, size_t sz)
        :beg_(str),
        end_(str + sz)
    {}
    
    StringRef(const char * beg, const char * end)
        :beg_(beg),
        end_(end)
    {}
    
    StringRef(const std::string & str)
        :beg_(str.c_str()),
        end_(beg_ + str.size())
    {}
    
    StringRef(const std::string & str, size_t sz)
        :beg_(str.c_str()),
        end_(beg_ + sz)
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

std::ostream & operator<<(std::ostream & os, const StringRef & str) {
	os.write(str.begin(), str.size());
	return os;
}

std::string & operator+=(std::string & lhs, const StringRef & rhs) {
	return lhs.append(rhs.begin(), rhs.end());
}

std::string operator+(const StringRef & lhs, const StringRef & rhs) {
	std::string str;
	// minimize allocations
	str.reserve(lhs.size() + rhs.size());
	str += lhs;
	str += rhs;
	return str;
}

bool operator==(const StringRef & lhs, const StringRef & rhs) {
	if (lhs.size() != rhs.size()) return false;
	if (lhs.begin() == rhs.begin()) return true;
	return std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

bool operator!=(const StringRef & lhs, const StringRef & rhs) {
	return !(lhs == rhs);
}

bool operator<(const StringRef & lhs, const StringRef & rhs) {
	return std::lexicographical_compare(
	    lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

bool operator>(const StringRef & lhs, const StringRef & rhs) {
	return std::lexicographical_compare(
	    rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
}

bool operator<=(const StringRef & lhs, const StringRef & rhs) {
	return !(lhs > rhs);	
}

bool operator>=(const StringRef & lhs, const StringRef & rhs) {
	return !(lhs < rhs);	
}

}

#endif // #ifndef BEN_STRINGREF_1004
