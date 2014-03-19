#include <vector>
#include <iostream>
#include <string>

#define SAVE void applySerialization() {  
#define REGISTER(T, V) registerVariable(new Variable<T>(&V));
#define END }

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

	Variable(T *var) : pointer(var)
	{
	}

	void save(std::ostream &out)
	{
		out << *pointer << " ";
	}

	void load(std::istream &in)
	{
		in >> *pointer;
	}

private:
	T *pointer;
};

class Base
{
public:

	Base() 
	{
	}

	Base(const Base &b)
	{
	}

	Base & operator=(const Base & b)
	{
		return *this;
	}

	void load(const char *filePath)
	{
		checkRegistration();
		for (std::vector<BaseVariable *>::iterator it = classMembers.begin();
			it != classMembers.end(); it++)
		{
			(*it)->load(std::cin);
		}
	}

	void save(const char *filePath)
	{
		checkRegistration();
		for (std::vector<BaseVariable *>::iterator it = classMembers.begin();
			it != classMembers.end(); it++)
		{
			(*it)->save(std::cout);
		}
		std::cout << std::endl;
	}
	
	void checkRegistration()
	{
		if (classMembers.empty())
		{
			applySerialization();
		}
	}

	void registerVariable(BaseVariable *variable)
	{
		classMembers.push_back(variable);
	}

	virtual void applySerialization() = 0;

	virtual ~Base()
	{
		for (std::vector<BaseVariable *>::iterator it = classMembers.begin();
			it != classMembers.end(); it++)
		{
			delete *it;
		}
	}

protected:
	std::vector<BaseVariable *> classMembers;
};

class Derived : public Base
{
public:
	SAVE
		REGISTER(int, x)
		REGISTER(std::string, a)
	END

	std::string a;
	int x;
};

int main()
{
	Derived d;
	d.load("input");
	d.save("output");

	{
		Derived d2 = d;
		d.save("input");
	}
	d.save("output");

	return 0;
}
