/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hadd <ael-hadd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 09:31:53 by ael-hadd          #+#    #+#             */
/*   Updated: 2022/09/11 16:40:14 by ael-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include	<iostream>
#include "functional.hpp"
// #include "iterators.hpp"

namespace	ft
{

	enum node_color {BLACK, RED};
	
	
	template<typename T>
	struct Node
	{
		typedef T			value_type;
		typedef Node<T>*	node_pointer;

		value_type		key;
		node_color		color;
		node_pointer		parent;
		node_pointer		right;
		node_pointer		left;
		
		Node(const value_type& key = value_type(), node_color color = RED) 
			: key(key), color(color), parent(nullptr), right(nullptr), left(nullptr)	{}
		bool	isRoot()	{ return (!parent); }
		bool isLeft()	{ return (parent && parent->left == this); }
		bool	isRight()	{ return (parent && parent->right == this); }
		bool isBlack()	{ return (color == BLACK); }
		bool isRed()	{ return (color == RED); }
		
	};

	template<typename T, class Compare, typename Alloc = std::allocator<Node<T> > >
	class RBTree
	{
		public:
			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef ft::Node<value_type>							node_type;
			typedef typename ft::Node<value_type>::node_pointer		node_pointer;
			typedef size_t										size_type;


			// typedef ft::RBiterator<value_type, node_pointer>					iterator;
			// typedef ft::RBiterator<const value_type, node_pointer>				const_iterator;
			// typedef ft::reverse_iterator<iterator>							reverse_iterator;
			// typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;
		private:
			node_pointer		root;
			node_pointer		NIL;
			node_pointer		_first;
			node_pointer		_last;
			allocator_type		_allocator;
			Compare			_comp;
			size_type			_size;
		protected:
			void	leftRotate(node_pointer ptr)	{
				node_pointer	r_node = ptr->right;
				ptr->right = r_node->left;
				if (r_node->left != NIL)
					r_node->left->parent = ptr;
				r_node->parent = ptr->parent;
				if (!ptr->parent)
					this->root = r_node;
				else	if (ptr->isLeft())
					ptr->parent->left = r_node;
				else 
					ptr->parent->right = r_node;
				r_node->left = ptr;
				ptr->parent = r_node;
			}

			void	rightRotate(node_pointer ptr)	{
				node_pointer	l_node = ptr->left;
				ptr->left = l_node->right;
				if (l_node->right != NIL)
					l_node->right->parent = ptr;
				l_node->parent = ptr->parent;
				if (!ptr->parent)
					this->root = l_node;
				else if (ptr->isLeft())
					ptr->parent->left = l_node;
				else
					ptr->parent->right = l_node;
				l_node->right = ptr;
				ptr->parent = l_node;
			}

			node_pointer	minNode(node_pointer root)	{
				node_pointer node = root;
				while (node->left != NIL)
					node = node->left;
				return (node);
			}

			node_pointer	maxNode(node_pointer root)	{
				node_pointer node = root;
				while (node->right != NIL)
					node = node->right;
				return (node);
			}
			
			node_pointer BSTinsertion(node_pointer ptr, node_pointer node)	{
				if (ptr == NIL || ptr == _last)	{
					ptr = node;	
				}
				else if (_comp(node->key, ptr->key))	{
					ptr->left = BSTinsertion(ptr->left, node);
					ptr->left->parent = ptr;
				}
				else {
					ptr->right = BSTinsertion(ptr->right, node);
					ptr->right->parent = ptr;
				}
				return (ptr);
			}

			void	insertionFix(node_pointer node)	{
				node_pointer uncle;
				while (!node->isRoot() && node->parent->isRed())	{				
					if (node->parent->isRight())	{
						uncle = node->parent->parent->left;
						if (uncle->isRed())	{
							// case 3.1
							uncle->color = BLACK;
							node->parent->color = BLACK;
							node->parent->parent->color = RED;
							node = node->parent->parent;
						}
						else	{
							if (node->isLeft())	{
								//case 3.2.2
								node = node->parent;
								rightRotate(node);
							}
							// case 3.2.1
							node->parent->color = BLACK;
							node->parent->parent->color = RED;
							leftRotate(node->parent->parent);
						}
					}
					else	{
						uncle = node->parent->parent->right;
						if (uncle->isRed())	{
							// mirror case 3.1
							uncle->color = BLACK;
							node->parent->color = BLACK;
							node->parent->parent->color = RED;
							node = node->parent->parent;
						}
						else	{
							if (node->isRight())	{
								// mirror case 3.2.2
								node = node->parent;
								leftRotate(node);
							}
							//mirror case 3.2.1
							node->parent->color = BLACK;
							node->parent->parent->color = RED;
							rightRotate(node->parent->parent);
						}
					}
				}
				this->root->color = BLACK;
			}

			void	fixDelete(node_pointer node)	{
				node_pointer sibling;
				while (node != root && node->isBlack())	{
					if (node->isLeft())	{
						sibling = node->parent->right;
						if (sibling->isRed())	{
							//case 3.1
							sibling->color = BLACK;
							node->parent->color = RED;
							leftRotate(node->parent);
							sibling = node->parent->right;
						}
						if (sibling->left->isBlack() && sibling->right->isBlack())	{ 
							// case 3.2
							sibling->color = RED;
							node = node->parent;
						}
						else	{
							if (sibling->right->isBlack())	{
								// case 3.3
								sibling->left->color = BLACK;
								sibling->color = RED;
								rightRotate(sibling);
								sibling = node->parent->right;
							}
							// case 3.4
							sibling->color = node->parent->color;
							node->parent->color = BLACK;
							sibling->right->color = BLACK;
							leftRotate(node->parent);
							node = root;
						}
					}
					else	{
						sibling = node->parent->left;
						if (sibling->isRed())	{
							//case 3.1
							sibling->color = BLACK;
							node->parent->color = RED;
							rightRotate(node->parent);
							sibling = node->parent->left;
						}
						if (sibling->left->isBlack() && sibling->right->isBlack())	{ 
							// case 3.2
							sibling->color = RED;
							node = node->parent;
						}
						else	{
							if (sibling->left->isBlack())	{
								// case 3.3
								sibling->right->color = BLACK;
								sibling->color = RED;
								leftRotate(sibling);
								sibling = node->parent->left;
							}
							// case 3.4
							sibling->color = node->parent->color;
							node->parent->color = BLACK;
							sibling->left->color = BLACK;
							rightRotate(node->parent);
							node = root;
						}
					}
				}
				node->color = BLACK;
			}

			void rbTransplant(node_pointer node1, node_pointer node2)	{
				if (!node1->parent)
					root = node2;
				else if (node1->isRight())
					node1->parent->right = node2;
				else if (node1->isLeft())
					node1->parent->left = node2;
				node2->parent = node1->parent;
			}

			void destroy(node_pointer node)	{
				if (node != NIL && node != _last)	{
					destroy(node->left);
					destroy(node->right);

					_allocator.destroy(node);
					_allocator.deallocate(node, 1);
				}
			}
			
		public:
			RBTree(const allocator_type &alloc = allocator_type()) : root(nullptr), NIL(nullptr), _first(nullptr), _last(nullptr), _allocator(alloc), _size(0)	{
				NIL = _allocator.allocate(1);
				_allocator.construct(NIL, node_type(value_type(), BLACK));
				// _last = _allocator.allocate(1);
				// _allocator.construct(_last, node_type(value_type(), BLACK));
				root = NIL;
				_last = NIL;
				_first = NIL;
			}

			~RBTree()	{
				clear();
				_allocator.destroy(NIL);
				_allocator.deallocate(NIL, 1);
			}

			node_pointer begin() const	{ return (_first); }

			node_pointer end() const	{ return (_last); }
			
			void	setBounds()	{
				if (root == NIL)	{
					_allocator.destroy(_last);
					_allocator.deallocate(_last, 1);
					_last = NIL;
					_first = NIL;
					return ;
				}
				_first = root;
				while (_first->left != NIL)
					_first = _first->left;
				node_pointer node = root;
				while (node->right != NIL && node->right != _last)
					node = node->right;
				if (_last == NIL)	{
					_last = _allocator.allocate(1);
					_allocator.construct(_last, node_type(value_type(), BLACK));
					_last->left = NIL;
					_last->right = NIL;
				}
				node->right = _last;
				_last->parent = node;
			}
			
			node_pointer	insert(value_type key)	{
				_size++;
				node_pointer newNode = _allocator.allocate(1);
				_allocator.construct(newNode, ft::Node<value_type>(key));
				newNode->left = NIL, newNode->right = NIL;
				this->root = BSTinsertion(this->root, newNode);
				this->root->color = BLACK;
				insertionFix(newNode);
				setBounds();
				// std::cout << "_first        = " << "==" << _first << std::endl;
				// std::cout << "_last         = " << "==" << _last << std::endl;
				// std::cout << "_last parent  = " << "==" << _last->parent << std::endl;
				return (newNode);
			}

			node_pointer search(const value_type &key) const	{
				node_pointer node = this->root;
				while (node != NIL && node != _last) {
					if (!_comp(key, node->key) && !_comp(node->key, key))
						return (node);
					if (_comp(key, node->key))
						node = node->left;
					else
						node = node->right;
				}
				return (_last);
			}

			size_type	remove(value_type key)	{
				node_pointer node = search(key);
				if (node != _last)
				{
					node_pointer x, y;
					int color = node->color;
					if (node->right == NIL)	{
						x = node->left;
						rbTransplant(node, node->left);
					}
					else if (node->left == NIL)	{
						x = node->right;
						rbTransplant(node, node->right);
					}
					else	{
						y = maxNode(node->left);
						color = y->color;
						x = y->left;
						if (y->parent == node)
							x->parent = y;
						else	{
							rbTransplant(y, y->left);
							y->left = node->left;
							y->left->parent = y;
						}
						rbTransplant(node, y);
						y->right = node->right;
						y->right->parent = y;
						y->color = node->color;
					}
					_allocator.destroy(node);
					_allocator.deallocate(node, 1);
					if (color == BLACK)
						fixDelete(x);
					_size--;
					if (!_size)
						this->root = NIL;
					setBounds();
					return (1);
				}
				return (0);
			}

			size_type size()	{ return (_size); }

			bool isEmpty()	{ return (_size == 0); }

			size_type max_size() { return (_allocator->max_size()); }
						
			void	clear()	{
				if (root != NIL)	{
					destroy(this->root);
					this->root = NIL;
					setBounds();
					_size = 0;
				}
			}


		void printHelper(node_pointer root, std::string indent, bool last) {
			// print the tree structure on the screen
			if (root != NIL) {
				std::cout<<indent;
				if (last) {
					std::cout<<"R----";
					indent += "     ";
				} else {
					std::cout<<"L----";
					indent += "|    ";
				}
				
				std::string sColor = root->color?"RED":"BLACK";
				std::cout<<root->key.first<<"("<<sColor<<")"<<std::endl;
				printHelper(root->left, indent, false);
				printHelper(root->right, indent, true);
			}
			// cout<<root->left->data<<endl;
		}

		void Print() 	{
			if (root) 
				printHelper(root, "", true);
		}
	};
}