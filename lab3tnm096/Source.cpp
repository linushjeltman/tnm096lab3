#include <iostream>
#include <map>
#include "clause.h"
#include <string>
#include <utility>
#include <optional>

clause resolution(clause& a, clause& b);
//std::optional<clause> resolution(clause& a, clause& b);
std::vector<clause> solver(std::vector<clause> knowledgeBase);
std::vector<clause> incorporate(std::vector<clause> s, std::vector<clause> knowledgeBase);
std::vector<clause> incorporate_clause(clause a, std::vector<clause> knowledgeBase);
std::set<char> intersection(const std::set<char>& a, const std::set<char>& b);

int main() {
	clause c1;
	clause c2;

	// Example 1, 
	std::string c1elements{ "ab-c" };
	std::string c2elements{ "bc" };

	c1.insertLiteral(c1elements);
	c2.insertLiteral(c2elements);

	c1.print();
	c2.print();

	std::set<char> anbp = intersection(c1.getNegativeLitterals(), c2.getPositiveLitterals());
	std::set<char> apbn = intersection(c2.getNegativeLitterals(), c1.getPositiveLitterals());


	auto result = resolution(c1, c2);
	std::cout << std::endl;
	result.print();
	// Resolution
	// Solver
	// Incorporate
	// Incorporate_clause

}

//Forms the resolution between two clauses 
clause resolution(clause& a, clause& b)
{
	std::pair<std::set<char>, std::set<char>> intersections;
	std::set<char> ApBn = intersection(a.getPositiveLitterals(), b.getNegativeLitterals());
	std::set<char> AnBp = intersection(a.getNegativeLitterals(), b.getPositiveLitterals());
	
	clause empty{ ApBn, AnBp };
	clause c;

	if (ApBn.empty() && AnBp.empty()) {
		return empty;
	}
	while(!ApBn.empty()) {
		
		a.removeFirstNegativeLitteral();
		b.removeFirstPositiveLitteral();

		std::set<char> ApBp = intersection(a.getPositiveLitterals(), b.getPositiveLitterals());
		std::set<char> AnBn = intersection(a.getNegativeLitterals(), b.getNegativeLitterals());
		c = { ApBp, AnBn };
		std::set<char> CpCn = intersection(c.getPositiveLitterals(), c.getNegativeLitterals());

		if (!CpCn.empty()) {
			std::cout << "Duplicates" << std::endl;
		}
	}

		return c;
	return empty;
}

std::set<char> intersection(const std::set<char>& a, const std::set<char>& b)
{
	std::set<char> result{};
	if (!a.empty() && !b.empty()) {
		for (auto&& i : b) {
			if (a.find(i) != a.end()) {
				result.insert(i);
			}
		}
		return result;
	}
	else {
		std::cout << "Set is empty!" << std::endl;
	}
	return result;
}


std::vector<clause> solver(std::vector<clause> knowledgeBase)
{
	return std::vector<clause>();
}

std::vector<clause> incorporate(std::vector<clause> s, std::vector<clause> knowledgeBase)
{
	return std::vector<clause>();
}

std::vector<clause> incorporate_clause(clause a, std::vector<clause> knowledgeBase)
{
	return std::vector<clause>();
}
