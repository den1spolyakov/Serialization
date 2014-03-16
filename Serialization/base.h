#ifndef BASE_H
#define BASE_H

#include "variable.h"
#include <vector>
#include <fstream>

#define	REGISTER(T, V) registerVariable(new Variable<T>(&V))

class Base
{
public:
	void registerVariable(BaseVariable *variable);
	void save(const char *filePath);
	void load(const char *filePath);
private:
	std::vector<BaseVariable *> classMembers;
};

void Base::registerVariable(BaseVariable *variable)
{
	classMembers.push_back(variable);
}

void Base::save(const char *filePath)
{
	std::ofstream out(filePath);
	if (out.is_open())
	{
		for (std::vector<BaseVariable *>::iterator it = classMembers.begin();
			it != classMembers.end(); it++)
		{
			(*it)->save(out);
		}
		out.close();
	}
}

void Base::load(const char *filePath)
{
	std::ifstream in(filePath);
	if (in.is_open())
	{
		for (std::vector<BaseVariable *>::iterator it = classMembers.begin();
			it != classMembers.end(); it++)
		{
			(*it)->load(in);
		}
		in.close();
	}
}

#endif