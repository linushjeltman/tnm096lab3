#include <iostream>
#include <map>
#include "clause.h"
#include <string>

clause resolution(const clause& a, const clause& b);
std::vector<clause> solver(std::vector<clause> knowledgeBase);
std::vector<clause> incorporate(std::vector<clause> s, std::vector<clause> knowledgeBase);
std::vector<clause> incorporate_clause(clause a, std::vector<clause> knowledgeBase);

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

	clause result = resolution(c1, c2);
	
	// Resolution
	// Solver
	// Incorporate
	// Incorporate_clause

}

// Forms the resolution between two clauses 
clause resolution(clause& a, clause& b)
{
	std::set<char> iAnBp;
	std::set<char> iBnAp;
	a.intersection(b.getLitterals());

	return clause();
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
