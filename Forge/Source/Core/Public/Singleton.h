#ifndef SINGLETON_H
#define SINGELTON_H

#include "Common/Compiler.h"

namespace Forge
{
	template<typename T>
	class Singleton
	{
	protected:
		Singleton() = default;

	protected:
		Singleton(Singleton<T>&& rhs) = delete;
		Singleton(const Singleton<T>& rhs) = delete;
		Singleton& operator=(Singleton<T>&& rhs) = delete;
		Singleton& operator=(const Singleton<T>&& rhs) = delete;
	
	public:
		static T& GetInstance()
		{
			static T instance;
			return instance;
		}
	};
}

#endif // SINGLETON_H
