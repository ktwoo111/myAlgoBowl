#include "info.h"
#include<iostream>
using namespace std;
Info::Info() {
	id = 0;
	totalCost = 0;
	perCost = 0;
	subSet = set<int>();
}

Info::Info(int id, set<int> subSet, int totalCost, double perCost) {
	this->id = id;
	this->subSet = subSet;
	this->totalCost = totalCost;
	this->perCost = perCost;
}
void Info::Print() {
	for (int x : subSet) {
		cout << x;
	}
	cout << endl;
	cout << "totalCost: " << totalCost << endl;
	cout << "perCost: " << perCost << endl << endl;

}