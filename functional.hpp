/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functional.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hadd <ael-hadd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 10:11:11 by ael-hadd          #+#    #+#             */
/*   Updated: 2022/09/02 10:12:36 by ael-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

namespace ft
{
	template<typename Arg1, typename Arg2, typename Result>
	struct binary_function
	{
		typedef Arg1	frist_argument_type;
		typedef Arg2	second_argument_type;
		typedef Result	result_type;
	};

	template<typename T>
	struct less: binary_function<T,T,bool>
	{
		bool operator()(const T& x, const T& y) const
		{
			return x < y;
		}
	};
}