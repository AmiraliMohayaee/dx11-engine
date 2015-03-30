#ifndef SINGLETON_H_INCLUDED
#define SINGLETON_H_INCLUDED

#include "Non-Copyable.h"

namespace DXEngine
{
	template <class T>
	class Singleton : public NonCopyable
	{
	public:
		static T* Instance()
		{
			static T t;
			return &t;
		}
	};
}

#endif