#include "clause.h"
#include <iostream>
#include <iterator>
#include <string>
#include <algorithm>


clause::clause() 
{
}

clause::clause(const clause& rhs): n(rhs.n), p(rhs.p)
{
}

clause::clause(const std::set<char>& p, const std::set<char>& n) : p(p), n(n)
{
}

// Function to insert new litterals to a clause
void clause::insertLiteral(const std::string& elements)
{
	for (auto it = elements.begin(); it != elements.end(); it++) {
		if (*it == '-') {
			it++;
			this->n.insert(*it);
		}
		else {
			this->p.insert(*it);
		}
	}
}

void clause::removeFirstPositiveLitteral()
{
	p.erase(this->p.begin());
}

void clause::removeFirstNegativeLitteral()
{
	n.erase(this->n.begin());
}

// Prints a clause
void clause::print()
{
	std::cout << "P: ";
	for (auto&& i : this->p) {
		std::cout << i << " ";
	}

	std::cout << std::endl << "N: ";
	for (auto&& i : this->n) {
		std::cout << i << " ";
	}
	std::cout << std::endl << "------" << std::endl;
}



const std::set<char> clause::getPositiveLitterals()
{
	return this->p;
}
const std::set<char> clause::getNegativeLitterals()
{
	return this->n;
}

