#pragma once

namespace ben
{
template<typename InIt, typename OutIt>
InIt CopyNextWord(InIt ibegin, InIt iend, OutIt obegin)
{
    ibegin = std::find_if(ibegin, iend, [](char c) { return !isspace(c); });
    while (ibegin != iend && !isspace(*ibegin))
    {
        *obegin = *ibegin;
        ++ibegin;
        ++obegin;
    }
    return ibegin;
}

template<typename InIt>
InIt ReadNextWord(InIt ibegin, InIt iend, std::string& s)
{
    s.clear();
    ibegin = CopyNextWord(ibegin, iend, std::back_inserter(s));
    return ibegin;
}

template<typename InIt, typename OutIt, typename Pred>
InIt CopyUntilMatch(InIt ibegin, InIt iend, OutIt obegin, Pred p)
{
    while (ibegin != iend && !p(*ibegin))
    {
        *obegin = *ibegin;
        ++obegin;
        ++ibegin;
    }
    return ibegin;
}

template<typename InIt, typename OutIt, typename Val>
InIt CopyUntilValue(InIt ibegin, InIt iend, OutIt obegin, Val v)
{
    typedef decltype(*ibegin) i_type;
    auto pred = [&](i_type t) { return t == v; };
    return CopyUntilMatch(ibegin, iend, obegin, pred);
}

template<typename InIt, typename OutIt>
InIt CopyLine(InIt ibegin, InIt iend, OutIt obegin)
{
    ibegin = CopyUntilValue(ibegin, iend, obegin, '\n');
    if (ibegin != iend)
        ++ibegin;
    return ibegin;
}

template<typename InIt>
InIt ReadLine(InIt ibegin, InIt iend, std::string& line)
{
    line.clear();
    ibegin = CopyLine(ibegin, iend, std::back_inserter(line));
    return ibegin;
}



}