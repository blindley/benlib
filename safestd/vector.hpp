#ifndef BEN_SAFESTD_VECTOR_554
#define BEN_SAFESTD_VECTOR_554

#include <vector>
#include <string>
#include <sstream>

namespace ben { namespace safestd {
	
	class OutOfBounds : public std::exception {
	public:
	    OutOfBounds(const std::string & str = "")
	    {
			std::ostringstream oss;
			oss << "ben::safestd::OutOfBounds";
			if (!str.empty())
			    oss << " : " << str;
			what_ = oss.str();
		}
		
		virtual ~OutOfBounds() throw() {}
		
		virtual const char * what() const throw() {
			return what_.c_str();
		}
		
	private:
	    std::string what_;	
	};
	
	template<typename T, typename Allocator=std::allocator<T>>
	class vector
	{
	private:
	    typedef std::vector<T,Allocator> impl_t;
	public:
	    
	    typedef T value_type;
	    typedef Allocator allocator_type;
	    typedef typename impl_t::size_type size_type;
	    typedef typename impl_t::difference_type difference;
	    typedef value_type& reference;
	    typedef const value_type& const_reference;
	    typedef typename impl_t::pointer pointer;
	    typedef typename impl_t::const_pointer const_pointer;
	    
	    explicit vector(const Allocator & alloc = Allocator() )
	        :impl_(alloc) {}
	    explicit vector( size_type count,
	                     const T& value,
	                     const Allocator& alloc = Allocator() )
	        :impl_(count, value, alloc) {}
	    explicit vector( size_type count )
	        :impl_(count) {}
	    template <class InputIterator>
	    vector( InputIterator first, InputIterator last,
	            const Allocator& alloc = Allocator() )
	        :impl_(first, last, alloc) {}
	    vector( const vector& other, const Allocator& alloc )
	        :impl_(other.impl_, alloc) {}
	    vector( vector && other, const Allocator& alloc)
	        :impl_(std::forward(other.impl_), alloc) {}
	    vector( std::initializer_list<T> init,
	            const Allocator& alloc = Allocator() )
	        :impl_(init, alloc) {}
	        
	    void assign( size_type count, const T& value ) {
			impl_.assign(count, value); }
		template<class InIt>
		void assign( InIt first, InIt last ) {
			impl_.assign(first, last); }
			
		allocator_type get_allocator() const {
			return impl_.get_allocator(); }
			
		reference at( size_type pos ) { return impl_.at(pos); }
		const_reference at( size_type pos ) const {
			return impl_.at(pos); }
			
		reference operator[]( size_type pos ) {
			if (pos >= impl_.size()) {
				std::ostringstream oss;
				oss << "vector<>::operator[] : tried to access element "
				    << pos << " in vector of size " << impl_.size();
			    throw OutOfBounds(oss.str());
			}
			return impl_[pos];
		}
		const_reference operator[]( size_type pos ) const {
			if (pos >= impl_.size()) {
				std::ostringstream oss;
				oss << "vector<>::operator[] const : tried to access element "
				    << pos << " in vector of size " << impl_.size();
			    throw OutOfBounds(oss.str());
			}
			return impl_[pos];
		}
		
		reference front() {
			if (impl_.empty()) {
				std::ostringstream oss;
				oss << "vector<>::front() : called on empty vector";
				throw OutOfBounds(oss.str());
			}
			return impl_.front();
		}
		
		const_reference front() const {
			if (impl_.empty()) {
				std::ostringstream oss;
				oss << "vector<>::front() const : called on empty vector";
				throw OutOfBounds(oss.str());
			}
			return impl_.front();			
		}
		
		reference back() {
			if (impl_.empty()) {
				std::ostringstream oss;
				oss << "vector<>::back() : called on empty vector";
				throw OutOfBounds(oss.str());
			}
			return impl_.back();
		}
		
		const_reference back() const {
			if (impl_.empty()) {
				std::ostringstream oss;
				oss << "vector<>::back() const : called on empty vector";
				throw OutOfBounds(oss.str());
			}
			return impl_.back();			
		}
		
		// can't make these functions safe
		T* data() { return impl_.data(); }		
		const T* data() const { return data(); }
		
		friend class VectorIterator<T,Allocator>
		
		
	private:
	    impl_t impl_;
	};
	
	template<typename T, typename Allocator>
	class VectorIterator
	{
	public:
	    
	private:
	    vector<T> * pvector_;
	    vector<T>::iterator it_;
	};
		
}}

#endif // #ifndef BEN_SAFESTD_VECTOR_554
