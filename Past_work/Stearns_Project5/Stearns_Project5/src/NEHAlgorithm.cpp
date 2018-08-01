#include "NEHAlgorithm.h"
#include "FSS.h"
#include "FSSB.h"
#include "FSSNW.h"
#include <algorithm>
#include <functional>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <ctime>
#include <fstream>

using namespace std;
NEHAlgorithm::NEHAlgorithm(string fname)
{
	filename = fname;
	ifstream infile;
	infile.open(filename);

	if (!infile.is_open()) {
		cout << "Error Opening File.\n";
		exit(1);
	}
	else {
		infile >> m_Machines;
		infile >> m_Jobs;

		m_ProcessTime = new float*[m_Machines];
		for (int i = 0; i < m_Machines; i++) {
			m_ProcessTime[i] = new float[m_Jobs];
		}

		for (int i = 0; i < (m_Machines); i++) {
			for (int j = 0; j < m_Jobs; j++) {
				infile >> m_ProcessTime[i][j];
			}
		}

		m_CompletionTime = new float*[m_Machines];
		for (int i = 0; i < m_Machines; i++) {
			m_CompletionTime[i] = new float[m_Jobs];
		}
	}

	infile.close();
}


NEHAlgorithm::~NEHAlgorithm()
{
	for (int i = 0; i < m_Machines; i++) {
		delete[] m_ProcessTime[i];
	}
	delete[] m_ProcessTime;

	for (int i = 0; i < m_Machines; i++) {
		delete[] m_CompletionTime[i];
	}
	delete[] m_CompletionTime;
}

int * NEHAlgorithm::sortbyTime(){

	int * order = new int[m_Jobs];
	strs *objects = (strs *)malloc(m_Jobs * sizeof *objects);
	for (int j = 0; j < m_Jobs; j++) {
		objects[j].index = j;
		objects[j].value = 0;
		for (int i = 0; i < m_Machines; i++){
			objects[j].value += m_ProcessTime[i][j];
		}
	}
	std::sort(objects, objects + m_Jobs, std::greater<strs>());
	for (int j = 0; j < m_Jobs; j++) {
		order[j] = objects[j].index+1;
	}
	free(objects);
	return order;
}

vector <int> NEHAlgorithm::sortFSSbyTime(vector<int> sequence, int nextIndex)
{
	cFSS fss = cFSS(filename);
	int* order = sortbyTime();
	vector<int> best;
	float bestval = FLT_MAX;
	vector<int> temp;
	int *a = new int[sequence.size()+1];
	for (int j = 0; j < sequence.size()+1; j++) {
		temp.assign(sequence.begin(), sequence.end());
		temp.insert(temp.begin() + j, nextIndex);
		float val = fss.Makespan(temp);
		counter++;
		if (val < bestval) {
			best = temp;
			bestval = val;
		}
	}
	delete order;
	delete[] a;
	return best;
}

vector<int> NEHAlgorithm::sortFSSBbyTime(vector<int> sequence, int nextIndex)
{
	cFSSB fss = cFSSB(filename);
	int* order = sortbyTime();
	vector<int> best;
	float bestval = FLT_MAX;
	vector<int> temp;
	int *a = new int[sequence.size() + 1];
	for (int j = 0; j < sequence.size()+1; j++) {
		temp.assign(sequence.begin(), sequence.end());
		temp.insert(temp.begin() + j, nextIndex);
		float val = fss.Makespan(temp);
		counter++;
		if (val < bestval) {
			best = temp;
			bestval = val;
		}
	}
	
	delete order;
	delete[] a;
	return best;
}

vector<int> NEHAlgorithm::sortFSSNWbyTime(vector<int> sequence, int nextIndex)
{
	
	cFSSNW fss = cFSSNW(filename);
	int* order = sortbyTime();
	vector<int> best;
	float bestval = FLT_MAX;
	vector<int> temp;
	int *a = new int[sequence.size() + 1];
	for (int j = 0; j < sequence.size()+1; j++) {
		temp.assign(sequence.begin(), sequence.end());
		temp.insert(temp.begin() + j, nextIndex);
		float val = fss.Makespan(temp);
		counter++;
		if (val < bestval) {
			best = temp;
			bestval = val;
		}
	}
	delete order;
	delete[] a;
	return best;
}

float NEHAlgorithm::runFSSAlgorithm()
{
	start = clock();
	counter = 0;
	fstream myfile;
	cFSS fss = cFSS(filename);
	int* order = sortbyTime();
	vector <int> sequence = { order[0] };
	for (int i = 1; i < m_Jobs; i++) {
		sequence = sortFSSbyTime(sequence, order[i]);
	}
	delete order;
	duration = (clock() - start) / (double)CLOCKS_PER_SEC; // print results to file
	myfile.open("results.csv", ios::app); // openfile
	if (myfile.is_open() == false) {
		cout << "Could not open file!" << endl;
	}
	else {
		myfile << "&" << fss.Makespan(sequence) << "," << "&"<< duration <<"," << "&"<< counter << ",";
	}
	myfile.close();
	return fss.Makespan(sequence);
}

float NEHAlgorithm::runFSSBAlgorithm()
{
	start = clock();
	counter = 0;
	fstream myfile;
	cFSSB fss = cFSSB(filename);
	int* order = sortbyTime();
	vector <int> sequence = { order[0] };
	for (int i = 1; i < m_Jobs; i++) {
		sequence = sortFSSBbyTime(sequence, order[i]);
	}
	delete order;
	duration = (clock() - start) / (double)CLOCKS_PER_SEC; // print results to file
	myfile.open("results.csv", ios::app); // openfile
	if (myfile.is_open() == false) {
		cout << "Could not open file!" << endl;
	}
	else {
		myfile << "&" << fss.Makespan(sequence) << "," << "&" << duration << "," << "&" << counter << ",";
	}
	myfile.close();
	return fss.Makespan(sequence);
}

float NEHAlgorithm::runFSSNWAlgorithm()
{
	start = clock();
	counter = 0;
	fstream myfile;
	cFSSNW fss = cFSSNW(filename);
	int* order = sortbyTime();
	vector <int> sequence = { order[0] };
	for (int i = 1; i < m_Jobs; i++) {
		sequence = sortFSSNWbyTime(sequence, order[i]);
	}
	delete order;
	duration = (clock() - start) / (double)CLOCKS_PER_SEC; // print results to file
	myfile.open("results.csv", ios::app); // openfile
	if (myfile.is_open() == false) {
		cout << "Could not open file!" << endl;
	}
	else {
		myfile << "&" << fss.Makespan(sequence) << "," << "&" << duration << "," << "&" << counter << "," << "\\" << "\n";
	}
	myfile.close();
	return fss.Makespan(sequence);
}
bool operator>(const strs &a, const strs &b)
{
	if ((a).value>(b).value)return true;
	else return false;
}
