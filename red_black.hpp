/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hadd <ael-hadd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 09:31:53 by ael-hadd          #+#    #+#             */
/*   Updated: 2022/09/04 14:26:59 by ael-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include	<iostream>
#include "functional.hpp"

namespace	ft
{

	enum node_color {BLACK, RED, DOUBLE_BLACK};
	
	
	template<typename T>
	struct Node
	{
		typedef T		value_type;
		typedef Node<T>*	node_pointer;

		value_type		key;
		node_color		color;
		node_pointer		parent;
		node_pointer		right;
		node_pointer		left;
		

		Node(value_type& data, node_color color = RED) 
			: key(data), color(color), parent(nullptr), right(nullptr), left(nullptr) {}
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
		public:
			node_pointer		root;
			node_pointer		NIL;
			allocator_type		_allocator;
			Compare			_comp;
			size_type			_size;
		public:
			void	leftRotate(node_pointer ptr)	{
				// std::cout << "leftRotate" << std::endl;
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
				// std::cout<< "rightRotate" << std::endl;
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

			node_pointer	begin()	{
				node_pointer node = this->root;
				while (node->left != NIL)
					node = node->left;
				return (node);
			}

			node_pointer	end()	{
				node_pointer node = this->root;
				while (node->right != NIL)
					node = node->right;
				return (node);
			}
			
			node_pointer BSTinsertion(node_pointer ptr, node_pointer node)	{
				if (ptr == NIL)
					ptr = node;
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
			
		public:
			RBTree()	{
				_size = 0;
				NIL = _allocator.allocate(1);
				NIL->color = BLACK;
				NIL->left = nullptr;
				NIL->right = nullptr;
				root = NIL;
			}

			node_pointer	insert(value_type key)	{
				_size++;
				node_pointer newNode = _allocator.allocate(1);
				_allocator.construct(newNode, ft::Node<value_type>(key));
				newNode->left = NIL, newNode->right = NIL;
				this->root = BSTinsertion(this->root, newNode);
				this->root->color = BLACK;
				insertionFix(newNode);
				return (newNode);
			}

			node_pointer searchNode(value_type key)
			{
				node_pointer node = this->root;
				while (node != NIL) {
					if (!_comp(key, node->key) && !_comp(node->key, key))
						break ;
					if (_comp(key, node->key))
						node = node->left;
					else
						node = node->right;
				}
				return (node);
			}

			void	remove(value_type key)
			{
				node_pointer node = searchNode(key);
				if (node != NIL)
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
						y->right->parent =y;
						y->color = node->color;
					}
					delete node;
					if (color == BLACK)
						fixDelete(x);
				}
			}


			size_type size()	{ return (_size); }
			bool isEmpty()	{ return (_size == 0); }
			size_type max_size() { return (_allocator->max_size()); }
			
			void destroy(node_pointer node)	{
				if (!node)
					return;
				destroy(node->left);
				destroy(node->right);

				_allocator.destroy(node);
				_allocator.deallocate(node, 1);
			}
			
			void	clear()	{
				destroy(this->root);
				this->root = nullptr;
				this->NIL = nullptr;
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

		void Print() 
		{
			if (root) 
				printHelper(root, "", true);
		}
	};
}