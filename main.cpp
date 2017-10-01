#include<iostream>
#include "info.h"
#include <vector>
#include <fstream>
#include<algorithm>
using namespace std;

void GetFile(string filename, vector<Info>& subSets, int& universalSetSize, int& numberOfSets) {
	ifstream fin(filename);

	int id = 1;
	int totalCost = 0;
	double perCost = 0;
	int number = 0;
	set<int> tempSet;


	fin >> universalSetSize >> numberOfSets;
	while (!fin.eof()) {
		do {
			
			fin >> number;
			tempSet.insert(number);
		} while (fin.peek() != '\n');
		
		fin >> totalCost;
		perCost = totalCost / tempSet.size();
		subSets.push_back(Info(id,tempSet,totalCost,perCost));
		tempSet.clear();
		id++;
	}

	sort(subSets.begin(), subSets.end(), [](const auto& lhs, const auto& rhs) {
		return (lhs.perCost <= rhs.perCost) && (lhs.totalCost <= rhs.totalCost);
	});
	cout << "End" << endl;
}



int main() {
	int universalSetSize(0), numberOfSets(0);
	vector<Info> subSets;
	GetFile("testing.txt",subSets, universalSetSize, numberOfSets);

	for (Info x : subSets) {
		x.Print();
	}



	return 0;
}