/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hadd <ael-hadd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 09:31:53 by ael-hadd          #+#    #+#             */
/*   Updated: 2022/09/02 19:19:58 by ael-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include	<iostream>
#include "iterators.hpp"
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

	template<class T, class Compare = ft::less<T>, class Alloc = std::allocator<ft::Node<T> > >
	class RBTree
	{
		public:
			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef ft::Node<value_type>							node_type;
			typedef typename ft::Node<value_type>::node_pointer		node_pointer;
			typedef ft::RBIterator<node_pointer,value_type>			iterator;
			typedef ft::RBIterator<node_pointer,const value_type>		const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;
			typedef size_t										size_type;
		public:
			node_pointer		root;
			node_pointer		DB;
			allocator_type		_allocator;
			Compare			_comp;
			size_type			_size;
		protected:
				void	leftRotate(node_pointer ptr)	{
				// std::cout << "leftRotate" << std::endl;
				node_pointer	r_node = ptr->right;
				ptr->right = r_node->left;
				if (r_node->left)
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
				if (l_node->right)
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
			void	reColor()
				{ this->color = BLACK ? this->color == RED : this->color = RED; }
			node_pointer	minNode(node_pointer root)
			{
				node_pointer node = root;
				while (node->left)
					node = node->left;
				return (node);
			}
			
			node_pointer	maxNode(node_pointer root)
			{
				node_pointer node = root;
				while (node->right)
					node = node->right;
				return (node);
			}
			
		public:
			RBTree() { this->root = nullptr; _size = 0;}
			void	insert(value_type key)
			{
				_size++;
				node_pointer newNode = _allocator.allocate(1);
				_allocator.construct(newNode, ft::Node<value_type>(key));
				this->root = BSTinsertion(this->root, newNode);
				this->root->color = BLACK;
				insertionFix(newNode);
			}
			void	insertionFix(node_pointer node)	{
				node_pointer uncle;
				while (!node->isRoot() && node->parent->isRed())	{					
					if (node->parent->isRight())	{
						uncle = node->parent->parent->left;
						if (uncle && uncle->isRed())	{
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
					// std::cout << "Here" << std::endl;
						uncle = node->parent->parent->right;
						if (uncle && uncle->isRed())	{
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
			
			node_pointer BSTinsertion(node_pointer ptr, node_pointer node)
			{
				if (!ptr)	{
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
			
			node_pointer searchNode(node_pointer root, value_type key)
			{
				node_pointer node = root;
				while (node)
				{
					if (node->key == key)
						break ;
					if (_comp(key, node->key))
						node = node->left;
					else
						node = node->right;
				}
				return (node);
			}
			void rbTransplant(node_pointer n1, node_pointer n2)
			{
				n1->key = n2->key;
				if (n2->left)
				{
					n2->parent = n2->left;	
					n2->left->parent = n2->parent;
				}
			}
			void	remove(value_type key)
			{
				node_pointer node = searchNode(this->root, key);
				if (node)
				{
					if (node->right)
					{
						if (node->isRoot())
						{
							this->root = node->right;
							node->right->parent = nullptr;	
						}
						else if (node->isLeft())
						{
							node->parent->left = node->right;
							node->right->parent = node->parent;	
						}
						else if (node->isRight())
						{
							node->parent->right = node->right;
							node->right->parent = node->parent;	
						}
					}
					if (node->left)
					{
						node_pointer to_replace = maxNode(node->left);
						rbTransplant(node, to_replace);
						int c = to_replace->color;
						delete to_replace;
					}
					else
					{
						int c = node->color;
						delete node;
					}
				}
				
				
			}


			// Iretators:
			iterator begin()	{
				return (iterator(minNode(this->root))); }
			const_iterator begin() const	{
				return (iterator(minNode(this->root))); }
			iterator end()	{
				return (iterator(maxNode(this->root))); }
			const_iterator end() const	{
				return (iterator(maxNode(this->root))); }
			reverse_iterator rbegin()	{
				return (reverse_iterator(maxNode(this->root))); }
			const_reverse_iterator rbegin() const	{
				return (reverse_iterator(maxNode(this->root))); }
			reverse_iterator rend()	{
				return (reverse_iterator(minNode(this->root))); }
			const_reverse_iterator rend() const	{
				return (reverse_iterator(minNode(this->root))); }
	};
}