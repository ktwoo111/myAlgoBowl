#include<iostream>
#include "info.h"
#include "set.h"
#include <vector>
#include <fstream>
#include<algorithm>
#include "set.h"
using namespace std;

void SortInfoVector(vector<Info>& input) {
	sort(input.begin(), input.end(), [](const auto& lhs, const auto& rhs) {
		return (lhs.perCost <= rhs.perCost) && (lhs.totalCost <= rhs.totalCost);
	});
}
void GetFile(string filename, vector<Info>& subSets,Set<int>& universalSet, int& universalSetSize, int& numberOfSets, bool& universalSetExists) {
	ifstream fin(filename);
	fin >> universalSetSize >> numberOfSets;

	int id = 1;
	int totalCost = 0;
	double perCost = 0;
	int number = 0;
	Set<int> tempSet;
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

	fin.close();

	SortInfoVector(subSets);
	cout << "End" << endl;
}
int AddUpCost(vector<Info>& solutions) {
	int cost = 0;
	for (int i = 0; i < solutions.size(); i++) {
		cost += solutions.at(i).totalCost;
	}
	return cost;
}
void OutputFile(vector<Info>& answer, int cost) {
	ofstream fout("answer.txt");
	fout << cost << endl;
	for (int i = 0; i < answer.size(); i++) {
		fout << answer.at(i).id << " ";
	}
	fout.close();
}

void OutputFileUniversal(vector<Info>& answer) {
	ofstream fout("answer.txt");
	fout << answer.at(0).totalCost << endl << answer.at(0).id << endl;
	fout.close();
}

int main() {
	int universalSetSize(0), numberOfSets(0);
	bool universalSetExists = false;
	vector<Info> subSets;
	vector<Info> solutions;
	vector<Info> infoWithUniversal;
	Set<int> universalSet;
	Set<int> checkSets; //the set that will be constantly built and checked with universalSet
	GetFile("MehtaExample.txt",subSets, universalSet,universalSetSize, numberOfSets, universalSetExists);

	for (Info i : subSets) {
		i.Print();
	}

	bool doNotAddMore = false;
	for (int i = 0; i < subSets.size(); i++) {
		if (subSets.at(i).IsUniversalSet == true) { 
			infoWithUniversal.push_back(subSets.at(i));
		}
		else if (!subSets.at(i).subSet.isSubsetOf(checkSets) && !doNotAddMore) {
			checkSets += subSets.at(i).subSet;
			solutions.push_back(subSets.at(i));
		}
		if (checkSets == universalSet) { doNotAddMore = true; }
	}


	SortInfoVector(infoWithUniversal);
	
	int solutionCost = AddUpCost(solutions);
	if (universalSetExists && !infoWithUniversal.empty()) {
		if (infoWithUniversal.at(0).totalCost <= solutionCost) {
			OutputFileUniversal(infoWithUniversal);
		}
	}
	else {
		OutputFile(solutions,solutionCost);
	}
	
	



	return 0;
}