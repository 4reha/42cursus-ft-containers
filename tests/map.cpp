/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hadd <ael-hadd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 08:35:35 by ael-hadd          #+#    #+#             */
/*   Updated: 2022/09/11 15:13:19 by ael-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <deque>
#include <unistd.h>
#if STL //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	#include <set>
	namespace ft = std;
#else
	#include "../map.hpp"
	#include "../stack.hpp"
	#include "../vector.hpp"
	// #include "set.hpp"
#endif

int main()
{
	try
	{
		// ft::map<int, char> map1;
		// // ft::map<int, char> map2;
		// map1[1] = 'a';
		// map1[2] = 'b';
		// map1[3] = 'c';
		// map1[4] = 'd';
		// ft::map<int, char>::iterator it = map1.begin();
		// map1[0] = '0';
		// map1[5] = 'e';
		// map1[6] = 'f';
		// while (it != map1.end())
		// {
		// 	std::cout << it->first << "==" << it->second << std::endl;
		// 	it++;
		// }
		
		
		
		// map2[5] = 'w';
		// map2[6] = 'x';
		// map2[7] = 'y';
		// map2.clear();
		
		// map1.swap(map2);
		// std::cout << "map1: "<< std::endl;
		// for (ft::map<int, char>::iterator it = map1.begin(); it != map1.end(); it++)
		// 	std::cout << it->first << "=" << it->second << std::endl;
		// std::cout << std::endl;
		// std::cout << "map2: "<< std::endl;
		// for (ft::map<int, char>::iterator it = map2.begin(); it != map2.end(); it++)
		// 	std::cout << it->first << "=" << it->second << std::endl;


		
		ft::map<int, int> map;
		for (int i = 0; i <= 10; i++)
			map[i] = 20+i;
		for (ft::map<int, int>::iterator it = map.begin(); it != map.end(); it++)
			std::cout << it->first << "=" << it->second << std::endl;
		
		ft::map<int, int> map2(map.begin(),map.end());
		std::cout << std::endl;
		for (ft::map<int, int>::iterator it = map2.begin(); it != map2.end(); it++)
			std::cout << it->first << "=" << it->second << std::endl;
			
		ft::map<int, int> map3(map);
		std::cout << std::endl;
		for (ft::map<int, int>::iterator it = map3.begin(); it != map3.end(); it++)
			std::cout << it->first << "=" << it->second << std::endl;
		ft::map<int, int> map4;
		map4.swap(map3);
		std::cout << std::endl;
		for (ft::map<int, int>::iterator it = map4.begin(); it != map4.end(); it++)
			std::cout << it->first << "=" << it->second << std::endl;
		std::cout << std::endl;

		
		map2.clear();
		for (int i = 115; i <= 130; i++)
			map2[i] = 20+i;
		std::cout << std::endl;
		for (ft::map<int, int>::iterator it = map2.begin(); it != map2.end(); it++)
			std::cout << it->first << "=" << it->second << std::endl;
		map3 = map2;
		if (map3 == map2)
			std::cout << "map3 and map2 are equal"<<std::endl;
			
		map2.at(120) = 1337;
		std::cout << map2[120] << std::endl;
		if (!map3.empty())
			std::cout << map3.size() << std::endl;
		map3.insert(map3.begin(), ft::make_pair(42, 1337));
		std::cout << map3[42] << std::endl;
		if (map3.erase(42))
			std::cout << "42 delete successfully" << std::endl;
		ft::map<int, int>::iterator it = map3.find(42);
		if (it == map3.end())
			std::cout << "42: No such key has found" << std::endl;
		std::cout << map2[120] <<std::endl;
		it = map2.find(120);
		map2.erase(it);
		std::cout << map2[120] <<std::endl;
		std::cout << std::endl;
		for (ft::map<int, int>::iterator it = map2.begin(); it != map2.end(); it++)
			std::cout << it->first << "=" << it->second << std::endl;
		std::cout << "size ==" << map2.size() << std::endl;
		map2.erase(map2.begin(), map2.end());
		map2.clear();
		std::cout << std::endl;
		for (ft::map<int, int>::iterator it = map2.begin(); it != map2.end(); it++)
			std::cout << it->first << "=" << it->second << std::endl;
		std::cout << "size == " << map2.size() << std::endl;
		std::cout << map3.size() << "----" << map.size() << std::endl;
		map3.clear();
		for (ft::map<int, int>::iterator it = map.begin(); it != map.end(); it++)
			std::cout << it->first << "=" << it->second << std::endl;
		std::cout << map3.size() << "----" << map.size() << std::endl;
		if (map3 == map2)
			std::cout << "map3 and map2 are equal"<<std::endl;
		std::cout << std::endl;
		for (ft::map<int, int>::iterator it2 = map.begin(); it2 != map.end(); it2++)
			std::cout << it2->first << "====" << it2->second << std::endl;
		std::cout << std::endl;
		map3.swap(map);
		std::cout << map3.size() << "----" << map.size() << std::endl;
		for (ft::map<int, int>::iterator it2 = map3.begin(); it2 != map3.end(); it2++)
			std::cout << it2->first << "=" << it2->second << std::endl;	
		std::cout << std::endl;
		std::cout << map3.lower_bound(4)->first << "=" << map3.lower_bound(4)->second << std::endl;
		std::cout << map3.upper_bound(8)->first << "=" << map3.upper_bound(8)->second << std::endl;
		std::cout << std::endl;
		
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
		// system("leaks a.out");
}