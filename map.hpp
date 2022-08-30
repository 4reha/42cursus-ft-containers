/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hadd <ael-hadd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 09:26:47 by ael-hadd          #+#    #+#             */
/*   Updated: 2022/08/29 14:07:40 by ael-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

#include <iostream>

namespace	ft
{
	template<typename Key, typename T, typename Compare = std::less<Key>,
				typename Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public:
			typedef Key									key_type;
			typedef T										mapped_type;
			typedef ft::pair<const Key, T>					value_type;
			typedef Compare								key_compare;
			typedef Alloc									allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef typename std::size_t						size_type;
			typedef typename allocator_type::difference_type		difference_type;
	};
}