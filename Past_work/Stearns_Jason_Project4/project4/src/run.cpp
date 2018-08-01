#include "run.h"
#include "FunctionStructs.h"
#include "ParticleSwarm.h"
#include "FireflyAlgorithm.h"
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


run::run()
{
}


run::~run()
{
}

/**
* Runs the Particle swarm and firefly algorithms and places their results in the output files
*
*/
void run::runProject4()
{
	clock_t start;
	double duration;
	ofstream myfile;
	string filename = "timer.csv";
	benchmarkfunctions * benchmarkfunctions1 = createFunctionStruct();
	ParticleSwarm pso = ParticleSwarm();
	FireflyAlgorithm ff = FireflyAlgorithm();
	char option;
	cout << "Which Algorithm would you like to run? " << endl;
	cout << "1) Particle Swarm" << endl;
	cout << "2) Fire Fly" << endl;
	cout << "Option: ";
	cin >> option;
	//run each algorithm depending on user input
	switch (option) {
	case '1':
	{
		for (int i = 0; i < 15; i++) {
			start = clock();
			for (int l = 0; l < 30; l++) {
				pso.PSOAlgorithm(benchmarkfunctions1[i].min, benchmarkfunctions1[i].max, benchmarkfunctions1[i].foo);
			}
			duration = (clock() - start) / (double)CLOCKS_PER_SEC; // print results to file
			myfile.open("results.csv", ios::app); // openfile
			if (myfile.is_open() == false) {
				cout << "Could not open file!" << endl;
			}
			else {
				myfile << "," << duration << "\n";
			}
			myfile.close();
			system("pause");
		}
		break;
	}
	case '2': {
		for (int i = 0; i < 15; i++) {
			start = clock();
			for (int j = 0; j < 30; j++) {

				ff.fireFlyAlgorithm(benchmarkfunctions1[i].min, benchmarkfunctions1[i].max, benchmarkfunctions1[i].foo);
			}
			duration = (clock() - start) / (double)CLOCKS_PER_SEC; // print results to file
			myfile.open("results2.csv", ios::app); // openfile
			if (myfile.is_open() == false) {
				cout << "Could not open file!" << endl;
			}
			else {
				myfile << "," << duration << "\n";
			}
			myfile.close();
		}
		system("pause");
		break;
	}
	default: {
		for (int i = 0; i < 15; i++) {
			start = clock();
			for (int l = 0; l < 30; l++) {
				pso.PSOAlgorithm(benchmarkfunctions1[i].min, benchmarkfunctions1[i].max, benchmarkfunctions1[i].foo);
			}
			duration = (clock() - start) / (double)CLOCKS_PER_SEC; // print results to file
			myfile.open("results.csv", ios::app); // openfile
			if (myfile.is_open() == false) {
				cout << "Could not open file!" << endl;
			}
			else {
				myfile << "," << duration << "\n";
			}
			myfile.close();
			start = clock();
			for (int j = 0; j < 30; j++) {

				ff.fireFlyAlgorithm(benchmarkfunctions1[i].min, benchmarkfunctions1[i].max, benchmarkfunctions1[i].foo);
			}
			duration = (clock() - start) / (double)CLOCKS_PER_SEC; // print results to file
			myfile.open("results2.csv", ios::app); // openfile
			if (myfile.is_open() == false) {
				cout << "Could not open file!" << endl;
			}
			else {
				myfile << "," << duration << "\n";
			}
			myfile.close();
		}
		system("pause");
	}
	}
}

