/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hadd <ael-hadd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 10:25:07 by ael-hadd          #+#    #+#             */
/*   Updated: 2022/08/27 10:43:13 by ael-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"

int main(void) 
{
	ft::vector<int> vector;
	vector.push_back(1);
	vector.push_back(2);
	vector.push_back(3);
	vector.push_back(4);
	vector.push_back(5);
	vector.pop_back();
	ft::vector<int>::iterator it = vector.begin();
	ft::reverse_iterator<ft::vector<int>::iterator>	r = vector.rbegin();
	while (it != vector.end())
	{
		std::cout << *it++ << std::endl;
	}
}