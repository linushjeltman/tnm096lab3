#include <iostream>
#include <map>
#include "clause.h"
#include <string>
#include <utility>
#include <optional>
#include <algorithm>

clause resolution(clause& a, clause& b);
//std::optional<clause> resolution(clause& a, clause& b);
std::vector<clause> solver(std::vector<clause> &knowledgeBase);
void incorporate(std::vector<clause> &s, std::vector<clause> &knowledgeBase);
std::vector<clause> incorporate_clause(clause &a, std::vector<clause> &knowledgeBase);
std::set<char> intersection(const std::set<char>& a, const std::set<char>& b);
std::set<char> combineSets(const std::set<char>& a, const std::set<char>& b);
void printLitterals(const std::set<char> temp);
bool operator!=(std::vector<clause> lhs, std::vector<clause> rhs);

int main() {
	clause c1, c2, c3, c4, c5;

	// Example 1, 
	std::string c1elements{ "-s-pi" };
	std::string c2elements{ "-pim" };
	std::string c3elements{ "-mp" };
	std::string c4elements{ "-m-i" };
	std::string c5elements{ "m" };

	c1.insertLiteral(c1elements);
	c2.insertLiteral(c2elements);
	c3.insertLiteral(c3elements);
	c4.insertLiteral(c4elements);
	c5.insertLiteral(c5elements);

	//c1.print();
	//c2.print();
	//c3.print();
	//c4.print();
	//c5.print();

	// Resolution
	//auto result = resolution(c4, c5);
	//std::cout << std::endl;
	//result.print();
	
	std::vector<clause> knowledgeBase;
	knowledgeBase.reserve(5);
	knowledgeBase.emplace_back(c1);
	knowledgeBase.emplace_back(c2);
	knowledgeBase.emplace_back(c3);
	knowledgeBase.emplace_back(c4);
	knowledgeBase.emplace_back(c5);

	// Solver
	knowledgeBase = solver(knowledgeBase);
	
	for (auto&& i : knowledgeBase) {
		i.print();
	}
}

//Forms the resolution between two clauses 
clause resolution(clause& a, clause& b)
{
	std::set<char> ApBn = intersection(a.getPositiveLitterals(), b.getNegativeLitterals());
	std::set<char> AnBp = intersection(a.getNegativeLitterals(), b.getPositiveLitterals());

	clause c;
	clause empty;

	// If both empty, return false
	if (ApBn.empty() && AnBp.empty()) {
		return c;
	}
	// if apbn not empty, take random element, in this case the first one.
	// Remove it from A.p and B.n
	// else 
	if (!ApBn.empty()) {
		char temp = *ApBn.begin();
		a.removePositiveLitteral(temp);
		b.removeNegativeLitteral(temp);

	}
	else {
		char temp = *AnBp.begin();

		a.removeNegativeLitteral(temp);
		b.removePositiveLitteral(temp);
	}

	std::set<char> ApBp, AnBn;
	ApBp = combineSets(a.getPositiveLitterals(), b.getPositiveLitterals());
	AnBn = combineSets(a.getNegativeLitterals(), b.getNegativeLitterals());

	c = { ApBp, AnBn };

	std::set<char> CpCn = intersection(c.getPositiveLitterals(), c.getNegativeLitterals());

	if (!CpCn.empty()) {
		std::cout << "Duplicates" << std::endl;
		return empty;
	}
	/*while (!CpCn.empty()) {
		c.removePositiveLitteral(*CpCn.begin());
		c.removeNegativeLitteral(*CpCn.begin());
		CpCn.erase(CpCn.begin());
	}*/
	return c;
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
	//else {
	//	//std::cout << "Set is empty!" << std::endl;
	//	continue;
	//}
	return result;
}

std::set<char> combineSets(const std::set<char>& a, const std::set<char>& b)
{
	std::set<char> result{};
	for (auto&& i : a) {
		result.insert(i);
	}
	for (auto&& i : b) {
		result.insert(i);
	}

	return result;
}

void printLitterals(const std::set<char> temp)
{
	for (auto&& i : temp) {
		std::cout << i << " ";
	}
	std::cout << "\n";
}

bool operator!=(std::vector<clause> lhs, std::vector<clause> rhs)
{
	clause itL = *lhs.begin();
	clause itR = *rhs.begin();
	for (auto&& i : lhs) {
		if (i == itR) {
			return false;
		}
	}
	for (auto&& i : rhs) {
		if (i == itL) {
			return false;
		}
	}
	return true;
}

std::vector<clause> solver(std::vector<clause> &knowledgeBase)
{
	clause C;
	std::vector<clause> KB = knowledgeBase;
	
	int count{};

	do
	{
		std::vector<clause> S;
		KB = knowledgeBase;
		// Nested loops to check all combinations
		//for (auto iter = knowledgeBase.begin(); iter != knowledgeBase.end() - 1; ++iter) {
		for (int i{0}; i < knowledgeBase.size()-1; i++) {
			for (int j{ 1 }; j < knowledgeBase.size(); j++) {
				C = resolution(knowledgeBase[i], knowledgeBase[j]);
				if (!(C.getPositiveLitterals().empty() && C.getNegativeLitterals().empty())) {
					std::cout << "Add to S" << std::endl;
					S.emplace_back(C);
				}
				count++;
			}
		}

		std::cout << "Counter: " << count << std::endl;
		for (auto&& i : S) {
			if (i.isEmpty()) {
				return knowledgeBase;
			}
		}
		incorporate(S, KB);
	} while (knowledgeBase != KB); 

	return std::vector<clause>();
}

void incorporate(std::vector<clause>& S, std::vector<clause>& knowledgeBase)
{
	for (auto&& i : S) {
		clause A = i;
		
		knowledgeBase = incorporate_clause(A, knowledgeBase);
		std::cout << "Incorporate";
	}
}

std::vector<clause> incorporate_clause(clause &a, std::vector<clause> &knowledgeBase)
{
	//std::vector<clause>::iterator it = std::find(knowledgeBase.begin(), knowledgeBase.end(), a);
	//if (it != knowledgeBase.end()) {
	//	return knowledgeBase;
	//}

	for (auto&& B : knowledgeBase) {
		if (B.isSubset(a)) {
			return knowledgeBase;
		}
	}
	std::cout << "Incorporate";

	auto it1 = knowledgeBase.begin();
	for (auto&& B : knowledgeBase) {
		if (a.isSubset(B) && a != B) {
			knowledgeBase.erase(it1);
		}
		it1++;
	}

	knowledgeBase.push_back(a);

	return knowledgeBase;
}
