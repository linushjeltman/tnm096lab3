#include "clause.h"
#include <iostream>
#include <iterator>
#include <string>
#include <algorithm>


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
void clause::intersection(const std::set<char>& rhsP)
{
	if (!this->n.empty() && !rhsP.empty()) {
		for (auto&& i : rhsP) {
			if (this->n.find(i) != this->n.end()) {
				this->np.insert(i);
			}
		}
	}
	else {
		std::cout << "Set is empty!" << std::endl;
	}
}

std::set<char> clause::getLitterals()
{
	return std::set<char>();
}

