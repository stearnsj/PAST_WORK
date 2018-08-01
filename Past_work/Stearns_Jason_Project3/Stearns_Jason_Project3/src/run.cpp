#include "stdafx.h"
#include "run.h"
#include "FunctionStructs.h"
#include "GeneticAlgorithm.h"
#include "DiffAlgorithm.h"
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;

run::run()
{
}


run::~run()
{
}

/**
 * Runs instances of the Genetic and differential Evolution Algorithms.
 * Runs each algorithms for all 15 fitness functions.
 */
void run::runProject3()
{

	clock_t start;
	double duration = 0.0;
	ofstream myfile;
	string filename = "timer1.csv";


	benchmarkfunctions * benchmarkfunctions1 = createFunctionStruct();


	DiffAlgorithm *DA = new DiffAlgorithm();
	GeneticAlgorithm *GA = new GeneticAlgorithm();

	char option;
	cout << "Which Algorithm would you like to run? " << endl;
	cout << "1) Genetic Algorithm" << endl;
	cout << "2) Differential Evolutionary algorithm" << endl;
	cout << "Option: ";
	cin >> option;
	//run each function depending on user input
	switch (option) {
	case '1':
		for (int i = 0; i < 15; i++) {
			for (int l = 0; l < 30; l++) {

				start = clock();
				GA->runGeneticAlgorithm(benchmarkfunctions1[i].min, benchmarkfunctions1[i].max, benchmarkfunctions1[i].name, benchmarkfunctions1[i].foo);
				//cout << benchmarkfunctions1[i].name << " best solution " << GA->runGeneticAlgorithm(benchmarkfunctions1[i].min, benchmarkfunctions1[i].max, benchmarkfunctions1[i].name, benchmarkfunctions1[i].foo) << endl;


				duration = (clock() - start) / (double)CLOCKS_PER_SEC; // print results to file
				myfile.open(filename, ios::app); // openfile
				if (myfile.is_open() == false) {
					cout << "Could not open file!" << endl;
				}
				else {
					myfile << duration << ",";
				}
				myfile.close();


			}

			myfile.open(filename, ios::app); // openfile
			if (myfile.is_open() == false) {
				cout << "Could not open file!" << endl;
			}
			else {
				myfile << "\n";
			}
		}
		myfile.close();
		break;
	case '2':
		for (int i = 8; i < 15; i++) {
			for (int k = 0; k < 30; k++) {
				for (int j = 1; j <= 10; j++) {
					if (/*j == 1 || j == 7 ||*/ j == 9) {
						start = clock();
						DA->runDiffAlgorithm(j, benchmarkfunctions1[i].min, benchmarkfunctions1[i].max, benchmarkfunctions1[i].name, benchmarkfunctions1[i].foo);
						//cout << benchmarkfunctions1[i].name << " best solution " << DA->runDiffAlgorithm(j, benchmarkfunctions1[i].min, benchmarkfunctions1[i].max, benchmarkfunctions1[i].name, benchmarkfunctions1[i].foo) << endl;
						duration = (clock() - start) / (double)CLOCKS_PER_SEC; // print results to file
						myfile.open(filename, ios::app); // openfile
						if (myfile.is_open() == false) {
							cout << "Could not open file!" << endl;
						}
						else {
							myfile << duration << ",";
						}
						myfile.close();
					}
				}
			}
			myfile.open(filename, ios::app); // openfile
			if (myfile.is_open() == false) {
				cout << "Could not open file!" << endl;
			}
			else {
				myfile << "\n";
			}
			myfile.close();

		}
		break;
	default:
		for (int i = 0; i < 15; i++) {
			for (int l = 0; l < 30; l++) {

				start = clock();
				GA->runGeneticAlgorithm(benchmarkfunctions1[i].min, benchmarkfunctions1[i].max, benchmarkfunctions1[i].name, benchmarkfunctions1[i].foo);
				//cout << benchmarkfunctions1[i].name << " best solution " << GA->runGeneticAlgorithm(benchmarkfunctions1[i].min, benchmarkfunctions1[i].max, benchmarkfunctions1[i].name, benchmarkfunctions1[i].foo) << endl;


				duration = (clock() - start) / (double)CLOCKS_PER_SEC; // print results to file
				myfile.open(filename, ios::app); // openfile
				if (myfile.is_open() == false) {
					cout << "Could not open file!" << endl;
				}
				else {
					myfile << duration << ",";
				}
				myfile.close();


			}

			myfile.open(filename, ios::app); // openfile
			if (myfile.is_open() == false) {
				cout << "Could not open file!" << endl;
			}
			else {
				myfile << "\n";
			}
			myfile.close();
		}
		break;
		myfile.open(filename, ios::app); // openfile
		if (myfile.is_open() == false) {
			cout << "Could not open file!" << endl;
		}
		else {
			myfile << "\n";
		}
		myfile.close();
		system("pause");
	}
}

