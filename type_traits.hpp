/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hadd <ael-hadd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 11:35:41 by ael-hadd          #+#    #+#             */
/*   Updated: 2022/08/29 11:47:27 by ael-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

namespace ft
{
	
	template<bool B, class T = void>
	struct enable_if {};
	
	template<class T>
	struct enable_if<true, T> { typedef T type; };



	template <class T, T v>
	struct integral_constant
	{
		typedef T 					value_type;
		typedef integral_constant<T,v> 	type;

		static const value_type value = v;

		operator value_type() const		{ return (value); }
	};

	typedef integral_constant<bool,true> true_type;
	typedef integral_constant<bool,false> false_type;

	template<typename T>
	struct is_integral: public false_type {};

	template<>
	struct is_integral<bool>: public true_type {};

	template<>
	struct is_integral<char>: public true_type {};

	template<>
	struct is_integral<char16_t>: public true_type {};

	template<>
	struct is_integral<char32_t>: public true_type {};

	template<>
	struct is_integral<wchar_t>: public true_type {};

	template<>
	struct is_integral<signed char>: public true_type {};

	template<>
	struct is_integral<short int>: public true_type {};

	template<>
	struct is_integral<int>: public true_type {};

	template<>
	struct is_integral<long int>: public true_type {};

	template<>
	struct is_integral<long long int>: public true_type {};

	template<>
	struct is_integral<unsigned char>: public true_type {};

	template<>
	struct is_integral<unsigned short int>: public true_type {};

	template<>
	struct is_integral<unsigned int>: public true_type {};

	template<>
	struct is_integral<unsigned long int>: public true_type {};

	template<>
	struct is_integral<unsigned long long int>: public true_type {};
	
}