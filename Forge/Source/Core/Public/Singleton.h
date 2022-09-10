#ifndef SINGLETON_H
#define SINGELTON_H

#include "Common/Compiler.h"

namespace Forge
{
	template<typename T>
	class TSingleton
	{
	protected:
		TSingleton() = default;
	   ~TSingleton() = default;

	protected:
		TSingleton(Singleton<T>&& rhs) = delete;
		TSingleton(const Singleton<T>& rhs) = delete;
		TSingleton& operator=(Singleton<T>&& rhs) = delete;
		TSingleton& operator=(const Singleton<T>&& rhs) = delete;
	
	public:
		static T& GetInstance()
		{
			static T instance;
			return instance;
		}
	};

	#define FORGE_CLASS_SINGLETON(Typename) \
		private:							\
			Typename() = default;			\
		friend Forge::Singleton<Typename>;  \
}

#endif // SINGLETON_H
