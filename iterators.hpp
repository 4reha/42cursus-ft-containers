/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hadd <ael-hadd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 11:23:26 by ael-hadd          #+#    #+#             */
/*   Updated: 2022/09/11 14:44:38 by ael-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "red_black.hpp"
#include "type_traits.hpp"
#include "functional.hpp"
#include "algorithm.hpp"

namespace ft 
{

	struct input_iterator_tag	{};
	struct output_iterator_tag	{};
	struct forward_iterator_tag	:	public input_iterator_tag {};
	struct bidirectional_iterator_tag	:	public forward_iterator_tag {};
	struct random_access_iterator_tag	:	public bidirectional_iterator_tag {};



	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator {
		typedef T         value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
		typedef Category  iterator_category;
	};
	template<typename Iter>
	struct iterator_traits
	{
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::iterator_category		iterator_category;
	};

	template<typename T>
	struct iterator_traits<T*>
	{
		typedef T									value_type;
		typedef std::ptrdiff_t						difference_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef random_access_iterator_tag				iterator_category;
	};

	template<typename T>
	struct iterator_traits<const T*>
	{
		typedef T									value_type;
		typedef std::ptrdiff_t						difference_type;
		typedef const T*							pointer;
		typedef const T&							reference;
		typedef random_access_iterator_tag				iterator_category;
	};
	
	// ITERATORS:
	template <typename T, typename U/*, typename node_pointer*/>
	class RBiterator
	{
		public:
			typedef typename iterator_traits<T*>::difference_type		difference_type;
			typedef typename iterator_traits<T*>::value_type			value_type;
			typedef typename iterator_traits<T*>::pointer				pointer;
			typedef typename iterator_traits<T*>::reference			reference;
			typedef typename iterator_traits<T*>::iterator_category		iterator_category;
			typedef typename ft::Node<T>::node_pointer				node_pointer;
			typedef typename ft::Node<U>::node_pointer				node_pointer2;
			
		protected:
			node_pointer	m_ptr;
		public:
			RBiterator() : m_ptr(nullptr) {}
			RBiterator(node_pointer ptr) : m_ptr(reinterpret_cast<node_pointer>(ptr))	{}
			RBiterator(node_pointer2 ptr) : m_ptr(reinterpret_cast<node_pointer>(ptr))	{}
			RBiterator& operator=(const node_pointer& ptr)	{ m_ptr = ptr; return (*this); }
			~RBiterator() {}
			
			reference	operator*() const	{ return (m_ptr->key); }
			pointer	operator->() const	{ return (&m_ptr->key); }

			RBiterator&	operator++()	{
				if (m_ptr->right && m_ptr->right->right)
				{
					m_ptr = m_ptr->right;
					while (m_ptr->left && m_ptr->left->left)
					{
						m_ptr = m_ptr->left;
					}
				}
				else {
					while(!m_ptr->isLeft() && !m_ptr->isRoot())
						m_ptr = m_ptr->parent;
					if (!m_ptr->isRoot())
						m_ptr = m_ptr->parent;
				}
				return (*this);
			}
			RBiterator	operator++(int)	{
				RBiterator it(*this);
				++(*this);
				return (it);
			}
			RBiterator&	operator--()	{
				if (m_ptr->left && m_ptr->left->left)
				{
					m_ptr = m_ptr->left;
					while (m_ptr->right && m_ptr->right->right)
						m_ptr = m_ptr->right;
				}
				else {
					while(m_ptr->isLeft())
						m_ptr = m_ptr->parent;
					if (!m_ptr->isRoot())
						m_ptr = m_ptr->parent;
				}
				return (*this);
			}
			RBiterator	operator--(int)	{
				RBiterator it(*this);
				--(*this);
				return (it);
			}

			node_pointer	base()	{ return (m_ptr); }
			node_pointer	base() const	{ return (m_ptr); }
			
			bool	operator==(const RBiterator& iter) const	{ return (this->m_ptr == iter.m_ptr); }
			bool	operator!=(const RBiterator& iter) const	{ return (this->m_ptr != iter.m_ptr); }
	};
	
	
	template<typename T>
	class vec_iterator
	{
	public:
		typedef T*												iterator_type;
		typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;
		typedef typename iterator_traits<iterator_type>::value_type			value_type;
		typedef typename iterator_traits<iterator_type>::difference_type		difference_type;
		typedef typename iterator_traits<iterator_type>::pointer			pointer;
		typedef typename iterator_traits<iterator_type>::reference			reference;

	private:
		iterator_type i_ptr;

	public:

		vec_iterator() : i_ptr() {}

		vec_iterator(const vec_iterator& other) : i_ptr(other.base()) {}

		vec_iterator(const iterator_type& ptr) : i_ptr(ptr) {}

		~vec_iterator() {}


		// operator vec_iterator<const T>() const;
		reference			operator*() const	{
			return (*this->i_ptr);
		}

		pointer			operator->() const	{
			return (this->i_ptr);
		}

		vec_iterator&		operator++()	{
			++this->i_ptr;
			return (*this);
		}

		vec_iterator		operator++(int)	{
			vec_iterator iter(*this);
			++this->i_ptr;
			return (iter);
		}

		vec_iterator&		operator--()	{
			--this->i_ptr;
			return (*this);
		}

		vec_iterator		operator--(int)	{
			vec_iterator iter(*this);
			--this->i_ptr;
			return (iter);
		}

		vec_iterator		operator+(difference_type n) const	{
			return (vec_iterator(i_ptr + n));
		}

		vec_iterator&		operator+=(difference_type n)	{
			i_ptr += n;
			return (*this);
		}

		vec_iterator		operator-(difference_type n) const	{
			return (vec_iterator(i_ptr - n));
		}

		difference_type	operator-(vec_iterator const& other) const	{
			return (this->base() - other.base());
		}

		vec_iterator&		operator-=(difference_type n)	{
			i_ptr -= n;
			return (*this);
		}

		reference			operator[](difference_type n) const	{
			return *(this->i_ptr - n);
		}
		
		iterator_type base() const	{
			return (this->i_ptr);
		}
		bool	operator==(const vec_iterator& iter) const	{ return (this->base() == iter.base()); }
		bool	operator!=(const vec_iterator& iter) const	{ return (this->base() != iter.base()); }
		bool	operator>=(const vec_iterator& iter) const	{ return (this->base() >= iter.base()); }
		bool	operator> (const vec_iterator& iter) const	{ return (this->base() >  iter.base()); }
		bool	operator<=(const vec_iterator& iter) const	{ return (this->base() <= iter.base()); }
		bool	operator< (const vec_iterator& iter) const	{ return (this->base() <  iter.base()); }

	};

	// REVERSE iTERATOR
	template<class Iter>
	class reverse_iterator	: public iterator<typename iterator_traits<Iter>::iterator_category,
		typename iterator_traits<Iter>::value_type, typename iterator_traits<Iter>::difference_type,
		typename iterator_traits<Iter>::pointer, typename iterator_traits<Iter>::reference>
	{
		public:
			typedef Iter												iterator_type;	
			typedef typename iterator_traits<iterator_type>::difference_type		difference_type;
			typedef typename iterator_traits<iterator_type>::value_type			value_type;
			typedef typename iterator_traits<iterator_type>::pointer			pointer;
			typedef typename iterator_traits<iterator_type>::reference			reference;
			typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;
		protected:
			iterator_type	current;
		public:
			reverse_iterator() : current()	{}

			reverse_iterator(iterator_type& iter) : current(iter)	{}

			template <class U>
  				reverse_iterator (const reverse_iterator<U>& rev_it) : current(rev_it.base())	{}

			reverse_iterator& operator=(const reverse_iterator& rev_it)	{ current = rev_it.current ; return (*this); }

			reference	operator*() const	{ iterator_type iter = current; return (*--iter); }
			reference	operator*() 		{ iterator_type iter = current; return (*--iter); }

			pointer	operator->() const	{ iterator_type iter = current; --iter; return (iter.operator->()); }
			pointer	operator->() 		{ iterator_type iter = current; --iter; return (iter.operator->()); }

			reference	operator[](difference_type n) const	{ return *(*this + n); }

			reverse_iterator	operator++(int)	{ reverse_iterator rev_it(*this); --current; return (rev_it); }

			reverse_iterator	operator--(int)	{ reverse_iterator rev_it(*this); ++current; return (rev_it); }

			reverse_iterator&	operator++()	{ --current; return (*this) ; }

			reverse_iterator&	operator--()	{ ++current; return (*this) ; }

			reverse_iterator&	operator+=(difference_type n)	{ current -= n; return (*this) ; }

			reverse_iterator&	operator-=(difference_type n)	{ current += n; return (*this) ; }

			reverse_iterator	operator+(difference_type n) const	{ return ( current - n); }

			reverse_iterator	operator-(difference_type n) const	{ return ( current + n); }


			iterator_type	base() 		{ return (current); }
			iterator_type	base() const	{ return (current); }
	};

	template<typename iterator>
	bool	operator==(const reverse_iterator<iterator> &lhs, const reverse_iterator<iterator> &rhs)	{ return (lhs.base() == rhs.base()); }

	template<typename iterator>
	bool	operator!=(const reverse_iterator<iterator> &lhs, const reverse_iterator<iterator> &rhs)	{ return (lhs.base() != rhs.base()); }

	template<typename iterator>
	bool	operator<(const reverse_iterator<iterator> &lhs, const reverse_iterator<iterator> &rhs)	{ return (lhs.base() > rhs.base()); }

	template<typename iterator>
	bool	operator<=(const reverse_iterator<iterator> &lhs, const reverse_iterator<iterator> &rhs)	{ return (lhs.base() >= rhs.base()); }

	template<typename iterator>
	bool	operator>(const reverse_iterator<iterator> &lhs, const reverse_iterator<iterator> &rhs)	{ return (lhs.base() < rhs.base()); }

	template<typename iterator>
	bool	operator>=(const reverse_iterator<iterator> &lhs, const reverse_iterator<iterator> &rhs)	{ return (lhs.base() <= rhs.base()); }

	template<typename iterator>
	typename reverse_iterator<iterator>::difference_type operator-(const reverse_iterator<iterator> &lhs, const reverse_iterator<iterator> &rhs)
		{ return -(rhs.base() - lhs.base()); }

	template<typename iterator>
	reverse_iterator<iterator> operator+(typename reverse_iterator<iterator>::difference_type n, const reverse_iterator<iterator> &rev_it)
		{ return (reverse_iterator<iterator>(rev_it.base() - n)); }

}