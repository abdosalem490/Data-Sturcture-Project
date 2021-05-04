#pragma once
#include "Node.h"
template<class T , class M>
class Pair
{
private:
	T value;
	M priority;
public:
	Pair()
	{
		priority = -1;
	}
	Pair(const T & v, const M & priority)
	{
		this->value = v;
		this->priority = priority;
	}
	T get_value() const
	{
		return this->value;
	}
	M getPriority() const
	{
		return this->priority;
	}	
	~Pair()
	{
	}
	bool operator <(const Pair& p)
	{
		if (priority < p.getPriority())
		{
			return true;
		}
		return false;
	}
	bool operator > (const Pair& p)
	{
		if (priority > p.getPriority())
		{
			return true;
		}
		return false;
	}
};
