#ifndef SET_HPP
# define SET_HPP

#include "includes_set.hpp"

#ifndef SET_VERBOSE
# define SET_VERBOSE 0
#endif 

namespace ft {

	template <class Key,class Compare = ft::less<Key>,class Allocator = std::allocator<Key> > 
	class set {
		public:
			// types: 
			typedef Key																			key_type; 		// Key : type of the keys. Chaque element element d'une map par cette key - map::key_type.
			typedef Key										                                    value_type;
			typedef Compare																		key_compare;	// Compare : prend deux arguments et retourme un booleen. 
																								// -> l'expression comp(a, b) - a et b sont deux keys et 
																								// retourne true si a doit venir avant b en terme de tri. 
																								// Compare permet de determiner l'odre des deux elements. - typedef Compare key_compare.
			typedef Compare																		compare;
			typedef Allocator																	allocator_type; // Allocator : type de l'allocateur, utilise pour definir le modele de stockage qui sera alloue. 
			typedef Node<value_type>															node_type;
			typedef typename allocator_type::reference											reference;
			typedef typename allocator_type::const_reference									const_reference;
			typedef typename std::size_t														size_type;
			typedef typename std::ptrdiff_t														difference_type;
			typedef typename allocator_type::pointer											pointer;
			typedef typename allocator_type::const_pointer										const_pointer;
			typedef typename ft::setRedBlackTree<value_type, key_compare>::iterator				iterator;
			typedef typename ft::setRedBlackTree<value_type, key_compare>::const_iterator		const_iterator;
			typedef ft::reverse_iterator<iterator>												reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> 										const_reverse_iterator;

			class value_compare
				: public ft::binary_function<value_type,value_type,bool> 
			{
				friend class set<Key,Compare,Allocator>;
					protected:
						Compare comp;
						value_compare(Compare c) : comp(c) {}
					public:
						bool operator()(const value_type& x, const value_type& y) const {return comp(x, y); }
			};

			private : 
				size_type											_size;
				key_compare											_compare;
				allocator_type										_allocator;
				setRedBlackTree<value_type, key_compare>			_rbt;
			
			public:
				explicit set(const Compare &comp = Compare(), const Allocator &alloc = Allocator()) {
					if (SET_VERBOSE)
						std::cout << "set default constructor" << std::endl;
					this->_size = 0;
					this->_compare = comp;
					this->_allocator = alloc;
				};
				template <class InputIterator>
				set(InputIterator first, InputIterator last, const Compare &comp = Compare(), const Allocator &alloc = Allocator()) {
					if (SET_VERBOSE)
						std::cout << "set range constructor" << std::endl;
					this->_size = 0;
					this->_compare = comp;
					this->_allocator = alloc;
					for (; first != last; first++)
						this->insert(*first);
				};
				set(const set& x) {
					if (SET_VERBOSE)
						std::cout << "set copy constructor" << std::endl;
					*this = x;
				};
				virtual ~set() {
					if (SET_VERBOSE)
						std::cout << "set destructor" << std::endl;
					if (this->_size > 0)
					{
						this->_rbt.clear();
						this->_size = 0;
					}
				};
				set&	operator=(const set<Key, Compare, Allocator>& x) {
					if (SET_VERBOSE)
						std::cout << "set assignation operator" << std::endl;
					this->_compare = x._compare;
					this->_allocator = x._allocator;
					this->_rbt.clear();
					this->insert(x.begin(), x.end());
					this->_size = x._size;
					return (*this);
				};

				/* 
				┌────────────────────┐
				│     ITERATORS      │
				└────────────────────┘
				*/

				iterator				begin() {return this->_rbt.begin();};
				const_iterator			begin() const {return this->_rbt.begin();};
				iterator				end() {return this->_rbt.end();};
				const_iterator			end() const {return this->_rbt.end();};
				reverse_iterator		rbegin() {return (reverse_iterator(this->end()));};
				const_reverse_iterator	rbegin() const {return (const_reverse_iterator(this->end()));};
				reverse_iterator		rend() {return (reverse_iterator(this->begin()));};
				const_reverse_iterator	rend() const {return (const_reverse_iterator(this->begin()));};

				void	printRBT() {
					this->_rbt.printNode();
				};

				/* 
				┌────────────────────┐
				│     CAPACITY       │
				└────────────────────┘
				*/

				bool					empty() const {return (this->_size == 0 ? true : false) ;};
				size_type				size() const {return this->_size;};
				size_type				max_size() const {return (this->_rbt.maxSize());};

				size_type				count (const key_type& key) {
					if (this->_size > 0 && this->_rbt.find(key) != this->_rbt.end())
						return (1);
					return (0);
				};
				size_type				count (const key_type &key) const {
					if (this->_size > 0 && this->_rbt.find(key) != this->_rbt.end())
						return (1);
					return (0);
				};
				/* 
				┌────────────────────┐
				│     MODIFIERS      │
				└────────────────────┘
				*/

				ft::pair<iterator,bool>	insert(const value_type& val) {
					if (SET_VERBOSE)
						std::cout << "set insert" << std::endl;
					iterator	it;

					if (this->_rbt.find(val) != this->_rbt.end())
						return (ft::make_pair(this->find(val), false));
					it = iterator(this->_rbt.insert(val), NULL);
					this->_size += 1;
					return (ft::make_pair(it, true));
				};
				iterator				insert(iterator position, const value_type& val) {
					if (SET_VERBOSE)
						std::cout << "set insert" << std::endl;
					(void)position;
					iterator ret;
					return (this->insert(val).first);
				};
				template <class InputIterator>
				void					insert(InputIterator first, InputIterator last) {
					if (SET_VERBOSE)
						std::cout << "set insert range" << std::endl;
					for (; first != last; first++)
						this->insert(*first);
				};

				void	erase(iterator position) {
					if (SET_VERBOSE)
						std::cout << "set erase" << std::endl;
					this->erase(*position);
				};
			size_type 									erase( const key_type& key ) { 
				if (this->_size > 0 && this->_rbt.find(key) != this->end()) {
					this->_rbt.erase(key);
					this->_size -= 1;
					return (1); 
				}
				return (0);
			};

				void	erase(iterator first, iterator last) {
					if (SET_VERBOSE)
						std::cout << "set erase range" << std::endl;
					iterator	next = first;
					if (this->_size > 0) {
						for (; first != last; first = next) {
							next++;
							this->erase(first);
						}
					}
				};

				iterator find(const key_type& x) {
					if (SET_VERBOSE)
						std::cout << "set find" << std::endl;
					return (this->_rbt.find(x));
				};

				const_iterator find(const key_type& x) const {
					if (SET_VERBOSE)
						std::cout << "set find" << std::endl;
					return (this->_rbt.find(x));
				};

				void	clear() {
					if (SET_VERBOSE)
						std::cout << "set clear" << std::endl;
					if (this->_size) {
						this->_rbt.clear();
						this->_size = 0;
					}
				};

				iterator		lower_bound(const key_type& key) {
					if (SET_VERBOSE)
						std::cout << "set lower_bound" << std::endl;
					if (this->_size > 0)
						return (this->_rbt.lower_bound(key));
					return (this->end());
				};
				iterator		upper_bound(const key_type& key) {
					if (SET_VERBOSE)
						std::cout << "set upper_bound" << std::endl;
					if (this->_size > 0)
						return (this->_rbt.upper_bound(key));
					return (this->end());
				};
				const_iterator	lower_bound(const key_type& key) const {
					if (SET_VERBOSE)
						std::cout << "set lower_bound" << std::endl;
					if (this->_size > 0)
						return (this->_rbt.lower_bound(key));
					return (this->end());
				};
				const_iterator	upper_bound(const key_type& key) const {
					if (SET_VERBOSE)
						std::cout << "set upper_bound" << std::endl;
					if (this->_size > 0)
						return (this->_rbt.upper_bound(key));
					return (this->end());
				};
				ft::pair<iterator,iterator> 				equal_range( const Key& key ) {
					iterator it = this->find(key);
					return (ft::make_pair(this->_rbt.lower_bound(key), this->_rbt.upper_bound(key)));
				};
				ft::pair<const_iterator,const_iterator> 	equal_range( const Key& key ) const {
					const_iterator it = this->find(key);
					return (ft::make_pair(this->_rbt.lower_bound(key), this->_rbt.upper_bound(key)));
				};

				value_compare value_comp() const {
					if (SET_VERBOSE)
						std::cout << "set value_comp" << std::endl;
					return (this->_compare);
				};

				key_compare key_comp() const {
					if (SET_VERBOSE)
						std::cout << "set key_comp" << std::endl;
					return (this->_compare);
				};
				void 										swap(set& other ) {
					if (SET_VERBOSE)
						std::cout << GR << "Set swap" << NC << std::endl;
					ft::swap(this->_size, other._size);
					this->_rbt.swap(other._rbt);
					ft::swap(this->_allocator, other._allocator);
					ft::swap(this->_compare, other._compare);
			};

			/* 
			┌──────────────────────────┐
			│    COMPARE OPERATORS     │
			└──────────────────────────┘
			*/

			template <class K, class Comp, class Alloc>
				bool operator==(const set<K,Comp,Alloc>& rhs ) const {
				if (this->size() != rhs.size())
					return (false);
				for (typename set<K,Comp,Alloc>::const_iterator it = this->begin(); it != this->end(); it++) {
					if (rhs.find(*it) == rhs.end())
						return (false);
				}
				return (true);
			};
			template< class K, class Comp, class Alloc >
				bool operator!=( const set<K,Comp,Alloc>& rhs ) const {
					return (!(this->operator==(rhs)));
			};
			template< class K, class Comp, class Alloc >
				bool operator<( const set<K,Comp,Alloc>& rhs ) const {
					return (ft::lexicographical_compare(this->begin(), this->end(), rhs.begin(), rhs.end()));
			};
			template< class K, class Comp, class Alloc >
				bool operator<=( const set<K,Comp,Alloc>& rhs ) const {
					return (this->operator==(rhs) || this->operator<(rhs));
			};
			template< class K, class Comp, class Alloc >
				bool operator>( const set<K,Comp,Alloc>& rhs ) const {
					return (!(this->operator<=(rhs)));
			}
			template< class K, class Comp, class Alloc >
				bool operator>=( const set<K,Comp,Alloc>& rhs ) const {
					return (!(this->operator<(rhs)));
			};
		};
		template< class K, class Comp, class Alloc >
		void swap( set<K,Comp,Alloc>& lhs, set<K,Comp,Alloc>& rhs ) {
			lhs.swap(rhs);
		};
}

#endif