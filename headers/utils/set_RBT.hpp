#ifndef SET_RBT_HPP
#define SET_RBT_HPP

#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
#include "pair.hpp"
#include "type_traits.hpp"
#include "make_pair.hpp"
#include "binary_function.hpp"
#include "../iterators/iterator_traits.hpp"
#include "define.hpp"
#include "utils.hpp"

namespace ft {
	
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
			out << "\t" << this->_value << " [label=\"" << this->_value << "\"]" << std::endl;
			if (this->_color == RED_NODE)
				out << " [color=red]";
			out << ";" << std::endl;
			if (this->_left) {
				this->_left->print(file);
				out << "\t" << this->_value << " -> " << this->_left->_value << "[label=\"L\"];" << std::endl;
			} if (this->_right) {
				this->_right->print(file);
				out << "\t" << this->_value << " -> " << this->_right->_value << "[label=\"R\"];" << std::endl;
			}
			file << out.str();
		}
	};

	template <class Type, class Compare>
	class const_set_iterators;
	template <class Type, class Compare>
	class set_iterators : ft::iterator<ft::bidirectional_iterator_tag, Type> {
		public:
			typedef Type*																					node_pointer;
			typedef	typename Type::value_type const						 										value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference			reference;
			typedef typename std::ptrdiff_t																	difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer				pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;

		private:
			node_pointer	_current;
			node_pointer	_parent;

		public:
			// Constructors
			set_iterators() : _current(NULL), _parent(NULL) {
				if (SET_IT_VERBOSE)
					std::cout << GR << "Set iterators default constructor" << NC << std::endl;
			};
			explicit set_iterators(node_pointer current, node_pointer end) : _current(current), _parent(end) {
				if (SET_IT_VERBOSE)
					std::cout << GR << "Set iterators constructor" << NC << std::endl;
			};
			set_iterators(const set_iterators &x) : _current(x._current), _parent(x._parent) {
				if (SET_IT_VERBOSE)
					std::cout << GR << "Set iterators copy constructor" << NC << std::endl;
			};
			set_iterators(const const_set_iterators<Type, Compare> &x) : _current(x.getCurrent()), _parent(x.getParent()) {
				if (SET_IT_VERBOSE)
					std::cout << GR << "Set iterators copy constructor" << NC << std::endl;
			};
			// Destructor
			virtual ~set_iterators() {
				if (SET_IT_VERBOSE)
					std::cout << GR << "Set iterators destructor" << NC << std::endl;
			};
			reference operator*(void) const {
				return(this->_current->_value);
			};
			pointer operator->(void) const {
				return(&(operator*()));
			};
			set_iterators	&operator=(set_iterators const &x) {
				if (SET_IT_VERBOSE)
					std::cout << GR << "Set iterators assignation operator" << NC << std::endl;
				this->_current = x._current;
				this->_parent = x._parent;
				return (*this); 
			};

			node_pointer		getCurrent(void) const { return (this->_current); };
			node_pointer		getParent(void) const { return (this->_parent); };

			bool 				operator==(const set_iterators& x) const { return (this->_current == x._current); };
			bool 				operator!=(const set_iterators& x) const { return (this->_current != x._current); };
			bool 				operator==(const node_pointer x) const { return (this->_current == x); };

			/* 
			┌───────────────────────────────────────┐
			│       INCREMENT/DECREMENT OP :        │
			└───────────────────────────────────────┘
			*/

			set_iterators&		operator++() {
				if (this->_current != this->_parent) 
				{
					this->_parent = this->_current;
					if (this->_current->_right) {
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
					return (*this);
				}
				else
					this->_current = this->_parent;
				return (*this);
			};
			set_iterators		operator++(int) {
				set_iterators tmp(*this);
				operator++();
				return (tmp);
			};

			set_iterators&		operator--() {
				if (this->_current)
				{
					this->_parent = this->_current;
					if (this->_current->_left) {
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
			};
			set_iterators		operator--(int) {
				set_iterators tmp(*this);
				operator--();
				return (tmp);
			};
	};

	template <class Type, class Compare>
	class	const_set_iterators : ft::iterator<ft::bidirectional_iterator_tag, Type> {
		public : 
			typedef Type*																					node_pointer;
			typedef	typename Type::value_type const						 									value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference			reference;
			typedef typename std::ptrdiff_t																	difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer				pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;
	
		private:
			node_pointer		_current;
			node_pointer		_parent;
		
		public : 
			const_set_iterators() : _current(NULL), _parent(NULL) {};
			explicit const_set_iterators(node_pointer x, node_pointer y) : _current(x), _parent(y) {};
			const_set_iterators(const const_set_iterators& x) : _current(x._current), _parent(x._parent) {};
			const_set_iterators(const set_iterators<Type, Compare>& x) : _current(x.getCurrent()), _parent(x.getParent()) {};
			virtual ~const_set_iterators() {};
			const_set_iterators&	operator=(const const_set_iterators& x) {
				this->_current = x._current;
				this->_parent = x._parent;
				return (*this);
			};

			bool 				operator==(const_set_iterators x) const { return (this->_current == x._current); };
			bool 				operator!=(const_set_iterators x) const { return (this->_current != x._current); };
			bool				operator==(node_pointer x) const { return (this->_current == x); };

			node_pointer		getCurrent() const { return (this->_current); };
			node_pointer		getParent() const { return (this->_parent); };

			reference			operator*() const { return (this->_current->_value); };
			pointer				operator->() const { return (&(this->_current->_value)); };

			const_set_iterators&		operator++() {
				if (this->_current)
				{
					this->_parent = this->_current;
					if (this->_current->_right) {
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
			};
			const_set_iterators		operator++(int) {
				const_set_iterators tmp(*this);
				operator++();
				return (tmp);
			};

			const_set_iterators&		operator--() {
				if (this->_current)
				{
					if (this->_current->_left) {
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
			};
			const_set_iterators		operator--(int) {
				const_set_iterators tmp(*this);
				operator--();
				return (tmp);
			};
	};

	template <class Type, class Compare, class Node = ft::Node<Type>, class Allocator = std::allocator<Type> >
	class setRedBlackTree {
		public:
			typedef Type																	value_type;
			typedef Compare																	key_compare;
			typedef typename std::size_t													size_type;
			typedef ft::Node<Type>*															node_pointer;
			typedef const ft::Node<Type>*													const_node_pointer;
			typedef ft::Node<Type>&															node_reference;
			typedef const ft::Node<Type>&													const_node_reference;
			typedef Allocator																allocator_type;
			typedef std::allocator<ft::Node<Type> >											node_allocator;
			typedef typename ft::set_iterators<Node, key_compare>							iterator;
			typedef typename ft::const_set_iterators<Node, key_compare>						const_iterator;

		protected:
			node_pointer		_root;
			node_pointer		_leaf;
			key_compare			_compare;
			node_allocator		_allocator;
		public:
			setRedBlackTree() : _root(NULL), _leaf(NULL), _compare(key_compare()), _allocator(node_allocator()) {};
			explicit setRedBlackTree (const value_type& comp) : _compare(comp), _allocator(node_allocator()) {
				if (SET_RBT_VERBOSE)
					std::cout << "setRedBlackTree constructor" << std::endl;
				this->_root = this->_allocator.allocate(1);
				this->_allocator.construct(this->_root, ft::Node<Type>());
				this->_root->_color = BLACK_NODE;
				this->_root->_parent = NULL;
				this->_root->_left = NULL;
				this->_root->_right = NULL;
			};
			setRedBlackTree (const setRedBlackTree& x) : _root(NULL), _leaf(NULL), _compare(x._compare), _allocator(x._allocator) {
				if (SET_RBT_VERBOSE)
					std::cout << "setRedBlackTree copy constructor" << std::endl;
				*this = x;
			};
			virtual ~setRedBlackTree() {
				if (SET_RBT_VERBOSE)
					std::cout << "setRedBlackTree destructor" << std::endl;
			};
			setRedBlackTree&	operator=(const setRedBlackTree& x) const {
				if (SET_RBT_VERBOSE)
					std::cout << "setRedBlackTree assignation operator" << std::endl;
				this->_root = x._root;
				this->_leaf = x._leaf;
				return (*this);
			};

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

		void	leftRotate( node_pointer node ) {
			if (RBT_VERBOSE)
				std::cout << GR << "RBT leftRotate" << NC << std::endl;
			
			node_pointer	y;
			y = node->_right;
			node->_right = y->_left;
			if (y->_left != this->_leaf)
				y->_left->_parent = node;
			y->_parent = node->_parent;
			if (node->_parent == this->_leaf)
				this->_root = y;
			else if (node == node->_parent->_left)
				node->_parent->_left = y;
			else
				node->_parent->_right = y;
			y->_left = node;
			node->_parent = y;
		}

		void	rightRotate( node_pointer node ) {
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

		iterator	begin() {
			return (iterator(this->findMin(this->_root), this->_leaf));
		}

		const_iterator	begin() const {
			return (const_iterator(this->findMin(this->_root), this->_leaf));
		}

		iterator	end() {
			return (iterator(this->_leaf, this->findMax(this->_root)));
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

		node_pointer	findNode(const value_type& first) const
		{
			if (RBT_VERBOSE)
				std::cout << GR << "RBT findNode" << NC << std::endl;
			node_pointer node = NULL;
			node = this->_root;
			while (node != NULL && node->_value != first) {
				if (this->_compare(first, node->_value))
					node = node->_left;
				else
					node = node->_right;
			}
			return (node);
		}
		// const value_type& first correspond à la clef à chercher.
		// Je regarde par rapport a la root si la clef est plus grande ou plus petite.
		// Si ma key est plus petite que ma racine, je parcours de mon begin a ma root,
		// si elle est plus grande, je parcours de ma root a mon end.
		// Je retourne un iterateur sur le noeud trouvé.
		iterator	find(const value_type& first) {
			if (RBT_VERBOSE)
				std::cout << GR << "RBT find" << NC << std::endl;
			node_pointer node = NULL;
			node = findNode(first);
			if (node == NULL)
				return (this->end());
			return (iterator(node, NULL));
		}

		const_iterator	find(const value_type& first) const {
			if (RBT_VERBOSE)
				std::cout << GR << "RBT find" << NC << std::endl;
			node_pointer node = NULL;
			node = findNode(first);
			if (node == NULL)
				return (this->end());
			return (const_iterator(node, NULL));
		}

		// Proprietes d'un RBT.
		// 1. Une node est rouge ou noir.
		// 2. La racine est noire.
		// 3. Toutes les feuilles/leafs (NULL) sont noires.
		// 4. Si une node est rouge, alors ses enfants sont noirs.
		// 5. Pour chaque node, tous les chemins de la node vers les feuilles/leafs contiennent le meme nombre de noeuds noirs.
		// 6. Toutes les nodes ont deux enfants : d'autres nodes ou des feuilles/leafs (NULL).
		// 7. La nouvelle node inseree est toujours rouge.
		// 8. Apres une insertion, on verifie si les proprietes ne sont pas violees et on les corrige si necessaire (rotation et changement de couleur).

		// Insertion d'une node dans un RBT.
		// 1. On check si l'arbre est est vide, si oui on insere la node a la racine et on la colore en noir.
		// 2. Sinon on parcourt l'arbre, on check si la valeur de la node a inserer
		// Je check si la node a inserer est inferieure ou superieur a ma route. 
		// Si elle est inferieure, je regarde a gauche, sinon je regarde a droite.
		// Si elle est deja presente, je la return.
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
				if (this->_compare(newNode->_value, x->_value))
					x = x->_left;
				else if (this->_compare(x->_value, newNode->_value))
					x = x->_right;
				else
					return (x);
			}
			newNode->_parent = y;
			if (this->_compare(newNode->_value, y->_value))
				y->_left = newNode;
			else if (this->_compare(y->_value, newNode->_value))
				y->_right = newNode;
			else 
				return (newNode);
			this->insertFix(newNode);
			return (newNode);
		}

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

		// transplant : remplace un noeud par un autre
		// 1. Si le parent du noeud a remplacer est NULL, alors le noeud a remplacer est la racine
		// 2. Si le noeud a remplacer est le fils gauche de son parent, alors le noeud a remplacer est le fils gauche de son parent
		// 3. Si le noeud a remplacer est le fils droit de son parent, alors le noeud a remplacer est le fils droit de son parent
		// 4. Si le noeud a remplacer est NULL, alors le noeud a remplacer est NULL
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

		node_pointer	findMax(node_pointer node) const {
			if (node == this->_leaf)
				return (this->_leaf);
			while (node->_right != this->_leaf)
				node = node->_right;
			return (node);
		}

		// erase : supprime un noeud de l'arbre
		void	erase( const value_type& val ) {
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
		iterator	upper_bound(const value_type& toFind) {
			if (RBT_VERBOSE)
				std::cout << GR << "RBT uper_bound" << NC << std::endl;

			node_pointer	node = this->_root;
			iterator		it;

			if (toFind >= this->findMax(this->_root)->_value)
				return (this->end());
			if (toFind < this->findMin(this->_root)->_value)
				return (this->begin());
			while (node->_right != NULL) {
				if (node->_value > toFind) {
					if (node->_left == NULL)
						return (iterator(node, this->_leaf));
					node = node->_left;
				} else if (node->_value < toFind) {
					if (node->_right == NULL)
						return (iterator(node, this->_leaf));
					node = node->_right;
				} else if (node->_value == toFind && node->_right != NULL) {
					it = iterator(node, this->_leaf);
					return (++it);
				}
			}
			if (node->_value > toFind && node->_right == NULL)
				return (iterator(node, this->_leaf));
			iterator tmp(node, this->_leaf);
			return (iterator(++tmp));
		}

		const_iterator upper_bound(const value_type& toFind) const {
			if (RBT_VERBOSE)
				std::cout << GR << "RBT const uper_bound" << NC << std::endl;

			node_pointer	node = this->_root;
			const_iterator	it;

			if (toFind >= this->findMax(this->_root)->_value)
				return (this->end());
			if (toFind < this->findMin(this->_root)->_value)
				return (this->begin());
			while (node->_right != NULL) {
				if (node->_value > toFind) {
					if (node->_left == NULL)
						return (iterator(node, this->_leaf));
					node = node->_left;
				} else if (node->_value < toFind) {
					if (node->_right == NULL)
						return (iterator(node, this->_leaf));
					node = node->_right;
				} else if (node->_value == toFind && node->_right != NULL) {
					it = iterator(node, this->_leaf);
					return (++it);
				}
			}
			if (node->_value > toFind && node->_right == NULL)
				return (iterator(node, this->_leaf));
			iterator tmp(node, this->_leaf);
			return (++tmp);
		}

		// Lower_bound, return un iterateur qui pointe sur la key passee en parametre
		// Si la key n'existe pas, renvoie l'iterateur sur la key suivante.
		iterator	lower_bound(const value_type& toFind) {
			if (RBT_VERBOSE)
				std::cout << GR << "RBT lower_bound" << NC << std::endl;

			node_pointer	node = this->_root;
			iterator		it;

			while (node->_right != NULL) {
				if (node->_value > toFind) {
					if (node->_left == NULL)
						return (iterator(node, this->_leaf));
					node = node->_left;
				} else if (node->_value < toFind) {
					if (node->_right == NULL)
						return (iterator(node, this->_leaf));
					node = node->_right;
				} else if (node->_value == toFind)
					return (iterator(node, this->_leaf));
			}
			if (toFind > this->findMax(this->_root)->_value)
				return (this->end());
			it = iterator(node, this->_leaf);
			return (toFind > node->_value ? ++it : it);
		}


		const_iterator lower_bound(const value_type& toFind) const {
			if (RBT_VERBOSE)
				std::cout << GR << "RBT const lower_bound" << NC << std::endl;

			node_pointer	node = this->_root;
			const_iterator		it;

			while (node->_right != NULL) {
				if (node->_value > toFind) {
					if (node->_left == NULL)
						return (iterator(node, this->_leaf));
					node = node->_left;
				} else if (node->_value < toFind) {
					if (node->_right == NULL)
						return (iterator(node, this->_leaf));
					node = node->_right;
				} else if (node->_value == toFind)
					return (iterator(node, this->_leaf));
			}
			if (toFind > this->findMax(this->_root)->_value)
				return (this->end());
			it = iterator(node, this->_leaf);
			return (toFind > node->_value ? ++it : it);
		}

		void	swap(setRedBlackTree& x) {
			if (RBT_VERBOSE)
				std::cout << GR << "set RBT swap" << NC << std::endl;

			ft::swap(this->_root, x._root);
			ft::swap(this->_leaf, x._leaf);
			ft::swap(this->_compare, x._compare);
		};
	};
}

#endif