#include<iostream>
#include "info.h"
#include <vector>
#include <fstream>
#include<algorithm>
using namespace std;

void GetFile(string filename, vector<Info>& subSets,set<int>& universalSet, int& universalSetSize, int& numberOfSets, bool& universalSetExists) {
	ifstream fin(filename);
	fin >> universalSetSize >> numberOfSets;

	int id = 1;
	int totalCost = 0;
	double perCost = 0;
	int number = 0;
	set<int> tempSet;
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
	int universalSetId = 0;
	vector<Info> subSets;
	vector<Info> solutionSets;
	set<int> universalSet;
	set<int> checkSets; //the set that will be constantly built and checked with universalSet
	GetFile("testing.txt",subSets, universalSet,universalSetSize, numberOfSets, universalSetExists);

	solutionSets.push_back(subSets.at(0));
	if (solutionSets.at(0).IsUniversalSet) { universalSetId = solutionSets.at(0).id; }
	for (int i = 1; i < subSets.size(); i++) {
		if (subSets.at(i).IsUniversalSet) { universalSetId = subSets.at(i).id; }
		
		//if the subset is already a subset of the checkSets, don't add
		//else add

		//validate to see if matching with universal Set. if so, break;
	
	}

	//compare if the totalCost of the solutionSet is better than subset containing universal set
	// if cheaper, solutionSets is the answer
	//else that one universal set is the answer



	return 0;
}