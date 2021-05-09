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
void printLiterals(const std::set<char> temp);
bool operator!=(std::vector<clause> lhs, std::vector<clause> rhs);

int main() {
	clause c1, c2, c3, c4, c5, c6;

	// Example 1, 
	std::string c1elements{ "-s-pi" };
	std::string c2elements{ "-pim" };
	std::string c3elements{ "-mp" };
	std::string c4elements{ "-m-i" };
	std::string c5elements{ "m" };
	std::string c6elements{ "spc" };

	c1.insertLiteral(c1elements);
	c2.insertLiteral(c2elements);
	c3.insertLiteral(c3elements);
	c4.insertLiteral(c4elements);
	c5.insertLiteral(c5elements);
	c6.insertLiteral(c6elements);

//	c1.print();
//	c2.print();
//	c3.print();
//	c4.print();
//	c5.print();
//	c6.print();

	//Resolution
	//auto result = resolution(c4, c5);
	//std::cout << std::endl;
	//result.print();

	std::vector<clause> knowledgeBase;
	knowledgeBase.reserve(6);
	knowledgeBase.emplace_back(c1);
	knowledgeBase.emplace_back(c2);
	knowledgeBase.emplace_back(c3);
	knowledgeBase.emplace_back(c4);
	knowledgeBase.emplace_back(c5);
	knowledgeBase.emplace_back(c6);

    // std::cout << c3.isSubset(c4);

    auto rest = resolution(c6, c2);
    rest.print();
    std::cout << "-----------------------" << std::endl;

	// Solver
	knowledgeBase = solver(knowledgeBase);

	std::cout << "Klar\n";

	//std::cout << "Size " << knowledgeBase.size() << std::endl;
	for (auto&& i : knowledgeBase) {
		i.print();
	}
}

//Forms the resolution between two clauses 
clause resolution(clause a, clause b)
{
	std::set<char> ApBn = intersection(a.getPositiveLiterals(), b.getNegativeLiterals());
	std::set<char> AnBp = intersection(a.getNegativeLiterals(), b.getPositiveLiterals());

//	std::cout << "ApBn: \n";
//    for (auto iterator = ApBn.begin(); iterator != ApBn.end(); ++iterator) {
//        std::cout << *iterator;
//    }

    //std::cout << "\nAnBp: \n";
	clause c;
	clause empty;

	// If both empty, return false
	if (ApBn.empty() && AnBp.empty()) {
	    //std::cout << "Empty\n";
		return c;
	}
	// if apbn not empty, take random element, in this case the first one.
	// Remove it from A.p and B.n
	// else 
	if (!ApBn.empty()) {
//        std::cout << "ApBn\n";
		char temp = *ApBn.begin();
        a.removePositiveLiteral(temp);
        b.removeNegativeLiteral(temp);
	}
	else if(!AnBp.empty()){
//        std::cout << "AnBp\n";
		char temp = *AnBp.begin();
        a.removeNegativeLiteral(temp);
        b.removePositiveLiteral(temp);
	}

	std::set<char> ApBp, AnBn;
	ApBp = combineSets(a.getPositiveLiterals(), b.getPositiveLiterals());
	AnBn = combineSets(a.getNegativeLiterals(), b.getNegativeLiterals());

	c = { ApBp, AnBn };

	std::set<char> CpCn = intersection(c.getPositiveLiterals(), c.getNegativeLiterals());

	if (!CpCn.empty()) {
//		std::cout << "Duplicates" << std::endl;
		return empty;
	}

	/*while (!CpCn.empty()) {
		c.removePositiveLiteral(*CpCn.begin());
		c.removeNegativeLiteral(*CpCn.begin());
		CpCn.erase(CpCn.begin());
	}*/
	//std::cout << "RETURNING C\n";
	//c.print();
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
//	    std::cout << i;
		result.insert(i);
	}
	for (auto&& i : b) {
//        std::cout << i;
	    result.insert(i);
	}

	return result;
}

void printLiterals(const std::set<char> temp)
{
	for (auto&& i : temp) {
		std::cout << i << " ";
	}
	std::cout << "\n";
}

// Upp�t �r ok

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
		//std::cout << "Sizes: " << KB.size() << " & " << knowledgeBase.size() << std::endl;
		KB = knowledgeBase;
		clause C{};
		int count{};
		std::vector<clause> S{};

		// Nested loops to check all combinations
		// for (auto iter = knowledgeBase.begin(); iter != knowledgeBase.end() - 1; ++iter) {
		for (unsigned i{ 0 }; i < knowledgeBase.size() - 1; i++) {
			for (unsigned j{ 1 }; j < knowledgeBase.size(); j++) {
				C = resolution(knowledgeBase[i], knowledgeBase[j]);
				if (C.size()!= 0) {
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
		std::cout << "------------------------------------------ö\n";

		for (auto&& i : S) {
			i.print();
		}

		std::cout << "------------------------------------------u\n";

		if (!S.empty()) {
			incorporate(S, knowledgeBase);
		}

//		std::cout << "PRINTING " << std::endl;
//		for (auto&& i : knowledgeBase) {
//			i.print();
//		}
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
	std::vector<clause>::iterator it = std::find(knowledgeBase.begin(), knowledgeBase.end(), a);
	if (it != knowledgeBase.end()) {
	    std::cout << "TEST0" << std::endl;
		return knowledgeBase;
	}

	auto it1 = knowledgeBase.begin();

	for (unsigned i{}; i < knowledgeBase.size(); i++) {
		if (knowledgeBase[i].isSubset(a)) {
			std::cout << "TEST1" << std::endl;
			return knowledgeBase;
		}
//        if (a.isSubset(knowledgeBase[i])) {
        else {
            std::cout << "TEST2" << std::endl;
            for (auto &&item : knowledgeBase) {
                item.print();
            }
            knowledgeBase.erase(it1);
            std::cout << "Efter" << std::endl;
            for (auto &&item : knowledgeBase) {
                item.print();
            }
        }
        it1++;
	}

//    for (unsigned i{}; i < knowledgeBase.size(); i++) {
//        if (a.isSubset(knowledgeBase[i])) {
//            std::cout << "TEST2" << std::endl;
//            knowledgeBase.erase(it1);
//        }
//        it1++;
//    }

	knowledgeBase.push_back(a);
	return knowledgeBase;
}
