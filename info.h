#pragma once
#include <set>
using namespace std;

class Info {
public:
	int id;
	set<int> subSet;
	int totalCost;
	double perCost;
	bool IsUniversalSet;
	Info();
	Info(int id, set<int> subSet, int totalCost, double perCost, bool IsUniversalSet);
	void Print();
};