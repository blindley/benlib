#pragma once

#include <cstdio>

namespace ben
{

class BinaryFileReader;
class BinaryFileReader_iterator;

class BinaryFileReader_iterator
{    
public:
    typedef unsigned char value_type;
    typedef std::input_iterator_tag iterator_category;
    typedef std::ptrdiff_t difference_type;
    typedef value_type* pointer;
    typedef value_type& reference;

    unsigned char operator*() const;
    BinaryFileReader_iterator& operator++();
    void operator++(int);
    
private:    
    BinaryFileReader* m_reader;

    friend class BinaryFileReader;
    friend bool operator==(BinaryFileReader_iterator lhs,
                           BinaryFileReader_iterator rhs);
};

class BinaryFileReader
{
public:
    typedef BinaryFileReader_iterator iterator;

    BinaryFileReader(std::string fn);
    ~BinaryFileReader();

    iterator begin();
    iterator end();

private:
    static const size_t buffer_size = 1024;
    FILE* m_file_ptr;
    std::string m_filename;
    std::array<unsigned char, buffer_size> m_buffer;
    size_t m_num_read;
    size_t m_position;

    void FillBuffer();
    void Next();
    unsigned char Current() const;

    BinaryFileReader(BinaryFileReader const&) /* = delete */;
    void operator=(BinaryFileReader const&) /* = delete */;

    friend class iterator;
};

inline unsigned char BinaryFileReader_iterator::operator*() const
{
    return m_reader->Current();
}

inline BinaryFileReader_iterator& BinaryFileReader_iterator::operator++()
{
    if (m_reader)
    {
        m_reader->Next();
        if (m_reader->m_num_read == 0)
            m_reader = nullptr;
    }
    return *this;
}

inline void BinaryFileReader_iterator::operator++(int)
{
    ++(*this);
}

inline bool operator==(BinaryFileReader_iterator lhs,
                BinaryFileReader_iterator rhs)
{
    return lhs.m_reader == rhs.m_reader;
}

inline bool operator !=(BinaryFileReader_iterator lhs,
                 BinaryFileReader_iterator rhs)
{
    return !(lhs == rhs);
}

inline BinaryFileReader::BinaryFileReader(std::string fn)
    :m_file_ptr(nullptr),
    m_filename(std::move(fn))
{
    m_file_ptr = std::fopen(m_filename.c_str(), "rb");
    FillBuffer();
}

inline BinaryFileReader::~BinaryFileReader()
{
    if (m_file_ptr)
        std::fclose(m_file_ptr);
}

inline BinaryFileReader::iterator BinaryFileReader::begin()
{
    iterator it;
    if (m_num_read != 0)
        it.m_reader = this;
    else
        it.m_reader = nullptr;
    return it;
}

inline BinaryFileReader::iterator BinaryFileReader::end()
{
    iterator it;
    it.m_reader = nullptr;
    return it;
}

inline void BinaryFileReader::FillBuffer()
{
    if(m_file_ptr)
    {
        m_num_read = fread(&m_buffer[0], 1, buffer_size, m_file_ptr);
        m_position = 0;
        if (m_num_read == 0)
        {
            fclose(m_file_ptr);
            m_file_ptr = nullptr;
        }
    }
}

inline void BinaryFileReader::Next()
{
    if (m_num_read == 0)
        return;
    ++m_position;
    if (m_position == m_num_read)
        FillBuffer();
}

inline unsigned char BinaryFileReader::Current() const
{
    return m_buffer[m_position];
}

}