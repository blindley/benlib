#ifndef BEN_CONTAINER_ALGO_844
#define BEN_CONTAINER_ALGO_844

#include <algorithm>
#include <numeric>
#include <iterator>

namespace ben
{
	template<typename C, typename T>
	void RemoveAndErase(C & cont, const T & val)	    
	{
		auto new_end =
		    std::remove(std::begin(cont), std::end(cont), val);
		cont.erase(new_end, std::end(cont));		
	}
	
	template<typename C, typename P>
	void RemoveAndEraseIf(C & cont, P pred)
	{
		auto new_end =
		    std::remove_if(std::begin(cont), std::end(cont), pred);
		cont.erase(new_end, std::end(cont));
	}
	
	template<typename C, typename F>
	void TransformSelf(C & cont, F func)
	{
		std::transform(
		    std::begin(cont), std::end(cont), std::begin(cont), func);
	}
	
	template<typename C>
	void Reverse(C & cont)
	{
		std::reverse(std::begin(cont), std::end(cont));
	}
	
	template<typename C, typename T>
	void Iota(C & cont, T init)
	{
		std::iota(std::begin(cont), std::end(cont), init);
	}
	
	template<typename C>
	void Shuffle(C & cont)
	{
		std::random_shuffle(std::begin(cont), std::end(cont));
	}
	
	template<typename C>
	void Sort(C & cont)
	{
		std::sort(std::begin(cont), std::end(cont));
	}
	
	template<typename C, typename P>
	void Sort(C & cont, P pred)
	{
		std::sort(std::begin(cont), std::end(cont), pred);
	}
	
	template<typename C1, typename C2>
	void Append(C1 & dest, const C2 & src)
	{		
		dest.insert(std::begin(dest), std::begin(src), std::end(src));
	}
	
	template<typename C>
	void Unique(C & cont)
	{
		auto new_end = std::unique(std::begin(cont), std::end(cont));
		cont.erase(new_end, std::end(cont));
	}
	
	template<typename C, typename T>
	auto Accumulate(const C & cont, T init)
	    -> decltype(std::accumulate(
	           std::begin(cont), std::end(cont), init))
	{
		return std::accumulate(std::begin(cont), std::end(cont), init);
	}
	
	template<typename C, typename T, typename P>
	auto Accumulate(const C & cont, T init, P pred)
	    -> decltype(std::accumulate(
	           std::begin(cont), std::end(cont), init, pred))
	{
		return std::accumulate(
		    std::begin(cont), std::end(cont), init, pred);
	}
	
	template<typename C, typename F>
	void ForEach(C & cont, F func)
	{
		std::for_each(std::begin(cont), std::end(cont), func);
	}
	
	template<typename C, typename F>
	void Generate(C & cont, F gen)
	{
		std::generate(std::begin(cont), std::end(cont), gen);
	}
	
	template<typename C, typename T>
	unsigned int Count(const C & cont, T & value)
	{
		return std::count(std::begin(cont), std::end(cont), value);
	}
	
	template<typename C, typename P>
	unsigned int CountIf(const C & cont, P pred)
	{
		return std::count_if(std::begin(cont), std::end(cont), pred);
	}
}

#endif // #ifndef BEN_CONTAINER_ALGO_844
