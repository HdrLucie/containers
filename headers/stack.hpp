#ifndef STACK_HPP
# define STACK_HPP

#include "vector.hpp"

namespace   ft {
	
	template <class Type, class Container = vector<Type> >
	class	stack {

	public : 
	typedef typename	Container::value_type	value_type;
	typedef typename	Container::size_type	size_type;
	typedef				Container				container_type;
	
	protected:
		Container c;

	public :
		explicit stack (const Container& ctnr = Container()) : c(ctnr) {};
		~stack(void) {};
		stack& operator=( const stack& other ) { c = other.c; return *this; }

		bool				empty() const {return (c.empty()); }
		size_type			size() const {return c.size(); }
		value_type&			top() { return c.back(); }
		const value_type& 	top() const { return c.back(); }
		void 				push(const value_type& x) { c.push_back(x); }
		void 				pop() { c.pop_back(); }

		// Une friend fonction est une fonction qui n’est pas membre d’une classe, mais qui a 
		// accès aux membres privés et protégés  de la classe.
		// Les fonctions Friend ne sont pas considérées comme membres de classe ; 
		// ce sont des fonctions externes normales qui reçoivent des privilèges d’accès spéciaux.

		friend bool operator== (const stack& lhs, const stack& rhs) { return (lhs.c == rhs.c); };
		friend bool operator!=(const stack& lhs, const stack& rhs) { return (rhs.c != lhs.c); };
		friend bool operator< (const stack& lhs, const stack& rhs) { return (lhs.c < rhs.c); };
		friend bool operator> (const stack& lhs, const stack& rhs) { return (lhs.c > rhs.c); };
		friend bool operator>=(const stack& lhs, const stack& rhs) { return (lhs.c >= rhs.c); };
		friend bool operator<=(const stack& lhs, const stack& rhs) { return (lhs.c <= rhs.c ); };
	};


}

#endif
