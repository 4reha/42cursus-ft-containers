/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hadd <ael-hadd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 09:31:53 by ael-hadd          #+#    #+#             */
/*   Updated: 2022/08/31 14:25:30 by ael-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include	<iostream>
#include "iterators.hpp"

namespace	ft
{

	enum node_color {BLACK, RED};

	
	template<typename T>
	struct Node
	{
		typedef T		value_type;
		typedef Node<T>*	node_pointer;

		value_type		key;
		node_pointer		parent;
		node_pointer		right;
		node_pointer		left;
		node_color		color;
		
		bool	isRoot()	{ return (!parent); }
		bool isLeft()	{ return (parent && parent->left == this); }
		bool	isRight()	{ return (parent && parent->right == this); }
		bool isBlack()	{ return (color == BLACK); }
		bool isRed()	{ return (color == RED); }
		
	};

	template<typename T>
	class RBTree
	{
		public:
			typedef typename	ft::Node<T>::value_type					value_type;
			typedef typename	ft::Node<value_type>					node_type;
			typedef typename	ft::Node<value_type>::node_pointer			node_pointer;
			typedef typename	ft::RBIterator<node_pointer,value_type>		iterator;
		public:
			node_pointer	root;
			size_t		_size;
		public:
			RBTree() { this->root = nullptr; _size = 0;}
			void	insert(value_type key)
			{
				node_pointer newNode = new node_type;
				newNode->key = key;
				newNode->parent = nullptr;
				newNode->right = nullptr;
				newNode->left = nullptr;
				newNode->color = RED;
				node_pointer p = nullptr;
				node_pointer x = this->root;
				this->_size++;
				while (x)
				{
					p = x;
					if (newNode->key < x->key)
						x = x->left;
					else
						x = x->right;
				}
				newNode->parent = p;
				if (!p)
				{
					this->root = newNode;
					this->root->color = BLACK;
					return ;
				}
				else if (newNode->key < p->key)
					p->left = newNode;
				else
					p->right = newNode;
				insertionFix(newNode);
			}
			void	insertionFix(node_pointer node)	{
				node_pointer uncle;
				while (node->parent->color == RED)	{
					std::cout << node->parent->key << std::endl;
					std::cout << node->key << std::endl;
					
					if (node->parent->isRight())	{
						uncle = node->parent->parent->left;
						if (uncle && uncle->color == RED)	{
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
						if (uncle && uncle->color == RED)	{
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
					if (node == this->root)	{
						std::cout << "root" << std::endl;
						node->color = BLACK;
						break ;
					}
				}
			}
			
			void	remove(value_type key)
			{
				node_pointer node = this->root;
				node_pointer tmp = nullptr;
				node_pointer p, q;
				while (node)
				{
					if (node->key == key)	{
						tmp = node;
						break ;
					}
					if (node->key < key)
						node = node->right;
					if (node->key > key)
						node = node->left;
				}
				if (!tmp)
					return;
				q = tmp;
				
				
			}

			iterator	begin()	
			{
				node_pointer t = this->root;
				while (t->left)
					t = t->left;
				return (iterator(t));
			}
			iterator	end()	
			{
				node_pointer t = this->root;
				while (t->right)
					t = t->right;
				return (iterator(t));
			}


			void	leftRotate(node_pointer ptr)	{
				std::cout << "leftRotate" << std::endl;
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
				std::cout<< "rightRotate" << std::endl;
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
			
		
	};
}