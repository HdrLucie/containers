#ifndef REVERSE_ITERATORS_HPP
# define REVERSE_ITERATORS_HPP

#include "iterator_traits.hpp"
#include "../utils/colors.hpp"

#ifndef VERBOSE_REVERSE_VECTOR_IT
# define VERBOSE_REVERSE_VECTOR_IT 0
#endif

namespace   ft {

	template <class Iterator>
	struct reverse_iterator {
		public:
			typedef Iterator												iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			// typedef typename reverse_iterator::const_pointer						const_pointer;
			// typedef typename reverse_iterator::const_reference						const_reference;

		protected:
			iterator_type _current; //copie de l'iterateur de base.
		public : 
			reverse_iterator() : _current() {
				if (VERBOSE_REVERSE_VECTOR_IT)
					std::cout << GR << "Default reverse_iterator constructor" << NC << std::endl;
			};
			explicit reverse_iterator(Iterator x) : _current(x) {
				if (VERBOSE_REVERSE_VECTOR_IT)
					std::cout << GR << "Initialization reverse_iterator constructor" << NC << std::endl;
			};
			template <class U> reverse_iterator(const reverse_iterator<U>& x) : _current(x.base()) {
				if (VERBOSE_REVERSE_VECTOR_IT)
					std::cout << GR << "Copy reverse_iterator constructor" << NC << std::endl;
			};
			reverse_iterator operator=(reverse_iterator const &x) {  
				if (VERBOSE_REVERSE_VECTOR_IT)
					std::cout << GR << "Overload = reverse_iterator" << NC << std::endl;
				_current = x.base(); 
				return *this; 
			};
			~reverse_iterator() {};

			Iterator base() const { return (this->_current); }; // explicit
			reference operator*() const {
				iterator_type	tmp = _current;
				return (*--tmp);
			};
			pointer operator->() const { return (&(operator*())); };
			reference operator[](difference_type n) const { return (*(*this + n)); };

			/* 
			┌───────────────────────────────────────┐
			│       INCREMENT/DECREMENT OP :        │
			└───────────────────────────────────────┘
			*/

			reverse_iterator& operator++() {
				--_current;
				return (*this);
			}; reverse_iterator operator++(int) {
				reverse_iterator	tmp = *this;
				_current--;
				return (tmp);
			}; reverse_iterator& operator--() {
				++_current;
				return (*this);
			}; reverse_iterator operator--(int) {
				reverse_iterator	tmp = *this;
				_current++;
				return (tmp);
			};

			/* 
			┌─────────────────────────────┐
			│      ARITHMETIC OP :        │
			└─────────────────────────────┘
			*/
			reverse_iterator operator+( difference_type n ) const { return (reverse_iterator(_current - n)); };
			reverse_iterator operator-( difference_type n ) const { return (reverse_iterator(_current + n)); };
			reverse_iterator& operator+=( difference_type n ) { 
				_current -= n;
				return (*this);
			}; 
			reverse_iterator& operator-=( difference_type n ) {
				_current += n;
				return (*this);
			};
	};

	template <class Iterator1, class Iterator2>
		bool operator==( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) { return (lhs.base() == rhs. base()); };
	template <class Iterator1, class Iterator2>
		bool operator!=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) { return !(lhs.base() == rhs.base()); };
	template <class Iterator1, class Iterator2>
		bool operator<( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) { return (lhs.base() > rhs.base()); };
	template <class Iterator1, class Iterator2>
		bool operator>( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) { return (lhs.base() < rhs.base()); };
	template <class Iterator1, class Iterator2>
		bool operator>=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) { return (lhs.base() <= rhs.base()); };
	template <class Iterator1, class Iterator2> 
		bool operator<=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) { return (lhs.base() >= rhs.base()); };
	template <class Iterator> 
		reverse_iterator<Iterator> operator+ ( typename reverse_iterator<Iterator>::difference_type _n, const reverse_iterator<Iterator>& i ) { return (reverse_iterator<Iterator>(i.base() - _n)); };
	template <class Iterator> 
		reverse_iterator<Iterator> operator- ( typename reverse_iterator<Iterator>::difference_type _n, const reverse_iterator<Iterator>& i ) { return (reverse_iterator<Iterator>(i.base() + _n)); };
	template <class Iterator1, class Iterator2 >
		typename reverse_iterator<Iterator1>::difference_type operator-( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) { return( rhs.base() - lhs.base());}
}

#endif