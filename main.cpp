#include<iostream>
#include "info.h"
#include <vector>
#include <fstream>
#include<algorithm>
#include<string>
#include<sstream>
#include<set>
using namespace std;

void SortInfoVector(vector<Info>& input) {
	sort(input.begin(), input.end(), [](const auto& lhs, const auto& rhs) {		
		//return ((lhs.perCost < rhs.perCost) && (lhs.totalCost < rhs.totalCost));
		return (lhs.perCost < rhs.perCost);
	});
}
void GetFile(string filename, vector<Info>& subSets,set<int>& universalSet, int& universalSetSize, int& numberOfSets, bool& universalSetExists) {
	ifstream fin(filename);
	if (fin.is_open())
	{
	//	cout << "File opened" << endl;
	}
	else
	{
		cout << "Error opening file";
	}
	fin >> universalSetSize >> numberOfSets;
	fin.ignore();

	int id = 1;
	int totalCost = 0;
	double perCost = 0;
	int number;
	set<int> tempSet;
	for (int i = 1; i <= universalSetSize; i++) {
		universalSet.insert(i);
	}
	
	char hi = 'a';
	string numbers ="";
	for(int i = 0; i < numberOfSets; i++) {
		getline(fin, numbers);
		stringstream linestream(numbers);
		for (int i = 0; i < numbers.size();i++) {
			while (linestream >> number) {
				tempSet.insert(number);
			}
		}
		fin >> totalCost;
		fin.ignore();
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
	//cout << "End" << endl;
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
	cout << cost << endl;//testing
	for (int i = 0; i < answer.size(); i++) {
		fout << answer.at(i).id << " ";
		cout << answer.at(i).id << " "; //testing
	}
	cout << endl;//testing
	fout.close();
}

void OutputFileUniversal(vector<Info>& answer) {
	ofstream fout("answer.txt");
	fout << answer.at(0).totalCost << endl << answer.at(0).id << endl;
	cout << answer.at(0).totalCost << endl << answer.at(0).id << endl;//testing
	fout.close();
}

void AlgoBowl(string FileName) {
	cout << FileName << endl; //testing
	int universalSetSize(0), numberOfSets(0);
	bool universalSetExists = false;
	vector<Info> subSets;
	vector<Info> solutions;
	vector<Info> infoWithUniversal;
	set<int> universalSet;
	set<int> checkSets; //the set that will be constantly built and checked with universalSet
	GetFile(FileName, subSets, universalSet, universalSetSize, numberOfSets, universalSetExists);

//	for (Info i : subSets) {
	//	i.Print();
	//}

	bool doNotAddMore = false;
	for (int i = 0; i < subSets.size(); i++) {
		if (subSets.at(i).IsUniversalSet == true) {
			infoWithUniversal.push_back(subSets.at(i));
		}
		else if (!includes(checkSets.begin(), checkSets.end(), subSets.at(i).subSet.begin(), subSets.at(i).subSet.end()) && !doNotAddMore) {
			checkSets.insert(subSets.at(i).subSet.begin(), subSets.at(i).subSet.end());
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
		else {
			OutputFile(solutions, solutionCost);
		}
	}
	else {
		OutputFile(solutions, solutionCost);
	}

}


int main() {
	/*
	AlgoBowl("test/DanielTest.txt");
	AlgoBowl("test/DanielTest2.txt");
	AlgoBowl("test/MehtaExample.txt");
	AlgoBowl("test/scenario2_10.txt");
	AlgoBowl("test/scenario2_20.txt");
	AlgoBowl("test/scenario2_30.txt");
	AlgoBowl("test/scenario2_100.txt");
	AlgoBowl("test/scenario2_200.txt");
	AlgoBowl("test/scenario2_300.txt");
	AlgoBowl("test/scenario2_400.txt");
	AlgoBowl("test/scenario2_500.txt");
	AlgoBowl("test/scenario3_100.txt");
	AlgoBowl("test/scenario3_200.txt");
	AlgoBowl("test/scenario3_300.txt");
	AlgoBowl("test/scenario3_500.txt");
	AlgoBowl("test/virus.txt");
	AlgoBowl("test/testing.txt");
	AlgoBowl("test/testing2.txt");
	AlgoBowl("test/virus2.txt");
	AlgoBowl("test/virus3.txt");
	AlgoBowl("test/virus4.txt");
	*/
	AlgoBowl("test/testing3.txt");

	return 0;
}