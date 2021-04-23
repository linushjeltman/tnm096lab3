#pragma once
#include <set>
#include <vector>
#include <string>

class clause
{
private: 
	std::set<char> p;
	std::set<char> n;
	std::set<char> np;
public: 
	void insertLiteral(const std::string &elements);
	void print();
	void intersection(const std::set<char>& rhsP);
	std::set<char> getLitterals();
	
};

