#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "includes_vector.hpp"
#include "utils/utils.hpp"

# define TRUE 1
# define FALSE 0

#ifndef VERBOSE_VECTOR
# define VERBOSE_VECTOR 0
#endif 

// Vector : sequence container, c'est-a-dire un groupe de classes template qui est utilise pour 
// stocker des elements. Du faSit que ce sont des templates, ils peuvent stocker n'importe quel
// type d'elements, y compris des classes custom. Utilise des tabeaux alloues dynamiquement. 
// Reallocation si la size depasse la capacite, pas a chaque fois qu'un element est insere.
// Arrangement lineaire. 
// A l'allocation, une plage est allouee, on parle de capacity : 1, 2, 4, 8, 16, 32, 64...
// Random access iterator : Les itérateurs à accès aléatoire sont des itérateurs qui peuvent 
// être utilisés pour accéder à des éléments à une position de décalage arbitraire par rapport 
// à l’élément sur lequel ils pointent, offrant la même fonctionnalité que les pointeurs. 

namespace   ft {

	// Parametres : type - type de donnees des elements a stocker dans le vecteur. 
	//				allocator - Type qui représente l'objet allocateur stocké qui 
	//				contient des informations détaillées sur l'allocation et la désallocation de mémoire du vecteur. 
	//				Cet argument est facultatif et sa valeur par défaut est allocator<Type>.
	template < class Type, class Allocator = std::allocator<Type> > 
	class   vector {

		public :
		//Types
		typedef typename Allocator::reference			reference;
		typedef typename Allocator::const_reference		const_reference;
		typedef typename std::size_t					size_type;
		// Type to represent the difference between two iterators.
		typedef typename std::ptrdiff_t					difference_type;
		typedef Type									value_type; // Type of the elements.
		typedef Allocator								allocator_type;
		typedef typename Allocator::pointer				pointer;
		typedef typename Allocator::const_pointer		const_pointer;
		typedef Type*									iterator;
		typedef const Type*								const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> 	const_reverse_iterator;

		private :
			
			Type*											_array;
			Allocator										_allocator;
			size_type										_capacity;
			size_type										_size;

		public :
			
			/* 
  			┌──────────────────────────────────┐
  			│       construct/copy/destroy:    │
  			└──────────────────────────────────┘
 			*/
			
			explicit 										vector(const Allocator& alloc = Allocator()) {
				if (VERBOSE_VECTOR)
					std::cout << GR << "Vector default constructor" << NC << std::endl;
				_allocator = alloc;
				_capacity = 0;
				_array = NULL;
				_size = 0;
			};

			// Fille constructor : constructs a container with n elements, each elements is a copy of value
			explicit 										vector(size_type n, const Type& value = value_type(), 
															const Allocator& alloc = Allocator()) {
				if (VERBOSE_VECTOR)
					std::cout << GR << "Vector file constructor" << NC << std::endl;
				this->_allocator = alloc;
				this->_size = n;
				this->_capacity = n;
				this->_array = NULL;
				if (n)
					this->_array = _allocator.allocate(_capacity);
				for (size_t i = 0; i < _size; i++)
					_allocator.construct(&_array[i], value);

			};

			// Construit un vecteur avec une range d'elements. Exemple : vector<int> v(10, 42);
			// Enable if : permet de specifier des conditions sur les types de parametres, c'est-a-dire 
			// qu'on doit specifier que le type de parametre est un iterator, et non un int, un char, etc.
			template <class InputIterator>
			vector (InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last,  const Allocator& alloc = Allocator()) {
				if (VERBOSE_VECTOR)
					std::cout << GR << "Vector range constructor" << NC << std::endl;
				this->_allocator = alloc;
				this->_size = ft::distance(first, last);
				this->_capacity = _size;
				this->_array = NULL;
				if (this->capacity())
					this->_array = _allocator.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
				{
					_allocator.construct(&_array[i], *first);
					first++;
				}
			};
			
			// Copy constructor : construct a container with a copy of each of the elements in x, in the same order. 
			vector(const vector<Type,Allocator>& x) {
				if (VERBOSE_VECTOR)
					std::cout << GR << "Vector copy constructor" << NC << std::endl;
				this->_allocator = x.get_allocator();
				this->_size = x.size();
				this->_capacity = x.capacity();
				this->_array = NULL;
				if (this->capacity())
					this->_array = _allocator.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					this->_allocator.construct(&_array[i], x._array[i]);
			};
			~vector() {
				if (VERBOSE_VECTOR)
					std::cout << GR << "Vector default destructor" << NC << std::endl;
				this->clear();
				if (this->_array != NULL)
					this->_allocator.deallocate(_array, _capacity);
			};

			// Operateur = permet d'assigner un vecteur a un autre
			vector& 						operator=(const vector<Type,Allocator>& x) {
				if (VERBOSE_VECTOR)
					std::cout << GR << "Vector = operator overloading =" << NC << std::endl;
				this->clear();
				this->_allocator.deallocate(_array, _capacity);
				this->_allocator = x.get_allocator();
				this->_size = x.size();
				this->_capacity = x._capacity;
				this->_array = this->_allocator.allocate(_capacity);
				for (size_type i = 0; i < this->_size; i++)
					this->_allocator.construct(&_array[i], x._array[i]);
				return (*this);
			};

			/* 
  			┌────────────────────────────────┐
  			│       Relational operators:    │
  			└────────────────────────────────┘
 			*/

			// Operteur == permet de comparer deux vecteurs
			// fonction template : permet de specifier le type de parametre a la compilation
			// On compare la taille, si elle est differente on retourne false
			// Sinon on compare chaque element du vecteur
			template <class T, class Alloc>
  				bool operator==(const vector<T,Alloc>&rhs) const {

				if (this->size() != rhs.size())
					return (false);
				for (size_t i = 0; i < this->_size; i++) {
					if (this->_array[i] != rhs._array[i])
						return (false);
				}
				return (true);
			}

			template <class T, class Alloc>
  				bool operator!=(const vector<T,Alloc>& rhs) const {
					if (this->size() != rhs.size())
						return (true);
					for (size_t i = 0; i < this->_size; i++) {
					if (this->_array[i] != rhs._array[i])
						return (true);
					}
					return (false);
			}

			// lexico_compare : compare deux vecteurs lexicographiquement, c'est a dire en comparant chaque element
			// On compare chaque element du vecteur, si un element est plus petit que l'autre on retourne true
			// Si on arrive a la fin du vecteur et que les deux vecteurs sont egaux on retourne false
			template <class T, class Alloc>
				bool operator<(const vector<T,Alloc>& rhs) const {
					return (ft::lexicographical_compare(this->begin(), this->end(), rhs.begin(), rhs.end()));
			}

			template <class T, class Alloc>
				bool operator>(const vector<T,Alloc>& rhs) const {
					return (rhs < *this);
			}

			template <class T, class Alloc>
				bool operator<=(const vector<T,Alloc>& rhs) const {
					if (ft::lexicographical_compare(this->begin(), this->end(), rhs.begin(), rhs.end()) || *this == rhs)
						return (true);
					else
						return (false);
			}

			template <class T, class Alloc>
				bool operator>=(const vector<T,Alloc>& rhs) const {
					return (!(*this < rhs));
			}	
			/* 
			┌───────────────────────┐
			│       Modifiers:      │
			└───────────────────────┘
			*/

			// La fonction assign permet de remplacer plusieurs éléments du conteneur par une valeur ou par une plage d'éléments.
			template <class InputIterator> void assign (InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last) {
				size_type	distance = ft::distance(first, last);

				this->clear();
				if (distance > this->_capacity) {
					try 
						{ this->reserve(distance); }
					catch (std::exception & e) 
						{ throw std::length_error("Length error: vector::_M_fill_insert"); }
				} for (size_t	i = 0; i < distance; i++) {
					this->_allocator.construct(&_array[i], *first);
					first++;
				}
				this->_size = distance;
			};

			// Assigne une nouvelle valeur à tous les éléments du conteneur, modifie sa taille et sa capacité si nécessaire.
			void 											assign(size_type n, const Type& u) {

				this->clear();
				try 
					{ this->reserve(n); }
				catch (std::exception & e) 
						{ throw std::length_error("Length error: vector::_M_fill_insert"); }
				for (size_t i = 0; i < n; i++)
					this->_allocator.construct(&_array[i], u);
				this->_size = n;
			};
			allocator_type 									get_allocator() const { return (this->_allocator); };

			/* 
			┌───────────────────┐
			│    iterators:     │
			└───────────────────┘
			*/

			iterator										begin() { return (&_array[0]); };
			const_iterator									begin() const { return (&_array[0]); };
			iterator										end() { return (&_array[_size]); };
			const_iterator									end() const { return (&_array[_size]); };
			reverse_iterator								rbegin() { return (reverse_iterator(end())); };
			const_reverse_iterator							rbegin() const { return (const_reverse_iterator(end())); } ;
			reverse_iterator								rend() { return (reverse_iterator(begin())); };
			const_reverse_iterator							rend() const { return (const_reverse_iterator(end())); };

			/* 
			┌─────────────────────┐
			│       capacity:     │
			└─────────────────────┘
			*/

			size_type 										size() const { return (this->_size); };
			// max_size() retourne le nombre maximum d'éléments que peut contenir le conteneur.
			size_type 										max_size() const { return (this->_allocator.max_size()); };

			// La fonction resize permet de modifier la taille du conteneur. 
			// Si la nouvelle taille est supérieure à la taille actuelle, les nouveaux éléments sont initialisés avec une valeur par défaut.
			// Si la nouvelle taille est inférieure à la taille actuelle, les éléments en trop sont supprimés.
			void resize (size_type sz, value_type value = value_type()) {
				if (sz < this->_size) {
					for (size_type i = sz; i < this->_size; i++)
						this->_allocator.destroy(&_array[i]);
					this->_size = sz;
					return ;
				} else if (sz > this->_size && sz > this->_capacity) {
					this->reserve(sz > 2 *this->_size ? sz : 2 * this->_size);
					for (size_type i = this->_size; i < sz; i++)
						this->_allocator.construct(&_array[i], value);
					this->_size = sz;
				} else if (sz > this->_size) {
					for (size_type i = this->_size; i < sz; i++)
						this->_allocator.construct(&_array[i], value);
					this->_size = sz;
				} 
			};
			size_type 										capacity() const { return (this->_capacity); };
			bool											empty() const { return (_size == 0 ? TRUE : FALSE); };

			// La fonction reserve permet de réserver de la mémoire pour le conteneur.
			// Si la nouvelle capacité est inférieure à la capacité actuelle, la fonction ne fait rien.
			// Si la nouvelle capacité est supérieure à la capacité actuelle, la fonction réalloue la mémoire.
			void											reserve(size_type n) { 
				if (n <= this->_capacity)
					return ;
				else if (n > max_size() || n + _capacity > max_size()) {
					throw std::length_error("vector::reserve");
				} else  {
					vector	tmp = *this;
					this->clear();
					this->_allocator.deallocate(_array, _capacity);
					this->_size = tmp.size();
					this->_capacity = n;
					this->_array = this->_allocator.allocate(_capacity);
					for (size_type i = 0; i < this->_size; i++)
						this->_allocator.construct(&_array[i], tmp[i]);
				}
			}; 

			/* 
  			┌────────────────────────────┐
  			│       element access:      │
  			└────────────────────────────┘
 			*/

			reference										operator[](size_type n) { return (this->_array[n]); };
			const_reference									operator[](size_type n) const { return (this->_array[n]); };
			const_reference									at(size_type n) const {
				if (n > this->_size)
					throw std::out_of_range("Out of Range error: vector::_M_range_check");
				return (this->_array[n]);
			};
			
			reference										at(size_type n) {
				if (n > this->_size)
					throw std::out_of_range("Out of Range error: vector::_M_range_check");
				return (this->_array[n]);
			};
			
			reference										front() { return (_array[0]); };
			const_reference									front() const { return (_array[0]); };
			reference										back() { return (_array[_size - 1]); }; 
			const_reference									back() const { return (_array[_size - 1]); };

			/* 
			┌────────────────────────┐
			│       Modifiers        │
			└────────────────────────┘
			*/

			// La fonction push_back permet d'ajouter un élément à la fin du conteneur.
			// Si la taille de mon vecteur est supérieure ou egale à sa capacité, je double sa capacité.
			void 											push_back(const Type& x) {
				if (this->_size == 0 || this->_capacity == 0)
					this->reserve(1);
				else if (_size >= _capacity)
					this->reserve(_size * 2);
				this->_allocator.construct(&_array[_size], x);
				this->_size++;
				return ;
			};
			
			// La fonction pop_back permet de supprimer le dernier élément du conteneur.
			void 											pop_back() {
				if (_size >= 1) {
					_size -= 1;
					this->_allocator.destroy(&_array[_size]);
				}
				return ;
			};
			
			void	printArr() {
				for (size_type i = 0; i < _size; i++)
					std::cout << YEL << _array[i] << NC << std::endl;
				return ;
			};
			
			void	printInfo() {
				std::cout << GR << "Size : " << NC << _size << std::endl;
				std::cout << GR << "Capacity : " << NC << _capacity << std::endl;
				return ;
			};
			
			iterator 										insert(iterator position, const value_type& x) {
				difference_type	positionValue = ft::distance(this->begin(), position);
				vector			tmp = *this;
				size_type		findPos = position - this->begin();
				this->clear();
				this->_allocator.deallocate(_array, _capacity);
				this->_size = tmp.size() + 1;
				if (this->_size > this->_capacity)
				{
					if (this->_size > this->_capacity * 2)
						this->_capacity = this->_size;
					else
						this->_capacity = this->_capacity * 2;
				}
				if (this->_capacity == 0)
					this->_capacity = 1;
				this->_array = this->_allocator.allocate(_capacity);
				size_type	j = 0;
				for (size_type i = 0; i < this->_size; i++) {
					if (i == findPos)
						this->_allocator.construct(&_array[i], x);
					else {
						this->_allocator.construct(&_array[i], tmp[j]);
						j++;
					}
				}
				iterator	it = &_array[positionValue];
				return (it); 
			};
			
			void 											insert(iterator position, size_type n, const value_type& x) {
				if (!n)
					return ;
				size_t	positionValue = ft::distance(this->begin(), position);
				size_t 	i = 0;
				size_t	j = 0;
				vector	tmp = *this;

				this->clear();
				this->_allocator.deallocate(_array, _capacity);
				this->_size = tmp.size() + n;
				if (this->_capacity == 0 || this->_size == 0)
					this->_capacity = n;
				else if (this->_size > tmp._capacity)
				{
					if (tmp._capacity * 2 < this->_size)
						this->_capacity = this->_size;
					else
						this->_capacity = tmp._capacity * 2;
				}
				this->_array = this->_allocator.allocate(_capacity);
				if (positionValue == tmp._size) {
					for (; i < positionValue; i++) { this->_allocator.construct(&_array[i], tmp[i]); }
					for (; i < this->_size; i++) { this->_allocator.construct(&_array[i], x); }
				} else {
					for (; i < positionValue; i++) {
						this->_allocator.construct(&_array[i], tmp[i]);
						j = i + 1;
					} for (size_t toInsert = 0; toInsert < n; toInsert++) {
						this->_allocator.construct(&_array[i], x);
						i++;
					} for (; i < this->_size; i++) {
						this->_allocator.construct(&_array[i], tmp[j]);
						j++;
					}
				}
			};
			
			template <class InputIterator> void 			insert
			(iterator position, InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last) {
				size_t	positionValue = ft::distance(this->begin(), position);
				size_t	dist = ft::distance(first, last);
				size_t 	i = 0;
				size_t	j = 0;
				vector	tmp = *this;

				this->clear();
				this->_allocator.deallocate(_array, _capacity);
				this->_size = tmp.size() + dist;
				if (this->_capacity == 0 || this->_size == 0)
					this->_capacity = dist;
				else if (this->_size > tmp._capacity) {
					if (tmp._capacity * 2 < this->_size)
						this->_capacity = this->_size;
					else
						this->_capacity = tmp._capacity * 2;
				}
				this->_array = this->_allocator.allocate(_capacity);
				if (positionValue == tmp._size) {
					for (; i < positionValue; i++) { this->_allocator.construct(&_array[i], tmp[i]); }
					for (; i < this->_size; i++) { this->_allocator.construct(&_array[i], *first); first++; }
				} else {
					for (; i < positionValue; i++) {
						this->_allocator.construct(&_array[i], tmp[i]);
						j = i + 1;
					} for (size_t toInsert = 0; toInsert < dist; toInsert++) {
						this->_allocator.construct(&_array[i], *first);
						i++;
						first++;
					} for (; i < this->_size; i++) {
						this->_allocator.construct(&_array[i], tmp[j]);
						j++;
					}
				}
			};

			iterator 										erase(iterator position) {
				vector		tmp;
				size_t		oldCapacity = this->_capacity;
				size_t		positionValue = ft::distance(this->begin(), position);

				for (size_t i = 0; i < this->_size; i++)
					if (i != positionValue)
						tmp.push_back(_array[i]);
				this->clear();
				this->_allocator.deallocate(_array, _capacity);
				this->_size = tmp._size;
				this->_capacity = oldCapacity;
				this->_array = this->_allocator.allocate(this->_capacity);
				for (size_t i = 0; i < this->_size; i++)
					this->_allocator.construct(&_array[i], tmp[i]);
				return (position);
			};

			iterator 										erase(iterator first, iterator last) {
				vector		tmp;
				size_t		positionValue = ft::distance(this->begin(), first);
				size_t		dist = ft::distance(this->begin(), last);
				size_t		oldCapacity = this->_capacity;

				for (size_t	i = 0; i < this->size(); i++) {
					if (i == positionValue)
						for (; i < dist - 1; i++) {}
					else
						tmp.push_back(this->_array[i]);
				}
				this->clear();
				this->_allocator.deallocate(_array, _capacity);
				this->_size = tmp._size;
				this->_capacity = oldCapacity;
				this->_array = this->_allocator.allocate(this->_capacity);
				for (size_t i = 0; i < this->_size; i++)
					this->_allocator.construct(&_array[i], tmp[i]);
				return (first);
			};

			void 											swap(vector<Type,Allocator>& x) {
				ft::swap(this->_array, x._array);
				ft::swap(this->_size, x._size);
				ft::swap(this->_capacity, x._capacity);
			};

			void 											clear() {
				if (this->_size == 0)
					return ;
				for (size_type i = 0; i < _size; i++)
					this->_allocator.destroy(&_array[i]);
				this->_size = 0;
			};
	};

	template <class T, class Alloc>
		void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {
		x.swap(y);
	}
}

#endif
