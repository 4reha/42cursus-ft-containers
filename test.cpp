/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hadd <ael-hadd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 10:25:07 by ael-hadd          #+#    #+#             */
/*   Updated: 2022/08/16 17:51:41 by ael-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iterator>
#include <vector>
#include <iostream>
#include <list>

int main(void) 
{
typedef std::iterator_traits<std::vector<int>:: iterator> traits;
	if (typeid(traits::iterator_category)==typeid(std::random_access_iterator_tag))
		std::cout << "int* is a random-access iterator";
	return 0;
}