#ifndef PAIR_HPP
# define PAIR_HPP

#include "colors.hpp"
#include <iostream>

#ifndef VERBOSE_PAIR
# define VERBOSE_PAIR 0
#endif 

namespace   ft {

	template <class T1, class T2>
	struct pair {
		typedef T1 first_type;
		typedef T2 second_type;
		
		T1 first;	// copy of the first object.
		T2 second;	// copy of the second object.

		pair() : first(), second() {
			if (VERBOSE_PAIR)
				std::cout << GR << "Default pair constructor" << NC << std::endl;
			return ;
		};
		// The constructor initializes first with x and second with y.
		pair(const T1& x, const T2& y) : first(x), second(y) {
			if (VERBOSE_PAIR)
				std::cout << GR << "File pair constructor" << NC << std::endl;
			return ;
		};
		// Initializes members from the corresponding members of the argument, 
		// performing implicit conversions as needed. Copy constructor en bref.
		template<class U, class V> pair(const pair<U, V> &p) : first(p.first), second(p.second) {
			if (VERBOSE_PAIR)
				std::cout << GR << "Copy pair constructor" << NC << std::endl;
			return ;
		};
	
		template< class U1, class U2 >
			pair& operator=( const pair<U1, U2>& other) {
				first = static_cast<T1>(other.first);
				second = static_cast<T2>(other.second);
				return (*this);
			};
		~pair() {
			if (VERBOSE_PAIR)
				std::cout << GR << "Pair destructor" << NC << std::endl;
			return ;
		}
	};

	template< class T1, class T2 >
		bool operator==( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs ) { return (lhs.first == rhs.first && lhs.second == rhs.second); };
	template <class T1, class T2>
		bool operator!=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs ) { return !(lhs == rhs); }
	template< class T1, class T2 >
		bool operator<( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs ) { return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second)); };
	template< class T1, class T2 >
	bool operator<=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs ) { return !(rhs < lhs); } ;
	template< class T1, class T2 >
		bool operator>( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs ) { return (lhs < rhs); };
	template< class T1, class T2 >
		bool operator>=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs ) { return !(lhs < rhs); };
}

#endif