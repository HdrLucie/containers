#ifndef MAP_HPP
# define MAP_HPP

#include "includes_map.hpp"

#ifndef MAP_VERBOSE
# define MAP_VERBOSE 0
#endif 

// Map : associative container, qui stocke de elements qui prennent la forme d'une key value et d'une mapped value.
// La key value est generalement utilisee pour trier et identifier les elements. 
// Le type de la key et de la mapped value doivent differer et former un groupe de type value_type, qui est une paire
// typedef pair<const Key, T> value_type;
// Les elements d'une map sont toujours tries par leur key suivant un ordre tres strict indique par une comparaison 
// d'objets : typedef Compare	key_compare;
// Les mapped values sont directement accessibles par la key qui leur est associee en utilisant l'operateur []
// Map supporte les bidirectionnal iterateurs qui permettent de parcourir la map dans les deux sens.
// Une map est optimisee pour les operations de recherche, d'insertion et de suppression.
namespace   ft {

	template <class Key, class Type, class Compare = ft::less<Key>, class Allocator=std::allocator<ft::pair <const Key, Type> > >
	class map {

		public:
			// types: 
			typedef Key																			key_type; 		// Key : type of the keys. Chaque element element d'une map par cette key - map::key_type.
			typedef Type																		mapped_type;	// T : type de la mapped value - map::mapped_value.
			typedef ft::pair<const key_type, mapped_type>										value_type;
			typedef Compare																		key_compare;	// Compare : prend deux arguments et retourme un booleen. 
																												// -> l'expression comp(a, b) - a et b sont deux keys et 
																												// retourne true si a doit venir avant b en terme de tri. 
																												// Compare permet de determiner l'odre des deux elements. - typedef Compare key_compare.
			typedef Allocator																	allocator_type; // Allocator : type de l'allocateur, utilise pour definir le modele de stockage qui sera alloue. 
			typedef Node<value_type>															node_type;
			typedef typename allocator_type::reference											reference;
			typedef typename allocator_type::const_reference									const_reference;
			typedef typename std::size_t														size_type;
			typedef typename std::ptrdiff_t														difference_type;
			typedef typename allocator_type::pointer											pointer;
			typedef typename allocator_type::const_pointer										const_pointer;
			typedef typename ft::redBlackTree<value_type, key_compare>::iterator				iterator;
			typedef typename ft::redBlackTree<value_type, key_compare>::const_iterator			const_iterator;
			typedef ft::reverse_iterator<iterator>												reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> 										const_reverse_iterator;

			class value_compare
				: public ft::binary_function<value_type,value_type,bool> 
			{
				friend class map<Key,Type,Compare,Allocator>;
					protected:
						Compare comp;
						value_compare(Compare c) : comp(c) {}
					public:
						bool operator()(const value_type& x, const value_type& y) const {return comp(x.first, y.first); }
			};

			private : 
				size_type											_size;
				key_compare											_compare;
				allocator_type										_allocator;
				redBlackTree<value_type, key_compare>				_rbt;

			public :
			/* 
			┌────────────────────────────────┐
			│    MEMBER FUNCTIONS/OPERATOR   │
			└────────────────────────────────┘
			*/

			// Default constructor
			explicit	map(const Compare& comp = key_compare(), const Allocator &alloc = allocator_type()) {
				if (MAP_VERBOSE)
					std::cout << GR << "Map default constructor" << NC << std::endl;
				this->_allocator = alloc;
				this->_size = 0;
				this->_compare = comp;
			};
			// Constructs the container with the contents of the range [first, last). If multiple elements 
			// in the range have keys that compare equivalent, it is unspecified which element is inserted
			template< class InputIterator >
			map(InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()) {
				if (MAP_VERBOSE)
					std::cout << GR << "Map iterator constructor" << NC << std::endl;
				this->_size = 0;
				this->_allocator = alloc;
				this->_compare = comp;
				for (; first != last; first++) {
					this->insert(*first);
				}
			};
			
			// Copy constructor
			map( const map& x) {
				if (MAP_VERBOSE)
					std::cout << GR << "Map copy constructor" << NC << std::endl;
				*this = x;
			};
			
			// Destructor
			virtual ~map() {
				if (MAP_VERBOSE)
					std::cout << GR << "Map default destructor" << NC << std::endl;
				if (this->_size > 0)
				{
					this->_rbt.clear();
					this->_size = 0;
				}
			};

			// Operator =
			map& operator=( const map<Key, Type, Compare, Allocator>& other ) {
				if (MAP_VERBOSE)
					std::cout << GR << "Map overload = operator" << NC << std::endl;
				this->_allocator = other._allocator;
				this->_compare = other._compare;
				this->_rbt.clear();
				this->insert(other.begin(), other.end());
				this->_size = other._size;
				return (*this);
			};

			allocator_type get_allocator() const {return (this->_allocator); };

			/* 
			┌──────────────────────────┐
			│       ELEMENT ACCESS     │
			└──────────────────────────┘
			*/

			mapped_type&											at(const Key& key) {
				iterator it = this->find(key);
				if (it == this->end())
					throw std::out_of_range("map::at");
				return (it->second);
			};
			const mapped_type&									at(const Key& key) const {
				const_iterator it = this->find(key);
				if (it == this->end())
					throw std::out_of_range("map::at");
				return (it->second);
			}
			mapped_type&											operator[](const Key& key) {
				iterator it = this->find(key);
				if (it == this->end())
					this->insert(ft::make_pair(key, mapped_type()));
				return (this->at(key));
			};

			/* 
			┌────────────────────┐
			│     ITERATORS      │
			└────────────────────┘
			*/

			void	printMap() {
				this->_rbt.printNode();
			}

			iterator 									begin() {
				return (this->_rbt.begin());
			};
			const_iterator								begin() const {
				return (this->_rbt.begin());
			};
			iterator									end() {
				return (this->_rbt.end());
			};
			const_iterator								end() const {
				return(this->_rbt.end());
			};
			reverse_iterator 							rbegin() {
				return (reverse_iterator(this->end()));
			};
			const_reverse_iterator						rbegin() const {
				return (const_reverse_iterator(this->end()));
			}
			reverse_iterator 							rend() {
				return (reverse_iterator(this->begin()));
			};
			const_reverse_iterator						rend() const {
				return (const_reverse_iterator(this->begin()));
			};

			/* 
			┌──────────────────────┐
			│       CAPACITY       │
			└──────────────────────┘
			*/

			bool										empty() const {return (this->_size == 0 ? true : false); };
			size_type									size() const {return (this->_size); };
			size_type									max_size() const {return (this->_rbt.maxSize()); };

			/* 
			┌──────────────────────┐
			│       MODIFIERS      │
			└──────────────────────┘
			*/

			void 										clear() {
				if (MAP_VERBOSE)
					std::cout << GR << "Map clear" << NC << std::endl;
				if (this->_size > 0)
				{
					this->_rbt.clear();
					this->_size = 0;
				}
			};
			ft::pair<iterator, bool>				 	insert(const value_type& value) {
				iterator	it;

				if (this->_rbt.find(value.first) != this->_rbt.end())
					return (ft::make_pair(this->find(value.first), false));
				it = iterator(this->_rbt.insert(value), NULL);
				this->_size += 1;
				return (ft::make_pair(it, true));
			};
			iterator 									insert(iterator hint, const value_type& value) {
				(void)hint;
				return (this->insert(value).first);
			};
			template< class InputIterator >
			void	 									insert(InputIterator first, InputIterator last) {
				for (; first != last; first++) {
					this->insert(*first);
				}
			};
			void 										erase(iterator pos) {
				if (this->_size > 0 && pos != this->end()) {
					this->erase(pos->first);
				}
			};
			void 										erase( iterator first, iterator last ) {
				iterator	next = first;
				if (this->_size > 0) {
					for (; first != last; first = next) {
						next++;
						this->erase(first);
					}
				}
			};
			size_type 									erase( const Key& key ) { 
				if (this->_size > 0 && this->_rbt.find(key) != this->end()) {
					this->_rbt.erase(key);
					this->_size -= 1;
					return (1); 
				}
				return (0);
			};
			void 										swap( map& other ) {
				if (MAP_VERBOSE)
					std::cout << GR << "Map swap" << NC << std::endl;
				ft::swap(this->_size, other._size);
				this->_rbt.swap(other._rbt);
				ft::swap(this->_allocator, other._allocator);
				ft::swap(this->_compare, other._compare);
			};

			/* 
			┌──────────────────────┐
			│       LOOKUP         │
			└──────────────────────┘
			*/

			size_type 									count( const Key& key ) {
				if (this->_size > 0 && this->_rbt.find(key) != this->end())
					return (1);
				return (0);
			};
			size_type 									count( const Key& key ) const {
				if (this->_size > 0 && this->_rbt.find(key) != this->end())
					return (1);
				return (0);
			};
			iterator 									find( const Key& key ) {
				return (this->_rbt.find(key));
			};
			const_iterator 								find( const Key& key ) const {
				return (this->_rbt.find(key));
			};
			ft::pair<iterator,iterator> 				equal_range( const Key& key ) {
				iterator it = this->find(key);
				return (ft::make_pair(this->_rbt.lower_bound(key), this->_rbt.upper_bound(key)));
			};
			ft::pair<const_iterator,const_iterator> 	equal_range( const Key& key ) const {
				const_iterator it = this->find(key);
				return (ft::make_pair(this->_rbt.lower_bound(key), this->_rbt.upper_bound(key)));
			};
			iterator 									lower_bound( const Key& key ) {
				if (this->_size > 0)
					return (this->_rbt.lower_bound(key));
				return (this->end());
			};
			const_iterator 								lower_bound( const Key& key ) const {
				if (this->_size > 0)
					return (this->_rbt.lower_bound(key));
				return (this->end());
			}
			iterator 									upper_bound( const Key& key ) {
				if (this->_size > 0)
					return (this->_rbt.upper_bound(key));
				return (this->end());
			};
			const_iterator 								upper_bound( const Key& key ) const {
				if (this->_size > 0)
					return (this->_rbt.upper_bound(key));
				return (this->end());
			};

			/* 
			┌──────────────────────┐
			│      OBSERVERS       │
			└──────────────────────┘
			*/

			// Key_comp() return la fonction de comparaison entre les clés
			key_compare 						key_comp() const {
				return (this->_compare);
			};
			value_compare 						value_comp() const {
				return (this->_compare);
			};

			/* 
			┌──────────────────────────┐
			│    COMPARE OPERATORS     │
			└──────────────────────────┘
			*/

			template <class K, class T, class Comp, class Alloc>
			bool operator==(const map<K,T,Comp,Alloc>& rhs ) const {
				if (this->size() != rhs.size())
					return (false);
				for (typename map<K,T,Comp,Alloc>::const_iterator it = this->begin(); it != this->end(); it++) {
					if (rhs.find(it->first) == rhs.end())
						return (false);
				}
				return (true);
			};
			template< class K, class T, class Comp, class Alloc >
				bool operator!=( const map<K,T,Comp,Alloc>& rhs ) const {
					return (!(this->operator==(rhs)));
				};
			template< class K, class T, class Comp, class Alloc >
				bool operator<( const map<K,T,Comp,Alloc>& rhs ) const {
					return (ft::lexicographical_compare(this->begin(), this->end(), rhs.begin(), rhs.end()));
				};
			template< class K, class T, class Comp, class Alloc >
				bool operator<=( const map<K,T,Comp,Alloc>& rhs ) const {
					return (this->operator==(rhs) || this->operator<(rhs));
				};
			template< class K, class T, class Comp, class Alloc >
				bool operator>( const map<K,T,Comp,Alloc>& rhs ) const {
					return (!(this->operator<=(rhs)));
				}
			template< class K, class T, class Comp, class Alloc >
				bool operator>=( const map<K,T,Comp,Alloc>& rhs ) const {
					return (!(this->operator<(rhs)));
				};
	};

	template< class K, class T, class Comp, class Alloc >
		void swap( map<K,T,Comp,Alloc>& lhs, map<K,T,Comp,Alloc>& rhs ) {
			lhs.swap(rhs);
	};
}

#endif