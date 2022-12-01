#ifndef T_PAIR_H
#define T_PAIR_H

#include "Core/Public/Algorithm/GeneralUtilities.h"

namespace Forge {
	namespace Containers
	{
		/**
		 * @brief Class template that allows to store two heterogeneous objects as
		 * a single unit.
		 * 
		 * @author Karim Hisham
		 */
		template<typename InTypeOne, typename InTypeTwo>
		struct TPair
		{
			using FirstType  = InTypeOne;
			using SecondType = InTypeTwo;

			FirstType  m_first;
			SecondType m_second;

			/**
			 * @brief Default Constructor.
			 */
			TPair(void) 
				: m_first(), m_second() {}
			
			/**
			 * @brief Move Items Constructor.
			 */
			TPair(FirstType&& first, SecondType&& second)
				: m_first(Algorithm::Move(first)), m_second(Algorithm::Move(second)) {}

			/**
			 * @brief Copy Items Constructor.
			 */
			TPair(const FirstType& first, const SecondType& second) 
				: m_first(first), m_second(second) {}

			/**
			 * @brief Move Constructor.
			 */
			TPair(TPair&& other)
			{
				*this = Algorithm::Move(other);
			}

			/**
			 * @brief Copy Constructor.
			 */
			TPair(const TPair& other)
			{
				*this = other;
			}

			/**
			 * @brief Move Assignment Operator.
			 */
			TPair& operator =(TPair&& other)
			{
				this->m_first  = Algorithm::Move(other.m_first);
				this->m_second = Algorithm::Move(other.m_second);

				return *this;
			}

			/**
			 * @brief Copy Assignment Operator.
			 */
			TPair& operator =(const TPair& other)
			{
				this->m_first  = other.m_first;
				this->m_second = other.m_second;

				return *this;
			}
		};
	}
}

#endif // T_PAIR_H
