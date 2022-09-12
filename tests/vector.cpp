/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hadd <ael-hadd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 11:20:10 by ael-hadd          #+#    #+#             */
/*   Updated: 2022/09/11 15:11:40 by ael-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <deque>
#if STL //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	#include <set>
	namespace ft = std;
#else
	// #include "../map.hpp"
	// #include <stack.hpp>
	#include "../vector.hpp"
	// #include "../stack.hpp"
#endif


int main(void)
{
	try{
		// ft::vector<int> v0;
		// ft::vector<int> v1;
		
		// for (size_t i = 0; i < 20; i++)
		// {
		// 	std::cout << v0.size() << "**" << v0.capacity() << std::endl;
		// 	v0.push_back(i);
			
		// }
		// std::cout << v0.size() << "++" << v0.capacity() << std::endl;
		// v0.assign(20, 11);
		// std::cout << v0.size() << "--" << v0.capacity() << std::endl;
		// for (ft::vector<int>::iterator i = v0.begin(); i != v0.end(); i++)
		// 	std::cout << *i << std::endl;
		// v0.assign(24, 1);
		// std::cout << v0.size() << "--" << v0.capacity() << std::endl;
		// v0.insert(v0.begin(), 20, 15);
		// std::cout << v1.size() << "--" << v1.capacity() << std::endl;
		// ft::vector<int>::iterator it0 = v0.begin();
		// v0.push_back(5);
		// v0.push_back(6);
		// v0.push_back(7);
		// v0.push_back(7);
		// while (it0 != v0.end())
		// {
		// 	std::cout << *it0++ << std::endl;
		// }
		
			
		
		
		ft::vector<int> v0;
		ft::vector<int> v1(5, 1337);
		ft::vector<int> v2(v1.begin(), v1.end());
		ft::vector<int> v3(v1);
		for (ft::vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
			std::cout << *it << std::endl;
		if (ft::equal(v1.begin(), v1.end(), v2.begin()) && ft::equal(v2.begin(), v2.end(), v1.begin()) &&
			ft::equal(v1.begin(), v1.end(), v3.begin()) && ft::equal(v3.begin(), v3.end(), v1.begin()))
			std::cout << "v1, v2, v3 are equal" << std::endl;
		v3 = v0;
		if (ft::equal(v1.begin(), v1.end(), v2.begin()) && ft::equal(v2.begin(), v2.end(), v1.begin()) &&
			ft::equal(v1.begin(), v1.end(), v3.begin()) && ft::equal(v3.begin(), v3.end(), v1.begin()))
			std::cout << "v1, v2, v3 are equal" << std::endl;
		if (ft::equal(v0.begin(), v0.end(), v3.begin()) && ft::equal(v3.begin(), v3.end(), v0.begin()))
			std::cout << "v0, v3 are equal" << std::endl;
		
		std::cout << "v3 size = " << v3.size() << std::endl;
		std::cout << "v3 capacity = " << v3.capacity() << std::endl;
		std::cout << "v3 is empty = " << v3.empty() << std::endl;
		v3.reserve(3);
		std::cout << "v3 size after reserve = " << v3.size() << std::endl;
		std::cout << "v3 capacity after reserve = " << v3.capacity() << std::endl;
		v3[0] = 15;
		v3[3] = 42;
		for (ft::vector<int>::iterator it = v3.begin(); it != v3.end(); it++)
			std::cout << *it << std::endl;
		v2.at(2) = 21;
		std::cout << v2.at(2) << std::endl;
		v2.front() = 21;
		std::cout << v2.front() << std::endl;
		v2.back() = 21;
		std::cout << v2.back() << std::endl;
		std::cout << std::endl;
		for (ft::vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
			std::cout << *it << std::endl;
		std::cout << std::endl;
		std::cout << "v1 size = " << v1.size() << " -- v1 capacity == " << v1.capacity() << std::endl;
		v1.pop_back();
		v1.pop_back();
		std::cout << "v1 size = " << v1.size() << " -- v1 capacity == " << v1.capacity() << std::endl;
		for (ft::vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
			std::cout << *it << std::endl;
		v1.insert(v1.begin(), 3, 42);
		for (ft::vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
			std::cout << *it << std::endl;
		std::cout << std::endl;
		v1.insert(v1.begin() + 3, v0.begin(), v0.end());
		for (ft::vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
			std::cout << *it << std::endl;
		std::cout << std::endl;
		v1.erase(v1.begin() + 3);
		v1.erase(v1.begin() + 3);
		v1.erase(v1.begin() + 3);

		for (ft::vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
			std::cout << *it << std::endl;
		v1.erase(v1.begin(), v1.begin() + 3);
		std::cout << std::endl;
		for (ft::vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
			std::cout << *it << std::endl;
		v1.resize(10, 42);
		std::cout << std::endl;
		for (ft::vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
			std::cout << *it << std::endl;
		v1.swap(v0);
		std::cout << std::endl;
		for (ft::vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
			std::cout << *it << std::endl;
		std::cout << std::endl;
		for (ft::vector<int>::iterator it = v0.begin(); it != v0.end(); it++)
			std::cout << *it << std::endl;
		v0.clear();
		v1.clear();
		v2.clear();
		v3.clear();
		std::cout << std::endl;
		for (ft::vector<int>::iterator it = v0.begin(); it != v0.end(); it++)
			std::cout << *it << std::endl;
		
		
		

	}
	catch (std::exception& exc)
	{
		std::cout << exc.what() << '\n';
	}

	// system("leaks a.out");
}