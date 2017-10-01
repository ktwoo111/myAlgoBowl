#pragma once
#include <set>
#include "set.h"
using namespace std;

class Info {
public:
	int id;
	Set<int> subSet;
	int totalCost;
	double perCost;
	bool IsUniversalSet;
	Info();
	Info(int id, Set<int> subSet, int totalCost, double perCost, bool IsUniversalSet);
	void Print();
};