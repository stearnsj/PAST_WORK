#include "FireflyAlgorithm.h"
#include "Population.h"
#include <fstream>
#include <random>
#include <algorithm>
#include <cstdlib>
#include <iostream>




using namespace std;

FireflyAlgorithm::FireflyAlgorithm()
{
}

/**
* Read in data from config file
*
*/
void FireflyAlgorithm::fileReader()
{
	double lightAbs;
	ifstream myfile;
	myfile.open("config2.txt", std::fstream::in);
	if (myfile.is_open()) {
		myfile >> dim >> numParticles >> iter >> gama >> alpha >> betamin;
	}
	myfile.close();
}

/**
* Returns the global best value
*
* @return      an array containing the global best value
*/
double * FireflyAlgorithm::getgBest()
{
	return gBest;
}

/**
* Sets the global best value of a particle in the swarm
*
* @param  globalBest  an array containing the new best value
* @param  dim  the number of dimensions
*/
void FireflyAlgorithm::setgBest(double globalBest[], int dim)
{
	for (int i = 0; i < dim; i++) {
		gBest[i] = globalBest[i];
	}
}

/**
* Returns an array contain the sorted order of the population based on fitness
*
* @param  population  a reference to the population to be sorted
* @param  foo  a pointer to the current fitness function
*
* @return      an integer array containing the order of the population if it was sorted
*/
int * FireflyAlgorithm::sortbyFitness(Population & population, double(*foo)(int dim, double myArray[]))
{
	int * order = new int[numParticles];
	double * fitness = population.getFitness();
	for (int j = 0; j < numParticles; j++) {
		fitness[j] = foo(dim, population.getSwarm()[j]);
	}
	strs *objects = (strs *)malloc(numParticles * sizeof *objects);
	for (int i = 0; i < numParticles; i++)
	{
		objects[i].value = fitness[i];
		objects[i].index = i;
	}
	sort(objects, objects + numParticles, std::less<strs>());
	for (int j = 0; j < numParticles; j++) {
		order[j] = objects[j].index;
	}
	free(objects);
	return order;
}

/**
* returns a randomly generated integer
*
* @param  min  the minimum value to be returned
* @param  max  the maximum value to be returned
*
* @return      A random integer between min and max
*/
int FireflyAlgorithm::getrandomInt(int min, int max)
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
double FireflyAlgorithm::getrandomdouble(double min, double max)
{
	static random_device rd{};
	static mt19937 engine{ rd() };
	uniform_real_distribution<double> dist{ min, max };
	return dist(engine);
}

/**
* Returns the light intensity level of a firefly
*
* @param  firefly  an array containing the firefly
* @param  v  the distance between two fireflies
* @param  dim  the number of dimensions
* @param  foo  a pointer to the current fitness function
*
* @return      the intensity value of the firefly as a double
*/
double FireflyAlgorithm::getIntensity(double firefly[], double v, int dim, double(*foo)(int dim, double myArray[]))
{
	double value = ((foo(dim, firefly))*exp(-gama*pow(v, 2)));
	return value;
}

/**
* Runs the firefly algorithm for a fitness function
*
* @param  min  a double representing the minimum of the range
* @param  max  a double representing the maximum of the range
* @param  foo  a pointer to the current fitness function
*
*/
void FireflyAlgorithm::fireFlyAlgorithm(double min, double max, double(*foo)(int dim, double myArray[]))
{
	double min2 = min;
	double max2 = max;
	fileReader();
	Population * fireflies = new Population(numParticles, dim, min, max);
	Population * temp = new Population(*fireflies);
	fireflies->solveFitness(dim, numParticles, min, max, foo);
	int* order = sortbyFitness(*fireflies, foo);
	double bestfitness = DBL_MAX;
	double * tempFF = new double[dim];
	int index = 0;
	for (int i = 1; i < numParticles; i++) {
		if (fireflies->getFitness()[i] < fireflies->getFitness()[index]) {
			index = i;
		}
	}
	gBest = fireflies->getSwarm()[index];
	for (int i = 0; i < iter; i++) {
			for (int j = 0; j < numParticles; j++) {
				for (int k = j + 1; k < numParticles; k++) {
					double r = 0.0;
						for (int l = 0; l < dim; l++) {
							r += ((temp->getSwarm()[order[j]][l] - temp->getSwarm()[order[k]][l])*(temp->getSwarm()[order[j]][l] - temp->getSwarm()[order[k]][l]));		
						}
						double v = sqrt(r);
					if (getIntensity(temp->getSwarm()[order[j]], v, dim, foo) >= getIntensity(temp->getSwarm()[order[k]], v, dim, foo)) {
						double beta0 = 0.2;
						double beta = 0.0;
						beta = ((beta0 - betamin)*exp(-gama*pow(v, 2)));
						for (int z = 0; z < dim; z++) { // equation 4
							r = getrandomdouble(0,1);
							double temp1 = alpha * (r - 0.5) *abs(max - min);
							tempFF[z] = temp->getSwarm()[order[j]][z] * beta * (temp->getSwarm()[order[j]][z] - temp->getSwarm()[order[k]][z]) + temp1;
						}
						fireflies->setSwarm(tempFF, order[k], dim);
					}
				}
			}	
	}
	setgBest(fireflies->getSwarm()[order[0]], dim);
	delete temp;
	delete[] tempFF;
	ofstream myfile;
	string filename = "FFresults.csv";
	myfile.open(filename, ios::app); // openfile
	if (myfile.is_open() == false) {
		cout << "Could not open file!" << endl;
	}
	else {
		myfile << foo(dim, fireflies->getSwarm()[order[0]]) << ",";
	}
	myfile.close();
	delete[] order;
	delete fireflies;
}
	bool operator<(const strs &a, const strs &b)
	{
		if ((a).value<(b).value)return true;
		else return false;
	}

