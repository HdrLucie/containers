#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
#include "pair.hpp"
#include "type_traits.hpp"
#include "make_pair.hpp"
#include "binary_function.hpp"
#include "utils.hpp"
#include "../iterators/iterator_traits.hpp"
#include "define.hpp"

namespace	ft {

		template <class Type>
		class Node {
			public :
			typedef	Type										value_type;
			typedef	Node*										node_pointer;
			typedef const Node*									const_node_pointer;
			typedef Node&										node_reference;
			typedef const Node&									const_node_reference;
			typedef typename std::size_t						size_type;
			typedef typename std::ptrdiff_t						difference_type;

			value_type			_value;
			node_pointer		_parent;
			node_pointer		_left;
			node_pointer		_right;
			size_type			_color;

			Node () : _value() {
				if (NODE_VERBOSE)
					std::cout << GR << "Node default constructor" << NC << std::endl;
				this->_parent = NULL;
				this->_left = NULL;
				this->_right = NULL;
				this->_color = RED_NODE;
				return ;
			}
			Node (const value_type val, node_pointer parent = NULL, node_pointer left = NULL, node_pointer right = NULL) : _value(val) {
				if (NODE_VERBOSE)
					std::cout << GR << "Node initialization constructor" << NC << std::endl;
				this->_parent = parent;
				this->_left = left;
				this->_right = right;
				this->_color = RED_NODE;
				return ;
			}
			Node (const Node<Type>& src) : _value(src._value) {
				if (NODE_VERBOSE)
					std::cout << GR << "Node copy constructor" << NC << std::endl;
				this->_parent = src._parent;
				this->_left = src._left;
				this->_right = src._right;
				this->_color = src._color;
				return ;
			}
			~Node() {
				if (NODE_VERBOSE)
					std::cout << GR << "Node destructor" << NC << std::endl;
				return ;
			}

			Node& operator=(const Node<Type>& rhs) {
				if (NODE_VERBOSE)
					std::cout << GR << "Node overload = operator" << NC << std::endl;
				if (*this == rhs)
					return (*this);
				this->_value = rhs._value;
				this->_parent = rhs._parent;
				this->_left = rhs._left;
				this->_right = rhs._right;
				this->_color = rhs._color;
				return (*this);
			}
			bool	operator==(const Node<Type>& rhs) { return (this->_value == rhs._value); };

			void print(std::fstream &file)
			{
				std::stringstream out;
				out << "\t" << this->_value.first << " [label=\"" << this->_value.first << " [" << this->_value.second << "]\"]";
				if (this->_color == RED_NODE)
					out << " [color=red]";
				out << ";" << std::endl;
				if (this->_left) {
					this->_left->print(file);
					out << "\t" << this->_value.first << " -> " << this->_left->_value.first << "[label=\"L\"];" << std::endl;
				} if (this->_right) {
					this->_right->print(file);
					out << "\t" << this->_value.first << " -> " << this->_right->_value.first << "[label=\"R\"];" << std::endl;
				}
				file << out.str();
			}
	};

	// Mes iterateurs prennent en parametre un type de node, et compare
	// Compare est un type de fonction qui compare deux nodes
	// Ils basent sur les bidirectionnels iterateurs.
	template <class Type, class Compare>
	class map_iterator : ft::iterator<ft::bidirectional_iterator_tag, Type> {
		public :
			typedef Type*																					node_pointer;
			typedef	typename Type::value_type						 										value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference			reference;
			typedef typename std::ptrdiff_t																	difference_type;
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer				pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;
		protected :
			node_pointer	_current;	// node sur lequel on pointe
			node_pointer	_parent;	// node parent qui contient la valeur la plus proche de celle du node courant
										// permet de construire l'iterateur end
		public :
			// Default constructor
			map_iterator(void) : _current(NULL), _parent(NULL) { 
				if (MAP_IT_VERBOSE)
					std::cout << GR << "Map iterators default constructor" << NC << std::endl;
			};
			// Copy Constructor
			explicit map_iterator( node_pointer current, node_pointer end ) : _current(current), _parent(end) {
				if (MAP_IT_VERBOSE)
					std::cout << GR << "Map iterators initialization constructor" << NC << std::endl;
			};
			map_iterator( const map_iterator& x) : _current(x._current), _parent(x._parent) {
				if (MAP_IT_VERBOSE)
					std::cout << GR << "Map iterators copy constructor" << NC << std::endl; 
			};
			// Destructor
			virtual~map_iterator() {
				if (MAP_IT_VERBOSE)
					std::cout << GR << "Map iterators destructor" << NC << std::endl;
			};
			map_iterator	&operator=(map_iterator const &x) {
				if (MAP_IT_VERBOSE)
					std::cout << GR << "Map iterators assignation operator" << NC << std::endl;
				this->_current = x._current;
				this->_parent = x._parent;
				return (*this); 
			};

			reference	operator*() const { 
				return (this->_current->_value); 
			};
			pointer		operator->() const { 
				return (&(this->_current->_value)); 
			};

			node_pointer	getCurrent(void) const {return(this->_current);};
			node_pointer	getParent(void) const {return(this->_parent);};

			bool 				operator==(const map_iterator& x) const { return (this->_current == x._current); }
			bool 				operator!=(const map_iterator& x) const { return (this->_current != x._current); }
			bool 				operator==(node_pointer x) const { return (this->_current == x); }

			/* 
			┌───────────────────────────────────────┐
			│       INCREMENT/DECREMENT OP :        │
			└───────────────────────────────────────┘
			*/

			// Prefix increment
			// Me permet de parcourir mon RBT. 
			// Je check si le node _current a un fils droit, si c'est le cas, je vais vers la droite.
			// Dans le cas contraire, je remonte vers le parent jusqu'a ce que je trouve un parent qui est un fils gauche.
			// Je dois aussi check si je suis a la fin de mon RBT, dans ce cas, je retourne un iterateur a NULL.
			map_iterator&	operator++() {
				if (this->_current) 
				{
					this->_parent = this->_current;
					if (this->_current->_right) 
					{
						this->_current = this->_current->_right;
						while (this->_current->_left)
							this->_current = this->_current->_left;
					} 
					else
					{
						while (this->_current->_parent && this->_current->_parent->_right == this->_current)
							this->_current = this->_current->_parent;
						this->_current = this->_current->_parent;
					}
				}
				return (*this);
			}
			map_iterator	operator++(int) {
				map_iterator	tmp = *this;
				operator++();
				return (tmp);
			}
			// Decrementation. 
			// Me permet de parcourir mon RBT dans le sens inverse.
			// Je check si le node _current a un fils gauche, si c'est le cas, je vais vers la gauche.
			// Dans le cas contraire, je remonte vers le parent jusqu'a ce que je trouve un parent qui est un fils droit.
			// Je dois aussi check si je suis a la fin de mon RBT, dans ce cas, je retourne un iterateur a NULL.
			map_iterator&	operator--() {
				if (RBT_VERBOSE)
					std::cout << GR << "Map iterators decrement operator" << NC << std::endl;
				if (this->_current)
				{
					this->_parent = this->_current;
					if (this->_current->_left) 
					{
						this->_current = this->_current->_left;
						while (this->_current->_right)
							this->_current = this->_current->_right;
					} 
					else 
					{
						while (this->_current->_parent && this->_current->_parent->_left == this->_current)
							this->_current = this->_current->_parent;
						this->_current = this->_current->_parent;
					}
				}
				else 
					this->_current = this->_parent;
				return (*this);
			}

			map_iterator	operator--(int) {
				map_iterator	tmp = *this;
				operator--();
				return (tmp);
			}
	};

	template <class Type, class Compare>
	class map_const_iterator : ft::iterator<ft::bidirectional_iterator_tag, Type> {
		public :
			typedef Type*		 																			const_node_pointer;
			typedef typename Type::value_type const															value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference			reference;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer				pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;
			typedef std::ptrdiff_t																			difference_type;
		protected :
			const_node_pointer	_current; // copie iterateur de base.
			const_node_pointer	_parent;
		public :
			// Default constructor
			map_const_iterator(void) : _current(NULL), _parent(NULL) {
				if (MAP_IT_VERBOSE)
					std::cout << GR << "Map iterators default constructor" << NC << std::endl;
			};
			// // Copy Constructor
			map_const_iterator( const_node_pointer current, const_node_pointer end ) : _current(current), _parent(end) {
				if (MAP_IT_VERBOSE)
					std::cout << GR << "Map iterators initialization constructor" << NC << std::endl;
			};
			map_const_iterator( const map_const_iterator& x) : _current(x._current), _parent(x._parent) {
				if (MAP_IT_VERBOSE)
					std::cout << GR << "Map iterators copy constructor" << NC << std::endl; 
			};
			// ce constructeur permet de convertir un map_iterator en map_const_iterator
			// et de pouvoir utiliser les fonctions de map_const_iterator sur un map_iterator.
			// Je recupere le node courant et le node parent de l'iterateur de base.
			map_const_iterator(const map_iterator<Type, Compare> &it) : _current(it.getCurrent()), _parent(it.getParent()) {
				if (MAP_IT_VERBOSE)
					std::cout << GR << "Map iterators copy constructor" << NC << std::endl;
			};
			// Destructor
			virtual ~map_const_iterator() {
				if (MAP_IT_VERBOSE)
					std::cout << GR << "Map iterators destructor" << NC << std::endl;
			};
			reference operator*(void) const {
				return(this->_current->_value);
			};
			pointer operator->(void) const {
				return(&(operator*()));
			};
			map_const_iterator	&operator=(const map_const_iterator &x) {
				if (MAP_IT_VERBOSE)
					std::cout << GR << "Map iterators assignation operator" << NC << std::endl;
				this->_current = x._current;
				this->_parent = x._parent;
				return (*this); 
			}

			bool 				operator==(const map_const_iterator& x) const { return (this->_current == x._current); }
			bool 				operator!=(const map_const_iterator& x) const { return (this->_current != x._current); }
			bool 				operator==(const_node_pointer x) const { return (this->_current == x); }

			const_node_pointer	getCurrent(void) const {return(this->_current);};
			const_node_pointer	getParent(void) const {return(this->_parent);};

	// 		/* 
	// 		┌───────────────────────────────────────┐
	// 		│       INCREMENT/DECREMENT OP :        │
	// 		└───────────────────────────────────────┘
	// 		*/

			map_const_iterator&	operator++() {
				if (this->_current)
				{
					this->_parent = this->_current;
					if (this->_current->_right) 
					{
						this->_current = this->_current->_right;
						while (this->_current->_left)
							this->_current = this->_current->_left;
					} 
					else 
					{
						while (this->_current->_parent && this->_current->_parent->_right == this->_current)
							this->_current = this->_current->_parent;
						this->_current = this->_current->_parent;
					}
				}
				return (*this);
			}
			map_const_iterator	operator++(int) {
				map_const_iterator	tmp = *this;
				operator++();
				return (tmp);
			}
			map_const_iterator&	operator--() {
				if (this->_current)
				{
					this->_parent = this->_current;
					if (this->_current->_left) 
					{
						this->_current = this->_current->_left;
						while (this->_current->_right)
							this->_current = this->_current->_right;
					} 
					else 
					{
						while (this->_current->_parent && this->_current->_parent->_left == this->_current)
							this->_current = this->_current->_parent;
						this->_current = this->_current->_parent;
					}
					return (*this);
				}
				else
					this->_current = this->_parent;
				return (*this);
			}
			map_const_iterator	operator--(int) {
				map_const_iterator	tmp = *this;
				operator--();
				return (tmp);
			}
	};

	// Proprietes d'un RBT.
	// 1. Une node est rouge ou noir.
	// 2. La racine est noire.
	// 3. Toutes les feuilles/leafs (NULL) sont noires.
	// 4. Si une node est rouge, alors ses enfants sont noirs.
	// 5. Pour chaque node, tous les chemins de la node vers les feuilles/leafs contiennent le meme nombre de noeuds noirs.
	// 6. Toutes les nodes ont deux enfants : d'autres nodes ou des feuilles/leafs (NULL).
	// 7. La nouvelle node inseree est toujours rouge.
	// 8. Apres une insertion, on verifie si les proprietes ne sont pas violees et on les corrige si necessaire (rotation et changement de couleur).
	// L'interet d'un arbre rouge et noir est de garantir un efficacite de recherche, insertion et suppression.

	// Le Type est ma value_type, c'est a dire une pair.
	// Compare est la fonction de comparaison.
	// Node est le type de node que je vais utiliser (cf debut de fichier quoi)
	// Allocator est l'allocator que je vais utiliser.
	template <class Type, class Compare, class Node = ft::Node<Type>, class Allocator = std::allocator<Type> >
	class redBlackTree {
		public:
			typedef	Type																	value_type;
			typedef typename value_type::first_type											key_type;
			typedef	Compare																	key_compare;
			typedef typename std::size_t													size_type;
			typedef typename ft::map_iterator<Node, key_compare>							iterator;
			typedef typename ft::map_const_iterator<Node, key_compare>						const_iterator;
			typedef ft::Node<Type>*															node_pointer;
			typedef const ft::Node<Type>*													const_node_pointer;
			typedef ft::Node<Type>&															node_reference;
			typedef const ft::Node<Type>&													const_node_reference;
			typedef Allocator																allocator_type;
			typedef std::allocator<ft::Node<Type> >											node_allocator;

		protected :
			node_pointer				_root;
			node_pointer				_leaf;
			key_compare					_compare;
			node_allocator				_allocator;

		public :
		redBlackTree() : _root(NULL), _leaf(NULL), _compare(key_compare()), _allocator(node_allocator()) {
			if (RBT_VERBOSE)
				std::cout << GR << "RBT default constructor" << NC << std::endl;
		}
		explicit redBlackTree( const key_compare& comp) : _compare(comp), _allocator(node_allocator()) {
			if (RBT_VERBOSE)
				std::cout << GR << "RBT default constructor" << NC << std::endl;
			this->_root = this->_allocator.allocate(1);
			this->_allocator.construct(this->_root, ft::Node<Type>());
			this->_root->_color = BLACK_NODE;
			this->_root->_parent = NULL;
			this->_root->_left = NULL;
			this->_root->_right = NULL;
			this->_leaf = NULL;
		}
		redBlackTree( const redBlackTree& x ) : _root(NULL), _leaf(NULL), _compare(x._compare), _allocator(x._allocator) {
			if (RBT_VERBOSE)
				std::cout << GR << "RBT copy constructor" << NC << std::endl;
			*this = x;
		}
		
		~redBlackTree() {
			if (RBT_VERBOSE)
				std::cout << GR << "RBT destructor" << NC << std::endl;
		};

		redBlackTree& operator=( const redBlackTree& x ) {
			if (RBT_VERBOSE)
				std::cout << GR << "RBT assignation operator" << NC << std::endl;
			this->_root = x._root;
			this->_leaf = x._leaf;
			return (*this);
		}

		void	printNode() 
		{
			std::fstream file;
			file.open("graph.dot", std::ios::out | std::ios::trunc);
			file << "digraph {" << std::endl;
			file << "\tedge [arrowhead=none];" << std::endl << std::endl;
			if (!this->_root) // single node with label saying empty
				file << "\tempty [label=\"Rien.\", shape=none];" << std::endl;
			else
				this->_root->print(file);
			file << "}" << std::endl;
			file.close();
			return ;
		}

		size_type	maxSize() const {
			if (RBT_VERBOSE)
				std::cout << GR << "RBT size" << NC << std::endl;
			return (this->_allocator.max_size());
		}

		node_pointer	initializationNode ( node_pointer node, const value_type& val ) {
			if (RBT_VERBOSE)
				std::cout << GR << "RBT initializationNode" << NC << std::endl;
			node = this->_allocator.allocate(1);
			this->_allocator.construct(node, Node(val));
			node->_color = RED_NODE;
			node->_parent = NULL;
			node->_left = NULL;
			node->_right = NULL;
			return (node);
		}

		iterator	end() {
			return (iterator(NULL, this->findMax(this->_root)));
		}

		iterator	begin() {
			return (iterator(this->findMin(this->_root), this->_leaf));
		}

		const_iterator	begin() const {
			return (const_iterator(this->findMin(this->_root), this->_leaf));
		}

		const_iterator	end() const {
			return (const_iterator(this->_leaf, this->findMax(this->_root)));
		}

		void	deleteTree(node_pointer node) {
			if (RBT_VERBOSE)
				std::cout << GR << "RBT deleteNode" << NC << std::endl;
			if (node->_left)
				this->deleteTree(node->_left);
			if (node->_right)
				this->deleteTree(node->_right);
			if (node)
			{
				this->_allocator.destroy(node);
				this->_allocator.deallocate(node, 1);
			}
		}

		void	clear() {
			if (RBT_VERBOSE)
				std::cout << GR << "RBT clear" << NC << std::endl;
			if (this->_root)
				deleteTree(this->_root);
			this->_root = NULL;
		}


		/******************
		 * FIND FUNCTIONS *
		 ******************/

		// FindNode me permet de trouver un noeud dans l'arbre
		// C'est plus opti de parcourir l'arbre avec un pointeur plutot qu'avec un iterateur.
		// Je pars de ma racine, si c'est plus petit je go a gauche sinon a droite.
		node_pointer	findNode(const key_type& first) const
		{
			if (RBT_VERBOSE)
				std::cout << GR << "RBT findNode" << NC << std::endl;
			node_pointer node = this->_root;
			while (node != NULL && node->_value.first != first) {
				if (this->_compare(first, node->_value.first))
					node = node->_left;
				else
					node = node->_right;
			}
			return (node);
		}

		iterator	find(const key_type& first) {
			if (RBT_VERBOSE)
				std::cout << GR << "RBT find" << NC << std::endl;
			node_pointer node = NULL;
			node = findNode(first);
			if (node == NULL)
				return (this->end());
			return (iterator(node, NULL));
		}

		const_iterator	find(const key_type& first) const {
			if (RBT_VERBOSE)
				std::cout << GR << "RBT find" << NC << std::endl;
			node_pointer node = NULL;
			node = findNode(first);
			if (node == NULL)
				return (this->end());
			return (const_iterator(node, NULL));
		}

		node_pointer	findMax(node_pointer node) const {
			if (node == this->_leaf)
				return (this->_leaf);
			while (node->_right != this->_leaf)
				node = node->_right;
			return (node);
		}

		node_pointer	findMin(node_pointer node) const
		{
			if (RBT_VERBOSE)
				std::cout << GR << "RBT findMin" << NC << std::endl;
			if (node == this->_leaf)
				return (this->_leaf);
			while (node->_left != this->_leaf)
				node = node->_left;
			return (node);
		}

		/*************************
		 * UTILITY RBT FUNCTIONS *
		 *************************/

		void	leftRotate(node_pointer node) {
			if (RBT_VERBOSE)
				std::cout << GR << "RBT leftRotate" << NC << std::endl;			
			node_pointer	y;

			y = node->_right;
			node->_right = y->_left;
			if (y->_left != this->_leaf)
				y->_left->_parent = node;
			// On donne le parent de node a y
			y->_parent = node->_parent;
			// si node->_parent est NULL, alors node est la racine
			if (node->_parent == this->_leaf)
				this->_root = y;
			else if (node == node->_parent->_left)
				node->_parent->_left = y;
			// Ici on fait en sorte que la node devienne le fils de son fils droit
			else
				node->_parent->_right = y;
			y->_left = node;
			node->_parent = y;
		}

		void	rightRotate(node_pointer node) {
			if (RBT_VERBOSE)
				std::cout << GR << "RBT rightRotate" << NC << std::endl;
			
			node_pointer	y;
			y = node->_left;
			node->_left = y ? y->_right : NULL;
			if (y->_right != this->_leaf)
				y->_right->_parent = node;
			y->_parent = node->_parent;
			if (node->_parent == this->_leaf)
				this->_root = y;
			else if (node == node->_parent->_right)
				node->_parent->_right = y;
			else
				node->_parent->_left = y;
			y->_right = node;
			node->_parent = y;
		}

		// transplant : remplace un noeud par un autre
		void	transplant(node_pointer u, node_pointer v) {
			if (RBT_VERBOSE)
				std::cout << GR << "RBT transplant" << NC << std::endl;
			if (u->_parent == NULL)
				this->_root = v;
			else if (u->_parent->_left && *u == *u->_parent->_left) 
				u->_parent->_left = v;
			else
				u->_parent->_right = v;
			if (v != NULL)
				v->_parent = u->_parent;
		}

		/******************
		 * INSERT FUNCTION *
		 ******************/

		// Insertion d'une node dans un RBT.
		// 1. On check si l'arbre est est vide, si oui on insere la node a la racine et on la colore en noir.
		// 2. Sinon on parcourt l'arbre, on check si la valeur de la node a inserer
		// Je check si la node a inserer est inferieure ou superieur a ma route. 
		// Si elle est inferieure, je regarde a gauche, sinon je regarde a droite.
		// Si elle est deja presente, je la return.
		// Y est le parent de X, c'est a dire le noeud precedent.
		// Puis je cree ma node, je la colore en rouge et je l'insere a gauche ou a droite de Y.
		// Sinon je retourne newnode car elle est deja presente.
		node_pointer insert(const value_type& val) {
			if (RBT_VERBOSE)
				std::cout << GR << "RBT insert" << NC << std::endl;
			node_pointer	newNode = NULL;
			node_pointer	y = NULL;
			node_pointer	x = NULL;

			if (this->_root == this->_leaf)
			{
				this->_root = this->initializationNode(this->_root, val);
				this->_root->_color = BLACK_NODE;
				return (this->_root);
			}
			newNode = initializationNode(newNode, val);
			x = this->_root;
			while (x)
			{
				y = x;
				if (this->_compare(newNode->_value.first, x->_value.first))
					x = x->_left;
				else if (this->_compare(x->_value.first, newNode->_value.first))
					x = x->_right;
				else
					return (x);
			}
			newNode->_parent = y;
			if (this->_compare(newNode->_value.first, y->_value.first))
				y->_left = newNode;
			else if (this->_compare(y->_value.first, newNode->_value.first))
				y->_right = newNode;
			else 
				return (newNode);
			this->insertFix(newNode);
			return (newNode);
		}

		// Quand on insere une node, on peut avoir une violation des propriete du RBT.
		// Le proprietes : tous les noeuds sont soit rouge soit noir, la root est noire, 
		// chaque leaf est noire, si un noeud est rouge alors ses enfants sont noirs et
		// pour chaque noeud, tous les chemins de la node a ses feuilles contiennent le 
		// meme nombre de noeuds noirs.
		// Les cas possibles de violations sont la deuxieme propriete qui exige que la root soit noire,
		// et la quatrieme propriete qui exige que les enfants d'un noeud rouge soient noirs.
		// On tourne dans la boucle while tant que le parent de la node est rouge (ce qui est IMPOSSIIIIIBLE) 
		// La variable parent permet de stocker l'oncle droite ou gauche de la node.
		// Le premier cas (lignes 627 a 632) se passe si le parent de la node et le grand parent sont rouges.
		// Pour resoudre ce cas, on colore le parent et l'oncle (droite ou gauche) en noir.
		// Les right et left rotate permettent de tourner la node et son parent pour que la node soit a gauche de son parent
		void	insertFix (node_pointer node) {

			node_pointer uncle = NULL;

			while (node->_parent && node->_parent->_parent && node->_parent->_color == RED_NODE) {
				if (node->_parent->_parent->_left == node->_parent) {
					uncle = node->_parent->_parent->_right;
					if (uncle && uncle->_color == RED_NODE) {
						node->_parent->_color = BLACK_NODE;
						uncle->_color = BLACK_NODE;
						node->_parent->_parent->_color = RED_NODE;
						node = node->_parent->_parent;
					}
					else {
						if (node->_parent->_right == node) {
							node = node->_parent;
							this->leftRotate(node);
						}
						// Dans ce cas, on a une suite deux de nodes rouges sur une meme ligne.
						// On colore le parent en noir et le grand parent en rouge.
						// et on rotate, le parent devient le parent du grand parent.
						node->_parent->_color = BLACK_NODE;
						node->_parent->_parent->_color = RED_NODE;
						this->rightRotate(node->_parent->_parent);
					}
				}
				else {
					uncle = node->_parent->_parent->_left;
					if (uncle && uncle->_color == RED_NODE) {
						node->_parent->_color = BLACK_NODE;
						uncle->_color = BLACK_NODE;
						node->_parent->_parent->_color = RED_NODE;
						node = node->_parent->_parent;
					}
					else {
						if (node->_parent->_left == node) {
							node = node->_parent;
							this->rightRotate(node);
						}
						node->_parent->_color = BLACK_NODE;
						node->_parent->_parent->_color = RED_NODE;
						this->leftRotate(node->_parent->_parent);
					}
				}
			}
			this->_root->_color = BLACK_NODE;
			return ;
		}

		/*******************
		 * ERASE FUNCTIONS *
		 *******************/

		// eraseFix permet d'équilibrer l'arbre suite à la suppression d'une node. 
		void	eraseFix(node_pointer x) {
			if (RBT_VERBOSE)
				std::cout << GR << "RBT eraseFix" << NC << std::endl;
			node_pointer	node = NULL;

			if (x == NULL)
				return ;
			while (this->_root && x->_parent && x->_color == BLACK_NODE) {
					if (x->_parent->_left && *x == *x->_parent->_left) 
					{
						node = x->_parent->_left;
						if (node && node->_color == RED_NODE) {
							node->_color = BLACK_NODE;
							x->_parent->_color = RED_NODE;
							this->leftRotate(x->_parent);
							node = x->_parent->_right;
						} else if (node->_left && node->_left->_color == BLACK_NODE && node->_right->_color == BLACK_NODE) {
							node->_color = RED_NODE;
							x = x->_parent;
						} else if (node->_right == BLACK_NODE) {
							if (node->_left)
								node->_left->_color = BLACK_NODE;
							node->_color = RED_NODE;
							if (node->_left)
								this->rightRotate(node);
							node = x->_parent->_right;
						}
						else {
							node->_color = x->_parent->_color;
							x->_parent->_color = BLACK_NODE;
							node->_right->_color = BLACK_NODE;
							this->leftRotate(x->_parent);
							x = this->_root;
						} 
					} 
					else 
					{
						node = x->_parent->_right;
						if (node && node->_color == RED_NODE) {
							node->_color = BLACK_NODE;
							x->_parent->_color = RED_NODE;
							this->rightRotate(x->_parent);
							node = x->_parent->_left;
						}
						else if (node->_right->_color == BLACK_NODE && node->_left->_color == BLACK_NODE) {
							node->_color = RED_NODE;
							x = x->_parent;
						} else if (node->_left == BLACK_NODE) {
							if (node->_right)
								node->_right->_color = BLACK_NODE;
							node->_color = RED_NODE;
							if (node->_right)
								this->leftRotate(node);
							node = x->_parent->_left;
						}
						else {
							node->_color = x->_parent->_color;
							x->_parent->_color = BLACK_NODE;
							node->_left->_color = BLACK_NODE;
							this->rightRotate(x->_parent);
							x = this->_root;
						}
					}
				}
			x->_color = BLACK_NODE;
		}

		// erase : supprime un noeud de l'arbre
		void	erase( const key_type& val ) {
			if (RBT_VERBOSE)
				std::cout << GR << "RBT delete" << NC << std::endl;
			node_pointer	node = NULL;
			node_pointer	x = NULL;
			node_pointer	y = NULL;
			size_type		originalColor;

			node = findNode(val);
			originalColor = node->_color;
			if (node->_left == NULL) {
				x = node->_right;
				this->transplant(node, x);
			} else if (node->_right == NULL) {
				x = node->_left;
				this->transplant(node, x);
			} else {
				y = this->findMax(node->_left);
				originalColor = y->_color;
				x = y->_left;
				if (*y->_parent == *node) { 
					if (x != NULL)
						x->_parent = y;
				} else {
					this->transplant(y, y->_left);
					y->_left = node->_left;
					y->_left->_parent = y;
				}
				this->transplant(node, y);
				y->_right = node->_right;
				y->_right->_parent = y;
				y->_color = originalColor;
			}
			this->_allocator.destroy(node);
			this->_allocator.deallocate(node, 1);
			if (originalColor == BLACK_NODE)
				this->eraseFix(x);
		}

		// upper_bound return l'iterateur du premier element superieur a k
		// Si la key a chercher est plus grande que le dernier element, return end()
		// Si la key a chercher est plus petite que le premier element, return begin()
		// Si la key a chercher est egale a un element, return l'iterateur de l'element suivant
		// Si la key a chercher n'est pas dans l'arbre, return l'iterateur de l'element suivant
		iterator	upper_bound(const key_type& toFind) {
			if (RBT_VERBOSE)
				std::cout << GR << "RBT uper_bound" << NC << std::endl;

			node_pointer	node = this->_root;
			iterator		it;

			if (toFind >= this->findMax(this->_root)->_value.first)
				return (this->end());
			if (toFind < this->findMin(this->_root)->_value.first)
				return (this->begin());
			while (node->_right != NULL) {
				if (node->_value.first > toFind) {
					if (node->_left == NULL)
						return (iterator(node, this->_leaf));
					node = node->_left;
				} else if (node->_value.first < toFind) {
					if (node->_right == NULL)
						return (iterator(node, this->_leaf));
					node = node->_right;
				} else if (node->_value.first == toFind && node->_right != NULL) {
					it = iterator(node, this->_leaf);
					return (++it);
				}
			}
			if (node->_value.first > toFind && node->_right == NULL)
				return (iterator(node, this->_leaf));
			iterator tmp(node, this->_leaf);
			return (iterator(++tmp));
		}

		const_iterator upper_bound(const key_type& toFind) const {
			if (RBT_VERBOSE)
				std::cout << GR << "RBT const uper_bound" << NC << std::endl;

			node_pointer	node = this->_root;
			const_iterator		it;

			if (toFind >= this->findMax(this->_root)->_value.first)
				return (this->end());
			if (toFind < this->findMin(this->_root)->_value.first)
				return (this->begin());
			while (node->_right != NULL) {
				if (node->_value.first > toFind) {
					if (node->_left == NULL)
						return (const_iterator(node, this->_leaf));
					node = node->_left;
				} else if (node->_value.first < toFind) {
					if (node->_right == NULL)
						return (const_iterator(node, this->_leaf));
					node = node->_right;
				} else if (node->_value.first == toFind && node->_right != NULL) {
					it = const_iterator(node, this->_leaf);
					return (++it);
				}
			}
			if (node->_value.first > toFind && node->_right == NULL)
				return (const_iterator(node, this->_leaf));
			const_iterator tmp(node, this->_leaf);
			return (const_iterator(++tmp));
		}

		// Lower_bound, return un iterateur qui pointe sur la key passee en parametre
		// Si la key n'existe pas, renvoie l'iterateur sur la key suivante.
		iterator	lower_bound(const key_type& toFind) {
			if (RBT_VERBOSE)
				std::cout << GR << "RBT lower_bound" << NC << std::endl;

			node_pointer	node = this->_root;
			iterator		it;

			while (node->_right != NULL) {
				if (node->_value.first > toFind) {
					if (node->_left == NULL)
						return (iterator(node, this->_leaf));
					node = node->_left;
				} else if (node->_value.first < toFind) {
					if (node->_right == NULL)
						return (iterator(node, this->_leaf));
					node = node->_right;
				} else if (node->_value.first == toFind)
					return (iterator(node, this->_leaf));
			}
			if (toFind > this->findMax(this->_root)->_value.first)
				return (this->end());
			it = iterator(node, this->_leaf);
			return (toFind > node->_value.first ? ++it : it);
		}


		const_iterator lower_bound(const key_type& toFind) const {
			if (RBT_VERBOSE)
				std::cout << GR << "RBT const lower_bound" << NC << std::endl;

			node_pointer	node = this->_root;
			const_iterator		it;

			while (node->_right != NULL) {
				if (node->_value.first > toFind) {
					if (node->_left == NULL)
						return (const_iterator(node, this->_leaf));
					node = node->_left;
				} else if (node->_value.first < toFind) {
					if (node->_right == NULL)
						return (const_iterator(node, this->_leaf));
					node = node->_right;
				} else if (node->_value.first == toFind)
					return (const_iterator(node, this->_leaf));
			}
			if (toFind > this->findMax(this->_root)->_value.first)
				return (this->end());
			it = const_iterator(node, this->_leaf);
			return (toFind > node->_value.first ? ++it : it);
		}

		node_pointer	getRoot() const {
			return (this->_root);
		}

		void	swap(redBlackTree& x) {
			if (RBT_VERBOSE)
				std::cout << GR << "RBT swap" << NC << std::endl;

			ft::swap(this->_root, x._root);
			ft::swap(this->_leaf, x._leaf);
			ft::swap(this->_compare, x._compare);
		};
	};
}

#endif
