/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hadd <ael-hadd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 09:26:53 by ael-hadd          #+#    #+#             */
/*   Updated: 2022/08/17 11:17:17 by ael-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

namespace	ft
{
	template <typename vector>
	class vectorIter
	{
		public:
			typedef vector::value_type	value_type;
			typedef vector::value_type*	pointer_type;
			typedef vector::value_type&	reference_type;
		protected:
			pointer_type	m_ptr;
		public:
			vectorIter(){}; // Default constructer
			vectorIter(pointer_type	ptr) : m_ptr(ptr){};
			vectorIter(vectorIter const& Iter) // copy constructer
			{
				*this = Iter;
			};
			vectorIter& operator=(const vectorIter& Iter) // copy assignment
			{
				m_ptr = Iter.m_ptr;
				return (*this);
			};
			~vectorIter(){};
			bool	operator==(const vectorIter& Iter) const // equality operator
			{
				return(m_ptr==Iter.m_ptr);
			};
			bool	operator!=(const vectorIter& Iter) const // inquality operator
			{
				return(m_ptr!=Iter.m_ptr);
			};
			reference_type operator*()
			{
				return (*m_ptr);
			};
			pointer_type operator->()
			{
				return(m_ptr);
			};
			vectorIter& operator++() //pre-increment operator
			{
				m_ptr++;
				return (*this);
			};
			vectorIter operator++(int) // post-increment operator
			{
				vectorIter Iter = *this;
				++m_ptr ;
				return (Iter);
			};
			vectorIter& operator--() // pre-decrement operator
			{
				m_ptr--;
				return (*this);
			};
			vectorIter operator--(int) //post-decrement operator
			{
				vectorIter Iter = *this;
				--m_ptr ;
				return (Iter);
			};
			reference_type	operator[](int index) // index operator
			{
				return(*m_ptr[index]);
			};
			bool	operator<(const vectorIter& Iter) const // smaller-than operator
			{
				return(m_ptr<Iter.m_ptr);
			};
			bool	operator>(const vectorIter& Iter) const // greater-than operator
			{
				return(m_ptr>Iter.m_ptr);
			};
			bool	operator<=(const vectorIter& Iter) const //  smaller-than or equal  operator
			{
				return(m_ptr<=Iter.m_ptr);
			};
			bool	operator>=(const vectorIter& Iter) const // greater-than or equal  operator
			{
				return(m_ptr>=Iter.m_ptr);
			};
	};
		
	template <typename T, typename Alloc = std::allocator<T>>
	class vector
	{
		public:
			typedef T						value_type;
			typedef Alloc					allocator_type;
			typedef T&					reference;
			typedef const T&				const_reference;
			typedef T*					pointer;
			typedef const T*				const_pointer;
			typedef ft::vectorIter<vector<T>>	iterator;
			typedef size_t					size_type;
		private:
			size_type	_size;
			size_type	_capacity;
			pointer	_data;
			allocator_type	_alloc;
	};	
}
