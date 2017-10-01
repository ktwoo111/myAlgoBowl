#include<iostream>
#include "info.h"
#include <vector>
#include <fstream>
#include<algorithm>
using namespace std;

void GetFile(string filename, vector<Info>& subSets, int& universalSetSize, int& numberOfSets, bool& universalSetExists) {
	ifstream fin(filename);
	fin >> universalSetSize >> numberOfSets;

	int id = 1;
	int totalCost = 0;
	double perCost = 0;
	int number = 0;
	set<int> tempSet;
	set<int> universalSet;
	for (int i = 1; i <= universalSetSize; i++) {
		universalSet.insert(i);
	}
	
	while (!fin.eof()) {
		do {
			
			fin >> number;
			tempSet.insert(number);
		} while (fin.peek() != '\n');
		
		fin >> totalCost;
		perCost = double(totalCost) / tempSet.size();
		if (tempSet == universalSet) {
			universalSetExists = true;
		}
		subSets.push_back(Info(id,tempSet,totalCost,perCost, tempSet == universalSet));
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
	bool universalSetExists = false;
	vector<Info> subSets;
	vector<Info> solutionSets;
	GetFile("testing.txt",subSets, universalSetSize, numberOfSets, universalSetExists);
	vector<bool> checks(false, universalSetSize);

	for (int i = 0; i < subSets.size(); i++) {
	
	
	}



	return 0;
}