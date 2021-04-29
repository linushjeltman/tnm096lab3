#include "clause.h"
#include <iostream>
#include <iterator>
#include <string>
#include <algorithm>


clause::clause()
{
}

clause::clause(const clause& rhs) : n(rhs.n), p(rhs.p)
{
	//std::cout << "Copy!" << std::endl;
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

void clause::removePositiveLitteral(const char& temp)
{
	auto it = p.find(temp);
	if (it != p.end()) {
		p.erase(it);
	}
}

void clause::removeNegativeLitteral(const char& temp)
{
	auto it = this->n.find(temp);
	if (it != n.end()) {
		n.erase(it);
	}
}

// Prints a clause
void clause::print()
{
	if (!this->isEmpty()) {
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
}


const std::set<char> clause::getPositiveLitterals()
{
	return this->p;
}
const std::set<char> clause::getNegativeLitterals()
{
	return this->n;
}

void clause::combineClauses(const clause& rhs)
{
	std::string litterals;

	for (auto&& i : rhs.p) {
		litterals += i;
	}
	for (auto&& i : rhs.n) {
		litterals += i;
	}

	this->insertLiteral(litterals);
}

bool clause::isEmpty()
{
	if (this->getNegativeLitterals().empty()) {
		if(this->getPositiveLitterals().empty()) return true;
	}
	return false;
}

bool clause::isSubset(const clause& rhs)
{

	/*
	bool checkSubset(Clause B, Clause A){
	*/

    int counter{0};

    for(const auto& i: rhs.p){
        for(const auto& j: this->p){
            if(i == j) counter++;
        }
    }
    if(counter != rhs.p.size()) return false;
    counter = 0;

    for(const auto& i: rhs.n){
        for(const auto& j: this->n){
            if(i == j) counter++;
        }
    }
    if(counter!=rhs.n.size()) return false;

    return true;

	//std::set<char> lhsp = this->p;
	//std::set<char> lhsn = this->n;
	//auto lhp = lhsp.begin();
	//auto lhn = lhsn.begin();
	//auto rhp = rhs.p.begin();
	//auto rhn = rhs.n.begin();

	//for (;rhn != rhs.n.end(); rhn++) {
	//	for (;lhn != this->n.end(); lhn++) {
	//		if (*rhn == *lhn)
	//			break;
	//	}

	//	/* If the above inner loop was
	//	not broken at all then arr2[i]
	//	is not present in arr1[] */
	//	if (j == m)
	//		return 0;
	//}

	///* If we reach here then all
	//elements of arr2[] are present
	//in arr1[] */
	//return 1;
	//// -----------------------------
	//std::set<char> lhsp = this->p;
	//std::set<char> lhsn = this->n;

	//auto it1 = lhsp.begin();
	//while (it1 != lhsp.end()) {
	//	if (rhs.p.find(*it1) != rhs.p.end()) {
	//		return false;
	//	}
	//	it1++;
	//}

	//auto it2 = lhsn.begin();
	//while (it2 != lhsn.end()) {
	//	if (rhs.n.find(*it2) != rhs.n.end()) {
	//		return false;
	//	}
	//	it2++;
	//}

	//return true;*/
}

bool clause::operator==(const clause& rhs)
{
	for (auto&& i : this->p) {
		if (rhs.p.find(i) == rhs.p.end()) {
			return false;
		}
	}
	for (auto&& i : this->n) {
		if (rhs.n.find(i) == rhs.n.end()) {
			return false;
		}
	}
	return true;
}

bool clause::operator!=(const clause& rhs)
{
	return !(*this == rhs);
}

int clause::size()
{
	return this->size();
}

