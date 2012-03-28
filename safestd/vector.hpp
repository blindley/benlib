#ifndef BEN_SAFESTD_VECTOR_554
#define BEN_SAFESTD_VECTOR_554

#include <vector>
#include <string>
#include <sstream>

#include "exception.hpp"

namespace ben { namespace safestd {
	
	template<typename T, typename Allocator=std::allocator<T>>
	class vector;
	template<typename T, typename Allocator=std::allocator<T>>
	class VectorIterator;
	
	template<typename T, typename Allocator>
	class vector
	{
	private:
	    typedef std::vector<T,Allocator> impl_t;
	public:
	    
	    typedef T value_type;
	    typedef Allocator allocator_type;
	    typedef typename impl_t::size_type size_type;
	    typedef typename impl_t::difference_type difference_type;
	    typedef value_type& reference;
	    typedef const value_type& const_reference;
	    typedef typename impl_t::pointer pointer;
	    typedef typename impl_t::const_pointer const_pointer;
	    typedef VectorIterator<T,Allocator> iterator;
	    
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
				throw IndexOutOfBounds(class_name_,
					"operator[]", pos, impl_.size());				
			}
			return impl_[pos];
		}
		const_reference operator[]( size_type pos ) const {
			if (pos >= impl_.size()) {				
				throw IndexOutOfBounds(class_name_,
					"operator[] const", pos, impl_.size());				
			}
			return impl_[pos];
		}
		
		reference front() {
			if (impl_.empty()) {
				throw IndexOutOfBounds(class_name_,
					"front()", 0, 0);
			}
			return impl_.front();
		}
		
		const_reference front() const {
			if (impl_.empty()) {
				throw IndexOutOfBounds(class_name_,
					"front() const", 0, 0);
			}
			return impl_.front();			
		}
		
		reference back() {
			if (impl_.empty()) {
				throw IndexOutOfBounds(class_name_,
					"back()", -1, 0);
			}
			return impl_.back();
		}
		
		const_reference back() const {
			if (impl_.empty()) {
				throw IndexOutOfBounds(class_name_,
					"back() const", -1, 0);
			}
			return impl_.back();			
		}
		
		void push_back(T val) {
			impl_.push_back(std::move(val));
		}
		
		// can't make these functions safe
		T* data() { return impl_.data(); }		
		const T* data() const { return data(); }
		
		iterator begin() {
			iterator i;
			i.pvector_ = this;
			i.it_ = impl_.begin();
			return i;
		}
		
		iterator end() {
			iterator i;
			i.pvector_ = this;
			i.it_ = impl_.end();
			return i;
		}
		
		friend class VectorIterator<T,Allocator>;
		
	private:
	    impl_t impl_;
	    
	    // useful for constructing exception explanations	    
	    static const char * const class_name_;
	};
	
	template<typename T, typename Allocator>
	const char * const vector<T,Allocator>::class_name_
		= "ben::safestd::vector<>";
		
		
	
	template<typename T, typename Allocator>
	class VectorIterator
	    // : public std::iterator<std::random_access_iterator_tag,T>
	{
	public:
	    typedef vector<T,Allocator> vec_t;
		typedef T value_type;
		typedef typename vec_t::difference_type difference_type;
		typedef typename vec_t::pointer pointer;
		typedef typename vec_t::reference reference;
		typedef std::random_access_iterator_tag iterator_category;
	    
	    typename vec_t::reference operator*() const {
			if (pvector_ == nullptr) {
				throw InvalidIteratorDereference(class_name_, "operator*");
			}
			if (it_ == pvector_->impl_.end()) {				
				throw EndIteratorDereference(class_name_, "operator*");
			}
			return *it_;
		}
		
		VectorIterator & operator++() {
			if (pvector_ == nullptr) {
				throw OperationOnInvalidIterator(class_name_, "operator++");
			}
			if (it_ == pvector_->impl_.end()) {
				throw IteratorOutOfBounds(class_name_, "operator++");
			}
			++it_;
			return *this;
		}
		
		VectorIterator operator++(int) {
			VectorIterator tmp(*this);
			++(*this);
			return tmp;
		}
		
		VectorIterator & operator--() {
			if (pvector_ == nullptr) {
				throw OperationOnInvalidIterator(class_name_, "operator--");				
			}
			if (it_ == pvector_->impl_.begin()) {
				throw IteratorOutOfBounds(class_name_, "operator--");
			}
			--it_;
			return *this;
		}
		
		VectorIterator operator--(int) {
			VectorIterator tmp(*this);
			--(*this);
			return tmp;
		}
		
		VectorIterator & operator+=(typename vec_t::difference_type n) {
			if (pvector_ == nullptr) {
				throw OperationOnInvalidIterator(class_name_, "operator+=");
			}
			if (n + (it_ - pvector_->impl_.begin()) > pvector_->impl_.size()) {
				throw IteratorOutOfBounds(class_name_, "operator+=");
			}
			it_ += n;
			return *this;
		}
		
		VectorIterator & operator-=(typename vec_t::difference_type n) {
			if (pvector_ == nullptr) {
				throw OperationOnInvalidIterator(class_name_, "operator-=");
			}
			if (n > (it_ - pvector_->impl_.begin())) {
				throw IteratorOutOfBounds(class_name_, "operator-=");
			}
			it_ -= n;
			return *this;
		}
		
		bool operator==(const VectorIterator & rhs) const {
			if (pvector_ != rhs.pvector_) {
				throw BadIteratorComparison(class_name_, "operator==");
			}
			return it_ == rhs.it_;
		}
		
		bool operator!=(const VectorIterator & rhs) const {
			try { return !(*this == rhs); }
			catch(BadIteratorComparison &) {
				throw BadIteratorComparison(class_name_, "operator!=");
			}
		}
		
		bool operator<(const VectorIterator & rhs) const {
			if (pvector_ != rhs.pvector_) {
				throw BadIteratorComparison(class_name_, "operator<");
			}
			return it_ < rhs.it_;
		}
		
		bool operator>(const VectorIterator & rhs) const {
			try { return rhs < (*this); }
			catch(BadIteratorComparison &) {
				throw BadIteratorComparison(class_name_, "operator>");
			}
		}
		
		bool operator<=(const VectorIterator & rhs) const {
			try { return !(rhs < (*this)); }
			catch(BadIteratorComparison &) {
				throw BadIteratorComparison(class_name_, "operator<=");
			}
		}
		
		bool operator>=(const VectorIterator & rhs) const {
			try { return !((*this) < rhs); }
			catch(BadIteratorComparison &) {
				throw BadIteratorComparison(class_name_, "operator>=");
			}
		}
		
		T * operator->() const {
			try { return &(**this); }
			catch(InvalidIteratorDereference & e) {
				throw InvalidIteratorDereference(class_name_, "operator->");
			}
		}
		
		difference_type operator-(const VectorIterator & rhs) const {
			if (pvector_ != rhs.pvector_) {
				throw IncompatibleIteratorOperation(class_name_, "operator-");
			}
			return it_ - rhs.it_;
		}
		
	private:
	    vec_t * pvector_ = nullptr;
	    typename vec_t::impl_t::iterator it_;
	    
	    friend vec_t;
	    
	    static const char * const class_name_;
	};
	
	template<typename T, typename A>
	const char * const VectorIterator<T,A>::class_name_ =
		"ben::safestd::vector<>::iterator";
		
	template<typename T, typename A>
	VectorIterator<T,A> operator+(
		VectorIterator<T,A> it,
		typename VectorIterator<T,A>::difference_type n)
	{
		return it += n;
	}
	
	template<typename T, typename A>
	VectorIterator<T,A> operator+(
		typename VectorIterator<T,A>::difference_type n,
		VectorIterator<T,A> it)
	{
		return it += n;
	}
	
	template<typename T, typename A>
	VectorIterator<T,A> operator-(
		VectorIterator<T,A> it,
		typename VectorIterator<T,A>::difference_type n)
	{
		return it -= n;
	}
		
}}

#endif // #ifndef BEN_SAFESTD_VECTOR_554
