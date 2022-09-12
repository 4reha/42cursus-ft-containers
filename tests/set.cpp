/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hadd <ael-hadd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 08:35:35 by ael-hadd          #+#    #+#             */
/*   Updated: 2022/09/11 15:14:29 by ael-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <deque>
#include <unistd.h>
#if STL //CREATE A REAL STL EXAMPLE
	#include <set>
	#include <map>
	#include <stack>
	#include <vector>
	#include <set>
	namespace ft = std;
#else
	#include "../map.hpp"
	#include "../stack.hpp"
	#include "../vector.hpp"
	#include "../set.hpp"
#endif

int main()
{
	{
		ft::set<int> set;
		for (int i = 0; i <= 10; i++)
			set.insert(i);
		for (ft::set<int>::iterator it = set.begin(); it != set.end(); it++)
			std::cout << *it << std::endl;
		
		ft::set<int> set2(set.begin(),set.end());
		std::cout << std::endl;
		for (ft::set<int>::iterator it = set2.begin(); it != set2.end(); it++)
			std::cout << *it << std::endl;
			
		ft::set<int> set3(set);
		std::cout << std::endl;
		for (ft::set<int>::iterator it = set3.begin(); it != set3.end(); it++)
			std::cout << *it << std::endl;
		ft::set<int> set4;
		set4.swap(set3);
		std::cout << std::endl;
		for (ft::set<int>::iterator it = set4.begin(); it != set4.end(); it++)
			std::cout << *it << std::endl;
		std::cout << std::endl;

		
		set2.clear();
		for (int i = 115; i <= 130; i++)
			set2.insert(i);
		std::cout << std::endl;
		for (ft::set<int>::iterator it = set2.begin(); it != set2.end(); it++)
			std::cout << *it << std::endl;
		std::cout << std::endl;
		set3 = set2;
		if (set3 == set2)
			std::cout << "set3 and set2 are equal"<<std::endl;
			
		ft::set<int>::iterator it = set2.find(120);
		std::cout << *it << std::endl;
		if (!set3.empty())
			std::cout << set3.size() << std::endl;
		set3.insert(set3.begin(), 42);
		if (set3.erase(42))
			std::cout << "42 delete successfully" << std::endl;
		ft::set<int>::iterator it2 = set3.find(42);
		if (it2 == set3.end())
			std::cout << "42: No such key has found" << std::endl;
		it = set2.find(120);
		set2.erase(it);
		std::cout << std::endl;
		std::cout << "size ==" << set2.size() << std::endl;
		set2.erase(set2.begin(), set2.end());
		set2.clear();
		std::cout << std::endl;
		for (ft::set<int>::iterator it = set2.begin(); it != set2.end(); it++)
			std::cout << *it << std::endl;
		std::cout << "size == " << set2.size() << std::endl;
		std::cout << set3.size() << "----" << set.size() << std::endl;
		set3.clear();
		for (ft::set<int>::iterator it = set.begin(); it != set.end(); it++)
			std::cout << *it << std::endl;
		std::cout << set3.size() << "----" << set.size() << std::endl;
		if (set3 == set2)
			std::cout << "set3 and set2 are equal"<<std::endl;
		std::cout << std::endl;
		for (ft::set<int>::iterator it2 = set.begin(); it2 != set.end(); it2++)
			std::cout << *it2 << "====" << *it2 << std::endl;
		std::cout << std::endl;
		set3.swap(set);
		std::cout << set3.size() << "----" << set.size() << std::endl;
		for (ft::set<int>::iterator it2 = set3.begin(); it2 != set3.end(); it2++)
			std::cout << *it2 << "=" << *it2 << std::endl;	
		std::cout << std::endl;
		std::cout << *set3.lower_bound(4) << std::endl;
		std::cout << *set3.upper_bound(8) << std::endl;
		std::cout << std::endl;
		
	}
		// system("leaks a.out");
}