#ifndef BEN_SAFESTD_EXCEPTION_338
#define BEN_SAFESTD_EXCEPTION_338

#include <stdexcept>

namespace ben { namespace safestd {
	
	class IndexOutOfBounds : public std::out_of_range
	{
	public:
	    IndexOutOfBounds(
			const char * class_name, const char * method,
			long long index, long long size)
			:std::out_of_range(
				std::string("IndexOutOfBounds Exception: In ")
			  + class_name + "::" + method + " : attempt to access element #"
			  + std::to_string(index) + " in container of size " + std::to_string(size))
		{}
	private:	    
	};
	
	class InvalidIteratorDereference : public std::out_of_range
	{
	public:
		InvalidIteratorDereference(
			const char * class_name, const char * method)
			:std::out_of_range(
				std::string("InvalidIteratorDereference Exception: In ")
			  + class_name + "::" + method)
		{}
	private:
	};
	
	class OperationOnInvalidIterator : public std::out_of_range
	{
	public:
	    OperationOnInvalidIterator(
	        const char * class_name, const char * method)
	        :std::out_of_range(
	            std::string("OperationOnInvalidIterator Exception: In ")
	          + class_name + "::" + method)
	    {}
	private:
	};
	
	class EndIteratorDereference : public std::out_of_range
	{
	public:
	    EndIteratorDereference(
			const char * class_name, const char * method)
			:std::out_of_range(
				std::string("EndIteratorDereference Exception: In ")
			  + class_name + "::" + method)
		{}
	private:
	};
	
	class IteratorOutOfBounds : public std::out_of_range
	{
	public:
	    IteratorOutOfBounds(
	        const char * class_name, const char * method)
	        :std::out_of_range(
	            std::string("IteratorOutOfBounds Exception: In ")
	          + class_name + "::" + method)
	    {}
	private:
	};
	
	class BadIteratorComparison : public std::runtime_error
	{
	public:
		BadIteratorComparison(
		    const char * class_name, const char * method)
		    :std::runtime_error(
				std::string("BadIteratorComparison Exception: In ")
			  + class_name + "::" + method)
		{}
	};
	
	class IncompatibleIteratorOperation : public std::runtime_error
	{
	public:
		IncompatibleIteratorOperation(
			const char * class_name, const char * method)
			:std::runtime_error(
				std::string("IncompatibleIteratorOperation Exception: In ")
			  + class_name + "::" + method)
		{}
	private:	
	};
}}

#endif // #ifndef BEN_SAFESTD_EXCEPTION_338
