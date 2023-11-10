#ifndef UTILS_HPP
# define UTILS_HPP

#include "../iterators/iterator_traits.hpp"

namespace ft
{
	template <typename Type>
	void	swap( Type &lhs, Type &rhs )
	{
		Type	tmp;

		tmp = lhs;
		lhs = rhs;
		rhs = tmp;
	}

	// difference_type renvoie la distance entre deux pointeurs; c'est un type entier
	template< class InputIt >
	typename iterator_traits<InputIt>::difference_type distance( InputIt first, InputIt last ) 
	{
		typename iterator_traits<InputIt>::difference_type	difference = 0;
		for (; first != last; first++) 
			difference++;
		return (difference);
	}; 
}

#endif