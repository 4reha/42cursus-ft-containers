/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hadd <ael-hadd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 09:26:47 by ael-hadd          #+#    #+#             */
/*   Updated: 2022/09/03 19:39:37 by ael-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

#include <iostream>
#include "iterators.hpp"

namespace	ft
{
	template< class Key, class T, class Compare = std::less<Key>,
		class Allocator = std::allocator<std::pair<const Key, T> >
	> class map
	{
		public:
			typedef Key										key_type;
			typedef T											mapped_type;
			typedef ft::pair<const Key, T>						value_type;
			typedef Compare									key_compare;
			typedef Allocator									allocator_type;
			typedef value_type&									reference;
			typedef const value_type&							const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef typename std::size_t							size_type;
			typedef typename std::ptrdiff_t						difference_type;
			class value_compare : public ft::binary_function<value_type, value_type, bool>
			{
				protected:
					key_compare comp;
				public:
					value_compare() : comp(key_compare()) {}

					value_compare(key_compare c) : comp(c) {}

					bool operator()(const value_type &lhs, const value_type &rhs) const
					{	
						return comp(lhs.first, rhs.first);
					};
			};
			typedef typename ft::Node<value_type>* 					node_pointer;
			typedef ft::RBiterator<value_type>						iterator;
			typedef ft::RBiterator<const value_type>				const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;
			

	};
}