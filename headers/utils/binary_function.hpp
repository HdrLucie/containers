#ifndef BINARY_FUNCTION_HPP
# define BINARY_FUNCTION_HPP

// Base class for standart binary function.

namespace ft
{
	template<typename Arg1, typename Arg2, typename Result>
	struct binary_function {
		typedef	Arg1	firstArgumentType;	// Type du premier argument dans l'operateur ()
		typedef	Arg2	secondArgumentType;	// Type du second argument dans l'operateur ()
		typedef Result	resultType;			// Type retourne par l'operateur ()
	};

	template<typename Type>
	struct less : public binary_function<Type, Type, bool>
	{
		bool operator()(const Type& lhs, const Type& rhs) const { 
			return (lhs < rhs); 
		}
	};
}


#endif