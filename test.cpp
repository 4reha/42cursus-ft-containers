/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hadd <ael-hadd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 10:25:07 by ael-hadd          #+#    #+#             */
/*   Updated: 2022/08/26 15:27:46 by ael-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iterator>
#include <vector>
#include <iostream>
#include <list>
#include <algorithm>

int main(void) 
{

	int n = 4;
	int i;
	std::vector<int> v;
	for (i = 0; i <= 10; i++)
		v.push_back(i);
	i = 0;
	std::vector<int>::iterator it = v.begin();
	std::reverse_iterator<std::vector<int>::iterator> rev_it = v.rbegin();
	std::reverse_iterator<std::vector<char>::iterator> rev_it2 = v.rend();
	// std::cout << rev_it2.base() << std::endl;
	// std::cout << rev_it.base() << std::endl;
	// if (rev_it2 > rev_it)
	// 	std::cout << "hello\n";
	// for(it = v.begin(); it != v.end(); it++,i++ )    {
	// 	// found nth element..print and break.
	// 	if(i == n) {
			std::cout<< *it << std::endl;  // prints d.
	// 		break;
	// 	}
	// }

	std::vector<int>::reverse_iterator	ri(it);
	std::cout << *it.base() << std::endl; // PRINTS 1
	std::cout << *ri.base() << std::endl; // PRINTS 1
	ri++;
	std::cout << *it << std::endl; // PRINTS 1
	std::cout << *ri << std::endl; // PRINTS 1
	std::cout << *ri.base() << std::endl; // PRINTS 1
		// typedef std::iterator_traits<std::vector<int>:: iterator> traits;
		// 	if (typeid(traits::iterator_category)==typeid(std::random_access_iterator_tag))
		// 		std::cout << "int* is a random-access iterator";
	return 0;
}