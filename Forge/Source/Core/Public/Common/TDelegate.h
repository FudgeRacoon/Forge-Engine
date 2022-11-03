#ifndef T_DELEGATE_HPP
#define T_DELEGATE_HPP

#include <utility>

#include "Compiler.h"
#include "TypeDefinitions.h"
#include "PreprocessorUtilities.h"

#include "Core/Public/Memory/MemoryUtilities.h"

namespace Forge {
	namespace Common
	{
		template<typename _Type>
		class TDelegate {};

		/**
		 * @brief A delegate is a type that represents references to functions with
		 * a particular parameter list and return type.
		 * 
		 * When an instance of a delegate is created, the instance can associated
		 * with any function with a compatible signature and return type. The method
		 * can be invoked (or called) through the delegate instance.
		 * 
		 * Delegates are used to pass functions as arguments to other functions.
		 * This ability to refer to a function as a parameter makes delegates ideal
		 * for defining callback functions.
		 * 
		 * @author Karim Hisham
		 */
		template<typename ReturnType, typename... Params>
		class TDelegate<ReturnType(Params...)>
		{
		private:
			using SelfType         = TDelegate<ReturnType(Params...)>;
			using SelfTypeRef      = TDelegate<ReturnType(Params...)>&;
			using SelfTypePtr      = TDelegate<ReturnType(Params...)>*;
			using ConstSelfType    = const TDelegate<ReturnType(Params...)>;
			using ConstSelfTypeRef = const TDelegate<ReturnType(Params...)>&;
			using ConstSelfTypePtr = const TDelegate<ReturnType(Params...)>*;

		private:
			using SignatureFunc = ReturnType(Params...);
			using InvokableFunc = ReturnType(*)(ConstSelfTypeRef, Params&&...);

		private:
			template<typename InLambdaFunctor>
			struct LambdaStorage 
			{ 
				InLambdaFunctor m_lambda; 
				
				LambdaStorage(InLambdaFunctor lambda)
					: m_lambda(lambda) {}
			};

		private:
			union
			{
				VoidPtr      m_instance_ptr;
				ConstVoidPtr m_const_instance_ptr;
			};

		private:
			Size m_func_container_size;
			 
		private:
			InvokableFunc m_invokable;

		private:
			 mutable VoidPtr m_func_address;

		private:
			/**
			 * @brief Invokes the lambda functor currently bound inplace in the
			 * delegate object.
			 *
			 * This function is used internally by the delegate object to call a
			 * function pointer with the appropriate parameter semantics it was
			 * passed.
			 *
			 * @param[in] self_type The calling delegate object to this function.
			 * @param[in] params    The parameters to pass to the bound function.
			 *
			 * @return ReturnType storing the return value of the bound function.
			 */
			template<typename InFunction>
			static ReturnType InvokeLambda(ConstSelfTypeRef self_type, const Params&... params)
			{
				return reinterpret_cast<LambdaStorage<InFunction>*>(&self_type.m_func_address)->m_lambda(params...);
			}

			/**
			 * @brief Invokes the global function currently bound inplace in the
			 * delegate object.
			 *
			 * This function is used internally by the delegate object to call a
			 * function pointer with the appropriate parameter semantics it was
			 * passed.
			 *
			 * @param[in] self_type The calling delegate object to this function.
			 * @param[in] params    The parameters to pass to the bound function.
			 *
			 * @return ReturnType storing the return value of the bound function.
			 */
			template<typename InFunction>
			static ReturnType InvokeFunction(ConstSelfTypeRef self_type, const Params&... params)
			{
				return (*(reinterpret_cast<InFunction*>(&self_type.m_func_address)))(params...);
			}

			/**
			 * @brief Invokes the member function currently bound inplace in the
			 * delegate object.
			 *
			 * This function is used internally by the delegate object to call a
			 * function pointer with the appropriate parameter semantics it was
			 * passed.
			 *
			 * @param[in] self_type The calling delegate object to this function.
			 * @param[in] params    The parameters to pass to the bound function.
			 *
			 * @return ReturnType storing the return value of the bound function.
			 */
			template<typename InFunction, typename InClass>
			static ReturnType InvokeClassFunction(ConstSelfTypeRef self_type, const Params&... params)
			{
				InFunction function = *(reinterpret_cast<InFunction*>(&self_type.m_func_address));

				return (static_cast<InClass*>(self_type.m_instance_ptr)->*function)(params...);
			}

			/**
			 * @brief Invokes the const member function currently bound inplace in
			 * the delegate object.
			 *
			 * This function is used internally by the delegate object to call a
			 * function pointer with the appropriate parameter semantics it was
			 * passed.
			 *
			 * @param[in] self_type The calling delegate object to this function.
			 * @param[in] params    The parameters to pass to the bound function.
			 *
			 * @return ReturnType storing the return value of the bound function.
			 */
			template<typename InFunction, typename InClass>
			static ReturnType InvokeClassConstFunction(ConstSelfTypeRef self_type, const Params&... params)
			{
				InFunction function = *(reinterpret_cast<InFunction*>(&self_type.m_func_address));

				return (static_cast<const InClass*>(self_type.m_const_instance_ptr)->*function)(params...);
			}

		public:
			/**
			 * @brief Default constructor.
			 * 
			 * Constructs an empty delegate object with the dispatch function
			 * pointers set to null.
			 */
			TDelegate(void)
				: m_invokable(nullptr)
			{
				this->m_func_address = malloc(sizeof(ReturnType(*)(Params...)));

				Memory::MemorySet(this->m_func_address, 0, sizeof(ReturnType(*)(Params...)));
			}

			/**
			 * @brief Bind global function constructor.
			 * 
			 * Constructs a delegate object with the passed function or lambda
			 * bound to the delegate object.
			 */
			template<typename InFunction>
			TDelegate(InFunction function)
			{
				this->m_func_address = malloc(sizeof(ReturnType(*)(Params...)));

				if (TIsAssignable<SignatureFunc*&, InFunction>::Value)
				{
					ConstSize function_size = sizeof(InFunction);

					if (function_size > 1 && function_size <= sizeof(ReturnType(*)(Params...)))
						Memory::MemoryCopy(this->m_func_address, &function, function_size);
					else
						Memory::MemorySet(this->m_func_address, 0, function_size);

					this->m_func_container_size = function_size;

					this->m_invokable = &InvokeFunction<InFunction>;
				}
				else
				{
					ConstSize lambda_storage_size = sizeof(LambdaStorage<InFunction>);

					if (lambda_storage_size > sizeof(ReturnType(*)(Params...)))
						this->m_func_address = realloc(this->m_func_address, lambda_storage_size);
						
					new (this->m_func_address) LambdaStorage<InFunction>(function);
				
					this->m_instance_ptr = nullptr;

					this->m_func_container_size = lambda_storage_size;

					this->m_invokable = &InvokeLambda<InFunction>;
				}
			}
			
			/**
			 * @brief Bind member function constructor.
			 * 
			 * Constructs a delegate object with the passed member function bound
			 * to the delegate object.
			 */
			template<typename InFunction, typename InClass>
			TDelegate(InFunction function, InClass* instance)
			{
				this->m_func_address = malloc(sizeof(ReturnType(*)(Params...)));

				ConstSize function_size = sizeof(InFunction);

				Memory::MemoryCopy(this->m_func_address, &function, function_size);

				this->m_instance_ptr = instance;

				this->m_func_container_size = function_size;

				this->m_invokable = &InvokeClassFunction<InFunction, InClass>;
			}
			
			/**
			 * @brief Bind const member function constructor.
			 *
			 * Constructs a delegate object with the passed const member function
			 * bound to the delegate object.
			 */
			template<typename InFunction, typename InClass>
			TDelegate(InFunction function, const InClass* instance)
			{
				this->m_func_address = malloc(sizeof(ReturnType(*)(Params...)));

				ConstSize function_size = sizeof(InFunction);

				Memory::MemoryCopy(this->m_func_address, &function, function_size);

				this->m_const_instance_ptr = instance;

				this->m_func_container_size = function_size;

				this->m_invokable = &InvokeClassFunction<InFunction, InClass>;
			}

		public:
			/**
			 * @brief Move constructor.
			 */
			TDelegate(SelfType&& other)
			{
				this->Invalidate();

				this->m_instance_ptr = other.m_instance_ptr;

				this->m_func_container_size = other.m_func_container_size;

				this->m_invokable = other.m_invokable;

				this->m_func_address = other.m_func_address;

				other.m_func_address = nullptr;
			}

			/**
			 * @brief Copy constructor.
			 */
			TDelegate(ConstSelfTypeRef other)
			{
				this->Invalidate();

				this->m_func_address = malloc(other.m_func_container_size);

				Memory::MemoryCopy(this->m_func_address, other.m_func_address, other.m_func_container_size);

				this->m_instance_ptr = other.m_instance_ptr;

				this->m_func_container_size = other.m_func_container_size;

				this->m_invokable = other.m_invokable;
			}

		public:
			~TDelegate()
			{
				this->Invalidate();

				free(this->m_func_address);
			}

		public:
			/**
			 * @brief Move assignment.
			 */
			ConstSelfTypeRef operator =(SelfType&& other)
			{
				this->Invalidate();

				this->m_instance_ptr = other.m_instance_ptr;

				this->m_func_container_size = other.m_func_container_size;

				this->m_invokable = other.m_invokable;
				
				this->m_func_address = other.m_func_address;
			
				other.m_func_address = nullptr;
			}

			/**
			 * @brief Copy assignment.
			 */
			ConstSelfTypeRef operator =(ConstSelfTypeRef other)
			{
				this->Invalidate();

				this->m_func_address = malloc(other.m_func_container_size);

				Memory::MemoryCopy(this->m_func_address, other.m_func_address, other.m_func_container_size);

				this->m_instance_ptr = other.m_instance_ptr;

				this->m_func_container_size = other.m_func_container_size;

				this->m_invokable = other.m_invokable;
			}

		public:
			/** 
			 * @brief Checks wether the delegate object has a currently bound
			 * function. The function pointer must be valid and non-nullptr.
			 * 
			 * @return True if the delegate object has a bound function.
			 */
			Bool IsValid(void)
			{
				return this->m_invokable != nullptr;
			}
			
			/**
			 * @brief Checks wether two delegate objects are bound to the same
			 * functions, including the same instance.
			 * 
			 * @param[in] other The other delegate object to check for equality.
			 * 
			 * @return True if both delegate objects are equal.
			 */
			Bool IsEqual(ConstSelfTypeRef other)
			{
				return this->m_instance_ptr == other.m_instance_ptr &&
					   this->m_invokable == other.m_invokable &&
					   Memory::MemoryCompare(this->m_func_address, other.m_func_address, sizeof(ReturnType(*)(Params...)));
			}

		public:
			/**
			 * @brief Releases the currently bound function.
			 * 
			 * This function invalidates the delegate object by resseting its
			 * inplace memory storage for function address and setting the
			 * dispatch function pointers to null.
			 */
			Void Invalidate(void)
			{
				Memory::MemorySet(this->m_func_address, 0, this->m_func_container_size);

				this->m_instance_ptr = nullptr;

				this->m_invokable = nullptr;
			}

			/**
			 * @brief Invokes the currently bound function.
			 *
			 * @param[in] params The parameters to pass to the bound function.
			 *
			 * @return ReturnType storing the return value of the bound function.
			 * 
			 * @throws InvalidOperationException if the delegate object is invalid.
			 */
			ReturnType Invoke(Params... params)
			{
				return (*(this->m_invokable))(*this, params...);
			}
		};
	}
}

#endif // T_DELEGATE_HPP
