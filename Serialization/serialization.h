#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <vector>
#include <string>

#define READ_TYPE(T) \
template<> inline void Reader::process(T &val) \
{ \
	processBasicType(val); \
}

#define WRITE_TYPE(T) \
template<> inline void Writer::process(T &val) \
{ \
	(*this).process((const T &)val); \
}

#define SAVE \
template<typename T> void serialize(T & rw) \
{
#define REG(V) rw.process(V); 
#define END }

class Writer
{
public:
	Writer()
	{
	}

	void *getBuffer()
	{
		return (unsigned char*)&m_buffer[0];
	}

	size_t getSize()
	{
		return m_buffer.size();
	}

	template<typename T>
	Writer & operator <<(const T &val)
	{
		(*this).process(val);
		return *this;
	}

	template<typename T>
	Writer & operator <<(T &val)
	{
		(*this).process(val);
		return *this;
	}

	template<typename T>
	void process(T &val)
	{
		val.serialize(*this);
	}

	template<typename T>
	void process(const T &data)
	{
		unsigned char *address = (unsigned char *)&data;
		for (size_t i = 0; i < sizeof(T); ++i)
		{
			m_buffer.push_back(*(address + i));
		}
	}

	template<typename T>
	void process(std::vector<T> &data)
	{
		(*this).process(data.size());
		for (typename std::vector<T>::iterator it = data.begin();
			it != data.end(); ++it)
		{
			(*this).process((*it));
		}
	}
private:
	std::vector<unsigned char> m_buffer;
};

template<>
inline void Writer::process(const std::string &data)
{
	unsigned char *address = (unsigned char *)data.c_str();
	for (size_t i = 0; i < data.size() + 1; ++i)
	{
		m_buffer.push_back(*(address + i));
	}
}

WRITE_TYPE(std::string)
WRITE_TYPE(char)
WRITE_TYPE(unsigned char)
WRITE_TYPE(int)
WRITE_TYPE(unsigned int)
WRITE_TYPE(long)
WRITE_TYPE(unsigned long)
WRITE_TYPE(float)
WRITE_TYPE(double)

class Reader
{
public:
	Reader(void *data, size_t len) : m_data(data), m_len(len), m_pos(0)
	{
	}

	template<typename T>
	Reader & operator>>(T &val)
	{
		(*this).process(val);
		return *this;
	}

	template<typename T>
	void process(T &val)
	{
		val.serialize(*this);
	}

	template<typename T>
	void process(std::vector<T> &data)
	{
		size_t num;
		(*this).process(num);
		data.clear();
		for (size_t i = 0; i < num; ++i)
		{
			T item;
			(*this).process(item);
			data.push_back(item);
		}
	}

private:

	template<typename T>
	void processBasicType(T & data)
	{
		data = *((T*)((char*)m_data + m_pos));
		m_pos += sizeof(T);
	}

	void *m_data;
	size_t m_len;
	size_t m_pos;
};

template<>
inline void Reader::process(std::string& data)
{
	data = (char*)m_data + m_pos;
	m_pos += data.length() + 1;
}

READ_TYPE(char)
READ_TYPE(unsigned char)
READ_TYPE(int)
READ_TYPE(unsigned int)
READ_TYPE(long)
READ_TYPE(unsigned long)
READ_TYPE(float)
READ_TYPE(double)

#endif
