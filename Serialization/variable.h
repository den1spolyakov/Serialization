#ifndef VARIABLE_H
#define VARIABLE_H 

#include <iostream>

class BaseVariable
{
public:
	virtual void save(std::ostream &out) = 0;
	virtual void load(std::istream &in) = 0;
};

template<typename T>
class Variable : public BaseVariable
{
public:
	Variable(T *var);
	void save(std::ostream &out);
	void load(std::istream &in);
private:
	T *pointer;
};

template<typename T>
Variable<T>::Variable(T *var) : pointer(var)
{
}

template<typename T>
void Variable<T>::save(std::ostream &out)
{
	out << *pointer << " ";
}

template<typename T>
void Variable<T>::load(std::istream &in)
{
	in >> *pointer;
}

#endif