/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hadd <ael-hadd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 10:15:00 by ael-hadd          #+#    #+#             */
/*   Updated: 2022/08/27 10:17:20 by ael-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <algorithm>

namespace ft
{
	template <typename T>
	void	swap(T& x, T& y)
	{
		T tmp(x);
		x = y;
		y = tmp;
	}
	
}