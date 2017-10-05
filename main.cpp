#include<iostream>
#include "info.h"
#include <vector>
#include <fstream>
#include<algorithm>
#include<string>
#include<sstream>
#include<set>
using namespace std;

void SetVerifier(vector<Info>& solutions, set<int>& universalSet) {
	set<int> checker;
	cout << "Set should go up to : " << universalSet.size() << endl;
	cout << "subset size: " << solutions.size() << endl;
	for (Info i : solutions) {
		checker.insert(i.subSet.begin(), i.subSet.end());
	}
	if (checker == universalSet) {
		cout << "valid sets" << endl;
	//	for (int i : checker) {
	//		cout << i << " ";
	//	}
	//	cout << endl;
	}
	else {
		cout << "sets not complete" << endl;
		for (int i : checker) {
			cout << i << " ";
		}
		cout << endl;
		exit(0);
	}
}
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
		cout << "File opened" << endl;
	}
	else
	{
		cout << "Error opening file";
		exit;
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
//	for (Info i : subSets) {
//		i.Print();
//	}


	SortInfoVector(subSets);
	cout << "              for the subsets from file: " << endl;
	SetVerifier(subSets, universalSet);
	//cout << "End" << endl;
}
int AddUpCost(vector<Info>& solutions) {
	int cost = 0;
	for (int i = 0; i < solutions.size(); i++) {
		cost += solutions.at(i).totalCost;
	}
	return cost;
}


void OutputFile(vector<Info>& answer, int cost, string FileName) {
	string file = "outputs/Answer_For_" + FileName.substr(5,FileName.length()-4);
	
	ofstream fout(file);
	fout << cost << endl;
	cout << cost << endl;//testing
	for (int i = 0; i < answer.size(); i++) {
		fout << answer.at(i).id << " ";
		cout << answer.at(i).id << " "; //testing
	}
	cout << endl;//testing
	fout.close();
}

void OutputFileUniversal(vector<Info>& answer, string FileName) {
	string file = "./outputs/Answer_For_" + FileName.substr(5, FileName.length() - 4);
	ofstream fout(file);
	fout << answer.at(0).totalCost << endl << answer.at(0).id << endl;
	cout << answer.at(0).totalCost << endl << answer.at(0).id << endl;//testing
	fout.close();
}


void SortBySize(vector<Info>& input) {
	sort(input.begin(), input.end(), [](const auto& lhs, const auto& rhs) {
		//return ((lhs.perCost < rhs.perCost) && (lhs.totalCost < rhs.totalCost));
		return (lhs.subSet.size() < rhs.subSet.size());
	});
}
void CleanUpFunction(vector<Info>& solutions) {
	set<int> checkSet;
	SortBySize(solutions);
	//	for (Info i : solutions) {
	//	i.Print();
	//	}
	for (int i = solutions.size() - 1; i >= 0; i--) {
		if (!includes(checkSet.begin(), checkSet.end(), solutions.at(i).subSet.begin(), solutions.at(i).subSet.end())) {
			checkSet.insert(solutions.at(i).subSet.begin(), solutions.at(i).subSet.end());
		}
		else {
			solutions.erase(solutions.begin()+i);
		}
	}
}


void AlgoBowl(string FileName) {
	cout << endl << endl << FileName << endl; //testing
	int universalSetSize(0), numberOfSets(0);
	bool universalSetExists = false;
	vector<Info> subSets;
	vector<Info> solutions;
	vector<Info> infoWithUniversal;
	set<int> universalSet;
	set<int> checkSets; //the set that will be constantly built and checked with universalSet
	GetFile(FileName, subSets, universalSet, universalSetSize, numberOfSets, universalSetExists);


	bool doNotAddMore = false; // if this is true, then we don't add anymore subset to the "solutions".
	for (int i = 0; i < subSets.size(); i++) {
		if (subSets.at(i).IsUniversalSet == true) { // if that subset is a univeral set, we are putting into a separate container called infoWithUniversal
			infoWithUniversal.push_back(subSets.at(i));
		}
		else if (!includes(checkSets.begin(), checkSets.end(), subSets.at(i).subSet.begin(), subSets.at(i).subSet.end()) && !doNotAddMore) {
			//if that subset is not already a subset of the currently built set and we still have to add more, then add it to the currently building set and add to "solutions"
			checkSets.insert(subSets.at(i).subSet.begin(), subSets.at(i).subSet.end());
			solutions.push_back(subSets.at(i));
		}
		if (checkSets == universalSet) { doNotAddMore = true; }
	}

	SortInfoVector(infoWithUniversal); //Sort vector by perCost



	if (doNotAddMore == false) { // if getting sets from the subsets, excluding ones that are universal sets, cannot complete the universal set, then we would need one of the subsets that are universal
		solutions.push_back(infoWithUniversal.at(0));
	}

	CleanUpFunction(solutions);


	int solutionCost = AddUpCost(solutions);
	if (universalSetExists && !infoWithUniversal.empty()) {
		if (infoWithUniversal.at(0).totalCost <= solutionCost) {
			cout << "           for the subsets from solutions: " << endl;
			SetVerifier(infoWithUniversal, universalSet);
			OutputFileUniversal(infoWithUniversal, FileName);
			
		}
		else {
			cout << "             for the subsets from solutions: " << endl;
			SetVerifier(solutions, universalSet);
			OutputFile(solutions, solutionCost, FileName);

		}
	}
	else {
		cout << "            for the subsets from solutions: " << endl;
		SetVerifier(solutions, universalSet);
		OutputFile(solutions, solutionCost, FileName);
		
	}

}


int main() {

	for (int i = 1; i <= 27; i++) {
		//if (i != 2 && i != 18 && i !=7 && i!= 12) {
		AlgoBowl("test/input_group" + to_string(i) + ".txt");
		//}
	}
	

	


	return 0;
}