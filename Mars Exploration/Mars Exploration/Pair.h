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
		value = 0;
	}
	Pair(const T & v, const M & priority)
	{
		this->value = v;
		this->priority = priority;
	}
	Pair(const Pair& p)
	{
		priority = p.getPriority();
		value = p.get_value();
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
	void setValue(T value)
	{
		this->value = value;
	}
	void setPriority(M priority)
	{
		this->priority = priority;
	}
	bool operator < (const Pair& p)
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
	
	bool operator == (const Pair& p)
	{
		return (priority == p.getPriority());
	}
	void operator =(const Pair& p)
	{
		this->value = p.get_value();
		this->priority = p.getPriority();
		
	}
};
