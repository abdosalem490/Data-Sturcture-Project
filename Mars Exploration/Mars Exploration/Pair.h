#pragma once
#include "Node.h"
template<class T* , class M>
class Pair
{
private:
	T* ptr;
	M priority;
public:
	Pair()
	{
		this->ptr = nullptr;
		priority = -1;
	}
	Pair(T* &ptr, M priority)
	{
		this->ptr = ptr;
		ptr = nullptr;
		this->priority = priority;
	}
	T* getPointer() const
	{
		return this->ptr;
	}
	M getPriority() const
	{
		return this->priority;
	}	
	~Pair()
	{
		delete ptr;
	}
};