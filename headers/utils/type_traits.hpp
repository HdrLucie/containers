#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

//Type traits : classes qui permettent d'obtenir, au moment de la compilation, 
// les caracteristiques d'un objet. 

namespace ft
{

	/* 
	┌───────────────────┐
	│   IS_INTEGRAL     │
	└───────────────────┘
	*/

	// Les classes et modeles type_traits sont utilises afin de prendre en charge l'indifference de type
	// la classification et la tranformation au moment de la compilation.
	// Programmation generique : repose sur son independance vis a vis du type. Permet d'augmenter l'abstraction du langage.
	// Un avantage de la programmation générique consiste à abstraire un ensemble de concepts cohérents pour construire des 
	// algorithmes au-dessus indépendamment de leur implémentation. Ainsi la fonction de tri de la STL a besoin en entrée 
	// d'itérateurs aléatoires sur une collection d'objets et d'une fonction de comparaison sur ces objets ; 
	// cela rend ainsi cette fonction utilisable dans de très nombreux contextes.

	template< class T >
	struct is_integral { static const bool value = false; };
	template<>
	struct is_integral<bool> { static const bool value = true; };
	template<>
	struct is_integral<char> { static const char value = true; };
	template<>
	struct is_integral<unsigned char> { static const unsigned char value = true; };
	template<>
	struct is_integral<wchar_t> { static const wchar_t value = true; };
	template<>
	struct is_integral<short> { static const short value = true; };
	template<>
	struct is_integral<unsigned short> { static const unsigned short value = true; };
	template<>
	struct is_integral<int> { static const int value = true; };
	template<>
	struct is_integral<unsigned int> { static const unsigned int value = true; };	
	template<>
	struct is_integral<long> { static const long value = true; };
	template<>
	struct is_integral<long long> { static const long value = true; };
	template<>
	struct is_integral<unsigned long> { static const unsigned long value = true; };

	/* 
  	┌────────────────────┐
  	│   ENABLE_IF        │
  	└────────────────────┘
 	*/

	// Enable_if : permet de creer une instance de type pour une resolution de surchage SFINAE
	// SFINAE : Substitution failure is not an Error. 
	// (https://h-deb.clg.qc.ca/Sujets/Divers--cplusplus/SFINAE.html)
	// Le typedef enable_if<condition, type> existe et est synonyme de type si et seulement si la condition est vraie.
	// B : determine l'existence du type obtenu, T : type a instancie si B est true.

	template <bool B, class T = void>
	struct enable_if;

	template<class T>
	struct enable_if<true, T> { typedef T type ; };

}

#endif