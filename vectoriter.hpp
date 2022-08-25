/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_reveres_iter.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hadd <ael-hadd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 09:26:53 by ael-hadd          #+#    #+#             */
/*   Updated: 2022/08/18 09:51:51 by ael-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

namespace ft 
{

	template <typename vector>
	class vector_Iter
	{
		public:
			typedef vector::value_type	value_type;
			typedef vector::value_type*	pointer_type;
			typedef vector::value_type&	reference_type;
		protected:
			pointer_type	m_ptr;
		public:
			vector_Iter(){}; // Default constructer
			// vector_Iter(pointer_type	ptr) : m_ptr(ptr){};
			vector_Iter(vector_Iter const& Iter) // copy constructer
			{
				*this = Iter;
			};
			vector_Iter& operator=(const vector_Iter& Iter) // copy assignment
			{
				m_ptr = Iter.m_ptr;
				return (*this);
			};
			~vector_Iter(){};
			bool	operator==(const vector_Iter& Iter) const // equality operator
			{
				return(m_ptr==Iter.m_ptr);
			};
			bool	operator!=(const vector_Iter& Iter) const // inquality operator
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
			vector_Iter& operator++() //pre-increment operator
			{
				m_ptr++;
				return (*this);
			};
			vector_Iter operator++(int) // post-increment operator
			{
				vector_Iter Iter = *this;
				++m_ptr ;
				return (Iter);
			};
			vector_Iter& operator--() // pre-decrement operator
			{
				m_ptr--;
				return (*this);
			};
			vector_Iter operator--(int) //post-decrement operator
			{
				vector_Iter Iter = *this;
				--m_ptr ;
				return (Iter);
			};
			reference_type	operator[](int index) // index operator
			{
				return(*m_ptr[index]);
			};
			bool	operator<(const vector_Iter& Iter) const // smaller-than operator
			{
				return(m_ptr<Iter.m_ptr);
			};
			bool	operator>(const vector_Iter& Iter) const // greater-than operator
			{
				return(m_ptr>Iter.m_ptr);
			};
			bool	operator<=(const vector_Iter& Iter) const //  smaller-than or equal  operator
			{
				return(m_ptr<=Iter.m_ptr);
			};
			bool	operator>=(const vector_Iter& Iter) const // greater-than or equal  operator
			{
				return(m_ptr>=Iter.m_ptr);
			};
			vector_Iter operator+(int n) const
			{
				vector_Iter Iter(*this);
				Iter+= n;
				return (Iter);
			};
			vector_Iter operator-(int n) const
			{
				vector_Iter Iter(*this);
				Iter-= n;
				return (Iter);
			};
			int	operator+(const vector_Iter& Iter)
			{
				int n = this->m_ptr + Iter.m_ptr;
				return (n);
			}
			int	operator-(const vector_Iter& Iter)
			{
				int n = this->m_ptr - Iter.m_ptr;
				return (n);
			}
			vector_Iter& operator+=(int n)
			{
				m_ptr+= n;
				return (*this);
			};
			vector_Iter& operator-=(int n)
			{
				m_ptr-= n;
				return (*this);
			}
	};

	template <typename vector>
	class vector_const_Iter	: public vector_Iter
	{
		public:
			typedef vector::value_type	value_type;
			typedef vector::value_type*	pointer_type;
			typedef vector::value_type&	reference_type;
			vector_const_Iter(){}; // Default constructer
			// vector_const_Iter(pointer_type	ptr) : m_ptr(ptr){};
			vector_const_Iter(vector_const_Iter const& Iter) // copy constructer
			{
				*this = Iter;
			};
			vector_const_Iter& operator=(const vector_const_Iter& Iter) // copy assignment
			{
				m_ptr = Iter.m_ptr;
				return (*this);
			};
			~vector_const_Iter(){};
			const reference_type operator*()
			{
				return (*m_ptr);
			};
			const reference_type	operator[](int index) // index operator
			{
				return(*m_ptr[index]);
			};

	};

	template	<typename vector>
	class vector_rev_Iter     : public vector_Iter
	{
		public:
			
	};
}