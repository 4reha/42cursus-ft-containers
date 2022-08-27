/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hadd <ael-hadd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 09:26:59 by ael-hadd          #+#    #+#             */
/*   Updated: 2022/08/27 13:00:41 by ael-hadd         ###   ########.fr       */
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
			typedef	typename container_type::reference			reference
			typedef	typename container_type::const_reference	const_reference;
		protected:
			container_type s_container;
		public:
			explicit stack (const container_type& ctnr = container_type());
	};
	
}