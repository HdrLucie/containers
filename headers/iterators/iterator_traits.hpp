#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

#include <cstddef>

// Iterator : abstraction de pointeur. Permet de parcourir un tableau d'elements.
// L'avantage d'un iterateur par rapport a un pointeur est que nous pouvons 
// limiter les operations qu'il peut effectuer, comment il se deplace, s'il peut 
// acceder a un element modifiable ou non,...
// Iterator category tags permettent d'avoir des informations afin de savoir 
// quel modele est le plus efficient. 
// Random Access Iterateur : utilise notamment pour vector, possede les fonctionnalites
// d'un bidirectional_iterator et supporte les methodes de parcours +=, +, -= et -.

namespace   ft {

	// Iterator tag : empty types, utilises pour distinguer les differents operateurs. 
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag: public input_iterator_tag {};
	struct bidirectional_iterator_tag: public forward_iterator_tag {};
	struct random_access_iterator_tag: public bidirectional_iterator_tag {};

	// Common iterator class. Cette classe permet de definir les typedef imbriques.
	// Les classes d'iterateurs peuvent heriter de cette classe.
	// Les typedef sont utilises pour la specialisation et la surchage.
	template <typename Category, typename T, typename Distance = ptrdiff_t, typename Pointer = T*, typename Reference = T&>
	struct iterator {
		typedef Category								iterator_category;	// Iterator tag.
		typedef T										value_type;			// type pointed by the iterator.
		typedef Distance								difference_type;	// Distance between iterators.
		typedef Pointer									pointer;			// This type represents a pointer-to-value_type.
		typedef Reference								reference;			// This type represents a reference-to-value_type.This class does nothing but define nested typedefs.
	};
	template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&> 
	struct const_iterator {
		typedef T 										value_type;
		typedef Distance								difference_type;
		typedef Pointer									pointer;
		typedef Reference								reference;
		typedef Category								iterator_category;		
	};

	// Traits class for iterators. 
	template<class Iterator>
	struct iterator_traits {
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;		
	};
	// Specialisation pour le type pointeur.
	template<class T> 
	struct iterator_traits<T*> {
		typedef ptrdiff_t 								difference_type;
		typedef T 										value_type;
		typedef T*										pointer;
		typedef T&										reference;
		typedef random_access_iterator_tag				iterator_category;		
	};
	// Specialisation pour le type const pointeur.
	template<class T> 
	struct iterator_traits<const T*> {
		typedef ptrdiff_t 								difference_type;
		typedef T										value_type;
		typedef const T*								pointer;
		typedef const T&								reference;
		typedef random_access_iterator_tag				iterator_category;
	};
}


#endif