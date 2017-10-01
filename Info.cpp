#include "info.h"
#include<iostream>
#include<set>
using namespace std;
Info::Info() {
	id = 0;
	totalCost = 0;
	perCost = 0;
	subSet = set<int>();
	IsUniversalSet = false;
}

Info::Info(int id, set<int> subSet, int totalCost, double perCost , bool IsUniversalSet) {
	this->id = id;
	this->subSet = subSet;
	this->totalCost = totalCost;
	this->perCost = perCost;
	this->IsUniversalSet = IsUniversalSet;
}
void Info::Print() {
	for (int x : subSet) {
		cout << x << " ";
	}
	cout << endl;
	cout << "totalCost: " << totalCost << endl;
	cout << "perCost: " << perCost << endl;
	cout << "IsUniversalSet: " << IsUniversalSet << endl << endl;

}