#include "ParticleSwarm.h"
#include "Population.h"
#include "FunctionStructs.h"
#include <random>
#define _USE_MATH_DEFINES
#include <cmath>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;

/**
* Constructor for Particle Swarm calls
* file reader to read in parameters.
*
*/
ParticleSwarm::ParticleSwarm()
{
	fileReader();
}

/**
* Runs Partical Swarm algorithm for a given fitness function 
*
* @param  min  a double representing the minimum of the range
* @param  max  a double representing the maximum of the range
* @param  foo  a pointer to the current fitness function
*/
void ParticleSwarm::PSOAlgorithm(double min, double max, double(*foo)(int dim, double myArray[]))
{
	fileReader();
	Population Swarm = Population(numParticles, dim, min, max);
	Swarm.solveFitness(dim, numParticles, min, max, foo);
	double *temp = new double[dim];
	double * gBest;
	double *tempPart;
	double min2 = min;
	double max2 = max;
	int index = 0;
		for (int i = 1; i < numParticles; i++) {
			if (Swarm.getFitness()[i] < Swarm.getFitness()[index]) {
				index = i;
			}
		}
		gBest = Swarm.getSwarm()[index];
	for (int t = 0; t < iter; t++) {
		for (int j = 0; j < numParticles; j++) {
			for (int k = 0; k < dim; k++) {
				temp[k] = Swarm.getVelocity(j)[k] + c1 * getrandomdouble(0,1) * (Swarm.getpBest(j)[k] - Swarm.getSwarm()[j][k])
					+ c2 * getrandomdouble(0, 1) * (gBest[k] - Swarm.getSwarm()[j][k]);				
				if (temp[k] < min) {
					if (min == 0) {
						min2 = max2;
						temp[k] = fmod(abs(temp[k]), min2);
					}
					else {
						temp[k] = fmod(temp[k], min2);
					}
				}
				else {
					temp[k] = fmod(temp[k], max2);
				}
			}
			Swarm.setVelocity(temp, j, dim);
			tempPart = Swarm.getSwarm()[j];
			for (int l = 0; l < dim; l++) {
				tempPart[l] = tempPart[l] + temp[l];
				if (tempPart[l] < min) {
					if (min == 0) {
						min2 = max2;
						tempPart[l] = fmod(abs(tempPart[l]), min2);
					}
					else {
						tempPart[l] = fmod(tempPart[l], min2);
					}
				}
				else {
					tempPart[l] = fmod(tempPart[l], max2);
				}
			}
			Swarm.setSwarm(tempPart, j, dim);
			if (foo(dim, tempPart) < foo(dim, Swarm.getpBest(j))) {
				Swarm.setpBest(tempPart, j, dim);
			}
			if (foo(dim, Swarm.getpBest(j)) < foo(dim, gBest)) {
				memcpy(gBest, Swarm.getpBest(j), sizeof(double)*dim);
			}
		}
	}
	ofstream myfile;
	string filename = "PSOresults.csv";
	myfile.open(filename, ios::app); // openfile
	if (myfile.is_open() == false) {
		cout << "Could not open file!" << endl;
	}
	else {
		myfile << foo(dim, gBest) << ",";
	}
	myfile.close();
	delete[] temp;
}

/**
* Read in data from config file
*
*/
void ParticleSwarm::fileReader()
{
	ifstream myfile;
	myfile.open("config.txt", std::fstream::in);
	if (myfile.is_open()) {
		myfile >> dim >> numParticles >> iter >> c1 >> c2;
	}
	myfile.close();
}

/**
* returns a randomly generated integer
*
* @param  min  the minimum value to be returned
* @param  max  the maximum value to be returned
*
* @return      A random integer between min and max
*/
int ParticleSwarm::getrandomInt(int min, int max)
{
	static random_device rd{};
	static mt19937 engine{ rd() };
	uniform_int_distribution<int> dist{ min, max };
	return dist(engine);
}

/**
* returns a randomly generated double
*
* @param  min  the minimum value to be returned
* @param  max  the maximum value to be returned
*
* @return      A random double between min and max
*/
double ParticleSwarm::getrandomdouble(double min, double max)
{
	static random_device rd{};
	static mt19937 engine{ rd() };
	uniform_real_distribution<double> dist{ min, max };
	return dist(engine);
}
