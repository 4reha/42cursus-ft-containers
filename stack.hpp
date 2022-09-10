/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hadd <ael-hadd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 09:26:59 by ael-hadd          #+#    #+#             */
/*   Updated: 2022/09/09 12:23:27 by ael-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public:
			typedef	Container								container_type;
			typedef	typename container_type::value_type		value_type;
			typedef	typename container_type::size_type			size_type;
			typedef	typename container_type::reference			reference;
			typedef	typename container_type::const_reference	const_reference;
		protected:
			container_type c;
		public:
			explicit	stack (const container_type& ctnr = container_type()) : c(ctnr)	{}
			stack&	operator=( const stack& other)	{ c = other.c; return (*this); }

			// Element access:
			reference			top()	{ return (c.back()); }
			const_reference	top() const	{ return (c.back()); }

			// Capacity:
			bool		empty() const	{ 	{ return (c.empty()); }}
			size_type	size() const	{ return (c.size()); }

			// Modifiers:
			void	push( const value_type& value)	{ c.push_back(value); }
			void	pop()	{ c.pop_back(); }
			
		public:
		template< class U, class Cntr >
			friend bool operator==(const stack<U,Cntr>& lhs, const stack<U,Cntr>& rhs);
		template< class U, class Cntr >
			friend bool operator<(const stack<U,Cntr>& lhs, const stack<U,Cntr>& rhs);
			
		
	};
	template< class T, class Container >
	bool operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return (lhs.c == rhs.c);
	}
	template< class T, class Container >
	bool operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return !(lhs.c == rhs.c);
	}
	template< class T, class Container >
	bool operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return (lhs.c < rhs.c);
	}
	template< class T, class Container >
	bool operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return !(rhs.c < lhs.c);
	}
	template< class T, class Container >
	bool operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return (rhs.c < lhs.c);
	}
	template< class T, class Container >
	bool operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return !(lhs.c < rhs.c);
	}
	
}