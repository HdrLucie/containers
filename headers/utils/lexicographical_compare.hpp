#ifndef LEXICOGRAPHICAL_COMPARE_HPP
# define LEXICOGRAPHICAL_COMPARE_HPP


// Lexicographical_compare : permet de comparer des strings. 
// First1 && First2 : iterateur au debut de la string.
// Last1 && last2 : iterateur a la fin de la string. 
// Return un bool : true si jamais les range sont string sont identiques, sinon, return false.

namespace ft
{
	template <class InputIterator1, class InputIterator2>
		bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
								InputIterator2 first2, InputIterator2 last2) {

		while (first1!=last1)
		{
			if (first2==last2 || *first2<*first1)
				return (false);
			else if (*first1<*first2) 
				return (true);
			++first1; 
			++first2;
		}
		return (first2!=last2);
	};

}

#endif