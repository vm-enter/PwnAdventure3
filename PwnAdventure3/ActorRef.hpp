#pragma once

template <typename T>
class ActorRef
{
public:
	ActorRef()
	{
		this->p = 0;
	}

	operator T*()
	{
		return this->p;
	}

	T& operator *()
	{
		return *this->p;
	}

	T* operator ->()
	{
		return this->p;
	}

	bool operator==(T* pT)
	{
		return this->p == pT;
	}

	T *p;
};