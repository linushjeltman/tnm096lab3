#include <iostream>
#include <map>
#include "clause.h"
#include <string>
#include <utility>
#include <optional>
#include <algorithm>

clause resolution(clause a, clause b);
//std::optional<clause> resolution(clause& a, clause& b);
std::vector<clause> solver(std::vector<clause>& knowledgeBase);
void incorporate(std::vector<clause>& s, std::vector<clause>& knowledgeBase);
std::vector<clause> incorporate_clause(clause& a, std::vector<clause>& knowledgeBase);
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


	std::cout << c3.isSubset(c4);

	// Solver
	knowledgeBase = solver(knowledgeBase);

	std::cout << "Klar\n";

	std::cout << "Size " << knowledgeBase.size() << std::endl;
	for (auto&& i : knowledgeBase) {
		i.print();
	}
}

//Forms the resolution between two clauses 
clause resolution(clause a, clause b)
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
		//std::cout << "Duplicates" << std::endl;
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

// Uppåt är ok

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

std::vector<clause> solver(std::vector<clause>& knowledgeBase)
{
	std::vector<clause> KB{};
	while (KB.size() != knowledgeBase.size())
	{
		std::cout << "Sizes: " << KB.size() << " & " << knowledgeBase.size() << std::endl;
		KB = knowledgeBase;
		clause C{};
		int count{};
		std::vector<clause> S{};

		// Nested loops to check all combinations
		// for (auto iter = knowledgeBase.begin(); iter != knowledgeBase.end() - 1; ++iter) {
		for (unsigned i{ 0 }; i < knowledgeBase.size() - 1; i++) {
			for (unsigned j{ 1 }; j < knowledgeBase.size(); j++) {
				C = resolution(knowledgeBase[i], knowledgeBase[j]);
				// KIKa
				if (!(C.getPositiveLitterals().empty() && C.getNegativeLitterals().empty())) {
					if (std::find(S.begin(), S.end(), C) == S.end()) {
						S.emplace_back(C);
					}
				}
				count++;
			}
		}

		//std::cout << "Counter: " << count << std::endl;
		/*for (auto&& i : S) {
			if (i.isEmpty()) {
				return knowledgeBase;
			}
		}*/
		//std::cout << "PRINTING knowLedgeBase" << std::endl;
		//for (auto&& i : knowledgeBase) {
		//	i.print();
		//}
		std::cout << "------------------------------------------\n";

		for (auto&& i : S) {
			i.print();
		}

		std::cout << "------------------------------------------\n";

		if (!S.empty()) {
			incorporate(S, knowledgeBase);
		}

		std::cout << "PRINTING " << std::endl;
		for (auto&& i : knowledgeBase) {
			i.print();
		}

	}

	return knowledgeBase;
}

void incorporate(std::vector<clause>& S, std::vector<clause>& knowledgeBase)
{
	for (auto&& i : S) {
		//std::cout << "Here" << std::endl;
		clause A = i;
		knowledgeBase = incorporate_clause(i, knowledgeBase);
	}
}

std::vector<clause> incorporate_clause(clause& a, std::vector<clause>& knowledgeBase)
{
	//std::vector<clause>::iterator it = std::find(knowledgeBase.begin(), knowledgeBase.end(), a);
	//if (it != knowledgeBase.end()) {
	//	return knowledgeBase;
	//}

	//Byt looptyp, programmet kommer inte längre än till slutet av loopen...
	auto it1 = knowledgeBase.begin();

	for (unsigned i{}; i < knowledgeBase.size(); i++) {
		if (knowledgeBase[i].isSubset(a)) {
			//std::cout << "TEST1" << std::endl;
			return knowledgeBase;
		}
		else if (a.isSubset(knowledgeBase[i]) /*&& a.size() != knowledgeBase[i].size()*/) {
			std::cout << "TEST2" << std::endl;
			knowledgeBase.erase(it1);
		}
		it1++;
		//std::cout << "Not subset" << std::endl;
	}

	//for (auto&& B : knowledgeBase) {
	//	B.print();

	//	if (B.isSubset(a)) {
	//		std::cout << "TEST1" << std::endl;
	//		return knowledgeBase;
	//	}
	//	else if (a.isSubset(B) && a != B) {
	//		std::cout << "TEST2" << std::endl;
	//		knowledgeBase.erase(it1);
	//	}
	//	it1++;
	//	std::cout << "Not subset" << std::endl;
	//}

	//std::cout << "Before" << std::endl;
	//for (auto&& B : knowledgeBase) {
	//	if (a.isSubset(B) && a != B) {
	//		std::cout << "TEST2" << std::endl;
	//		knowledgeBase.erase(it1);
	//	}
	//	
	//}

	//a.print();
	//std::cout << "After" << std::endl;
	knowledgeBase.push_back(a);

	return knowledgeBase;
}
