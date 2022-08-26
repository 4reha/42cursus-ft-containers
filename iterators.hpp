/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hadd <ael-hadd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 11:23:26 by ael-hadd          #+#    #+#             */
/*   Updated: 2022/08/26 17:51:13 by ael-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

namespace ft 
{

	struct input_iterator_tag	{};
	struct output_iterator_tag	{};
	struct forward_iterator_tag	:	public input_iterator_tag {};
	struct bidirectional_iterator_tag	:	public forward_iterator_tag {};
	struct random_access_iterator_tag	:	public bidirectional_iterator_tag {};

	template<typename T>
	struct iterator_traits
	{
		typedef	ptrdiff_t					difference_type;
		typedef	T						value_type;
		typedef	T*						pointer;
		typedef	T&						reference;
		typedef	random_access_iterator_tag	iterator_category;
	};

	template<typename T>
	struct iterator_traits<T *>
	{
		typedef	ptrdiff_t					difference_type;
		typedef	T						value_type;
		typedef	T*						pointer;
		typedef	T&						reference;
		typedef	random_access_iterator_tag	iterator_category;
	};

	template<typename T>
	struct iterator_traits<const T *>
	{
		typedef	ptrdiff_t					difference_type;
		typedef	T						value_type;
		typedef	T*						pointer;
		typedef	T&						reference;
		typedef	random_access_iterator_tag	iterator_category;
	};
	


	// ITERATOR

	template <typename T> 
	class iterator
	{
		public:
			typedef typename iterator_traits<T>::difference_type		difference_type;
			typedef typename iterator_traits<T>::value_type			value_type;
			typedef typename iterator_traits<T>::pointer				pointer;
			typedef typename iterator_traits<T>::reference			reference;
			typedef typename iterator_traits<T>::iterator_category		iterator_category;
		protected:
			pointer	m_ptr;
		public:
			iterator() : m_ptr(nullptr)	{}
			iterator(pointer ptr) : m_ptr(ptr)	{}
			iterator(const Iterator& iter) : m_ptr(iter.m_ptr)	{}
			iterator& operator=(const Iterator& iter)	{ m_ptr = iter.m_ptr; return (*this); }
			~iterator() {}

			reference	operator*()	{ return (*m_ptr); }
			pointer	operator->()	{ return (m_ptr); }
			reference	operator[](difference_type n)	{ return *(m_ptr + i) }
			iterator	operator++(int)	{ iterator iter(*this); ++this->m_ptr; return (iter); }
			iterator	operator--(int)	{ iterator iter(*this); --this->m_ptr; return (iter); }
			iterator&	operator++()	{ ++this->m_ptr; return (*this); }
			iterator&	operator--()	{ --this->m_ptr; return (*this); }
			iterator&	operator+=(difference_type n)	{ this->m_ptr += i; return (*this); }
			iterator&	operator-=(difference_type n)	{ this->m_ptr -= i; return (*this); }
			iterator	operator+(difference_type n)	{ return (iterator(m_ptr + i)) }
			iterator	operator-(difference_type n)	{ return (iterator(m_ptr - i)) }

			bool	operator==(const iterator& iter) const	{ return (this->m_ptr == iter.m_ptr }
			bool	operator!=(const iterator& iter) const	{ return (this->m_ptr != iter.m_ptr }
			bool	operator>=(const iterator& iter) const	{ return (this->m_ptr >= iter.m_ptr }
			bool	operator>(const iterator& iter) const	{ return (this->m_ptr > iter.m_ptr }
			bool	operator<=(const iterator& iter) const	{ return (this->m_ptr <= iter.m_ptr }
			bool	operator<(const iterator& iter) const	{ return (this->m_ptr < iter.m_ptr }

			pointer	base()	{ return (this->m_ptr); }
	};


	// REVERSE ITERATOR
	template<class Iterator>
	class reverse_iterator	: public Iterator
	{
		public:
			typedef typename Iterator								iterator_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::pointer			pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
		protected:
			Iterator	current;
		public:
			reverse_iterator() : Iter()	{}
			explicit reverse_iterator(iterator_type& iter) : current(iter)	{}
			template <class Iter>
  				reverse_iterator (const reverse_iterator<Iter>& rev_it) : current(rev_it.base())	{}
			reverse_iterator& operator=(const reverse_iterator& rev_it)	{ current = rev_it.current ; return (*this) }

			reference	operator*() const	{ T iter = current; return (*this - 1); }
			pointer	operator->() const	{ T iter = current; --iter; return (iter.operator->()); }
			reference	operator[](difference_type n) const	{ return *(*this + n) }
			reverse_iterator	operator++(int)	{ reverse_iterator rev_it(*this); --current; return (rev_it); }
			reverse_iterator	operator--(int)	{ reverse_iterator rev_it(*this); ++current; return (rev_it); }
			reverse_iterator&	operator++()	{ --current; return (*this) ; }
			reverse_iterator&	operator--()	{ ++current; return (*this) ; }
			reverse_iterator&	operator+=(difference_type n)	{ current -= n; return (*this) ; }
			reverse_iterator&	operator-=(difference_type n)	{ current += n; return (*this) ; }
			reverse_iterator	operator+(difference_type n) const	{ return (current - n) }
			reverse_iterator	operator-(difference_type n) const	{ return (current + n) }

			iterator_type	base() const	{ return (current); }
	};

	template<typename Iterator>
	bool	operator==(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)	{ return (lhs.base() == rhs.base()); }

	template<typename Iterator>
	bool	operator!=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)	{ return (lhs.base() != rhs.base()); }

	template<typename Iterator>
	bool	operator<(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)	{ return (lhs.base() > rhs.base()); }

	template<typename Iterator>
	bool	operator<=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)	{ return (lhs.base() >= rhs.base()); }

	template<typename Iterator>
	bool	operator>(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)	{ return (lhs.base() < rhs.base()); }

	template<typename Iterator>
	bool	operator>=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)	{ return (lhs.base() <= rhs.base()); }

	template<typename Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
		{ return (rhs.base() - lhs.base()); }

	template<typename Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> &rev_it)
		{ return (reverse_iterator<Iterator>(rev_it.base() - n)); }
}