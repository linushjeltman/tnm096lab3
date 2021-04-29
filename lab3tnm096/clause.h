#pragma once
#include <set>
#include <vector>
#include <string>
#include <utility>

class clause
{
private: 
	std::set<char> p;
	std::set<char> n;
public: 
	clause();
	clause(const clause& rhs);
	clause(const std::set<char>& p, const std::set<char>& n);
	void insertLiteral(const std::string &elements);
	void removePositiveLitteral(const char& temp);
	void removeNegativeLitteral(const char& temp);
	void print();
	const std::set<char> getPositiveLitterals();
	const std::set<char> getNegativeLitterals();
	void combineClauses(const clause& rhs);
	bool isEmpty();
	bool isSubset(const clause& rhs);
	bool operator==(const clause& rhs);
	bool operator!=(const clause& rhs);
	int size();
};


