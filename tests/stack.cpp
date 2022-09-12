/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hadd <ael-hadd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 09:27:06 by ael-hadd          #+#    #+#             */
/*   Updated: 2022/09/11 15:39:18 by ael-hadd         ###   ########.fr       */
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
	#include "../vector.hpp"
	#include "../stack.hpp"
#endif

template<typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};


int main()
{
	{
			
		ft::stack<std::string> s0;
		for (int i = 0; i < 5; i++)
			s0.push("1337");
		
		MutantStack<std::string> s1;
		ft::stack<std::string, std::deque<std::string> > s2;
		std::cout << "s0 is empty = " << s0.empty() << std::endl;
		std::cout << "s1 is empty = " << s1.empty() << std::endl;
		s1.push("42");
		s1.push("42");
		s1.push("42");

		s2.push("1337");
		s2.push("1337");
		s2.push("1337");
		std::cout << "s1 is empty = " << s1.empty() << std::endl;
		std::cout << "s0 size = " << s0.size() << std::endl;
		std::cout << "s1 size = " << s1.size() << std::endl;
		for (; s0.size(); )	{
			std::cout << s0.top() << std::endl;
			s0.pop();
		}
		std::cout << std::endl;
		for (MutantStack<std::string>::iterator it = s1.begin(); it != s1.end(); it++)	{
			std::cout << *it << std::endl;
		}
		std::cout << std::endl;
		s0.push("42");
		s0.push("42");
		s0.push("42");
		if (s0 == s1)
			std::cout << "s0 and s1 are equal" << std::endl;
		
	}
	// system("leaks a.out");
}