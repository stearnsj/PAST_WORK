#include "stdafx.h"
#include "DiffAlgorithm.h"
#include "Population.h"
#include <fstream>
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <cmath>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;


DiffAlgorithm::DiffAlgorithm()
{
}


DiffAlgorithm::~DiffAlgorithm()
{
	delete[] parent1;
	delete[] parent2;
	delete[] child1;
	delete[] child2;
}

/**
* Reads from the input file to initialize and set the private feilds
* of the population class to the values for Differential Evolution Algorithm
*
*/
void DiffAlgorithm::fileReader()
{
	int dim, popSize, iter;
	double CR, MR, MRange, MPre, EliteRate, scale;
	ifstream myfile;
	myfile.open("config.txt", std::fstream::in);
	if (myfile.is_open()) {
		myfile >> dim >> popSize >> CR >> MR >> MRange >> MPre >> EliteRate >> iter >> scale;
		pop->setDimensions(dim);
		pop->setPopSize(popSize);
		pop->setCrossoverRate(CR);
		pop->setMutaionRate(MR);
		pop->setMutationRange(MRange);
		pop->setMutPrec(MPre);
		pop->setEliteRate(EliteRate);
		pop->setIterations(iter);
		pop->setScaleFactor(scale);
		myfile.close();
	}
	else {
		cout << "File could not be opened!" << endl;
	}
}

/**
* Confirms that the two selected parents are not the same parent
*
* @param  index  a  integer value representing working index
* @param  population  a  2D double array representing current population
* @param  foo  a pointer to the current fitness function
*/
void DiffAlgorithm::select(int index, double ** population, double(*foo)(int dim, double myArray[]))
{
	double val = foo(pop->getDimensions(), population[index]);
	double val2 = foo(pop->getDimensions(), getChild1());
	if (val2 < val) {
		population[index] = getChild1();
		pop->setPopulation(population);
	}
	
}

/**
* Mutates several genes based on different strategies for the algorithm
*
* @param  index  a  integer value representing working index
* @param  strategy  a  integer value representing current mutation strategy being ran
* @param  population  a  2D double array representing current population
* @param  min  a double representing the minimum of the range
* @param  max  a double representing the maximum of the range
* @param  foo  a pointer to the current fitness function
*/
void DiffAlgorithm::mutate(int index, int strategy, double ** population, double min, double max, double(*foo)(int dim, double myArray[]))
{
	int num = pop->getPopSize();
	int num2 = pop->getDimensions();
	random_device rd{};
	mt19937 engine{ rd() };
	uniform_int_distribution<int> dist{ 0, num-1 };
	uniform_int_distribution<int> dist1{ 0, num2-1 };
	int counter = 0;
	int r1, r2, r3, r4, r5 = 0;
	vector <int> randomnumbers;
	randomnumbers.push_back(index-1);
	getBestSolution(population, foo);
	while (randomnumbers.size() < 7) {
		int number = dist(engine);
		randomnumbers.push_back(number);
		vector<int>::iterator it;
		it = unique(randomnumbers.begin(), randomnumbers.end());
		randomnumbers.resize(distance(randomnumbers.begin(), it));
	}
	double * trialVector = new double[pop->getDimensions()];
	double * best = pop->getBestValue();
		r1 = randomnumbers.at(1);
		r2 = randomnumbers.at(2);
		r3 = randomnumbers.at(3);
		r4 = randomnumbers.at(4);
		r5 = randomnumbers.at(5);
	int j = dist1(engine);
	if (strategy == 1) {
		while (counter < pop->getDimensions()) {
			trialVector[j] = best[j] + pop->getScaleFactor() * (population[r2][j] - population[r3][j]);
			j++;
			if (j = pop->getDimensions()) {
				j = 0;
			}
			counter++;
		}
		setParent1(trialVector);
	}
	else if (strategy == 2) {
		while (counter < pop->getDimensions()) {
			trialVector[j] = population[r1][j] + pop->getScaleFactor() * (population[r2][j] - population[r3][j]);
			j++;
			if (j >= pop->getDimensions()) {
				j = 0;
			}
			counter++;
		}
		setParent1(trialVector);
	}
	else if (strategy == 3) {
		while (counter < pop->getDimensions()) {
			trialVector[j] = population[index][j] + (pop->getScaleFactor()/2) * (best[j] - population[index][j]) + pop->getScaleFactor() * (population[r1][j] - population[r2][j]);
			j++;
			if (j >= pop->getDimensions()) {
				j = 0;
			}
			counter++;
		}
		setParent1(trialVector);
	}
	else if (strategy == 4) {
		while (counter < pop->getDimensions()) {
			trialVector[j] = best[j] + pop->getScaleFactor() * (population[r1][j] + population[r2][j] - population[r3][j] - population[r4][j]);
			j++;
			if (j >= pop->getDimensions()) {
				j = 0;
			}
			counter++;
		}
		setParent1(trialVector);
	}
	else if (strategy == 5) {
		while (counter < pop->getDimensions()) {
			trialVector[j] = population[r5][j] + pop->getScaleFactor() * (population[r1][j] + population[r2][j] - population[r3][j] - population[r4][j]);
			j++;
			if (j >= pop->getDimensions()) {
				j = 0;
			}
			counter++;
		}
		setParent1(trialVector);
	}
	else if (strategy == 6) {
		while (counter < pop->getDimensions()) {
			trialVector[j] = best[j] + pop->getScaleFactor() * (population[r2][j] - population[r3][j]);
			j++;
			if (j >= pop->getDimensions()) {
				j = 0;
			}
			counter++;
		}
		setParent1(trialVector);
	}
	else if (strategy == 7) {
		while (counter < pop->getDimensions()) {
			trialVector[j] = population[r1][j] + pop->getScaleFactor() * (population[r2][j] - population[r3][j]);
			j++;
			if (j >= pop->getDimensions()) {
				j = 0;
			}
			counter++;
		}
		setParent1(trialVector);
	}
	else if (strategy == 8) {
		while (counter < pop->getDimensions()) {
			trialVector[j] = population[index][j] + (pop->getScaleFactor() / 2) * (best[j] - population[index][j]) + pop->getScaleFactor() * (population[r1][j] - population[r2][j]);
			j++;
			if (j >= pop->getDimensions()) {
				j = 0;
			}
			counter++;
		}
		setParent1(trialVector);
	}
	else if (strategy == 9) {
		while (counter < pop->getDimensions()) {
			trialVector[j] = best[j] + pop->getScaleFactor() * (population[r1][j] + population[r2][j] - population[r3][j] - population[r4][j]);
			j++;
			if (j >= pop->getDimensions()) {
				j = 0;
			}
			counter++;
		}
		setParent1(trialVector);
	}
	else if (strategy == 10) {
		while (counter < pop->getDimensions()) {
			trialVector[j] = population[r5][j] + pop->getScaleFactor() * (population[r1][j] + population[r2][j] - population[r3][j] - population[r4][j]);
			j++;
			if (j >= pop->getDimensions()) {
				j = 0;
			}
			counter++;
		}
		setParent1(trialVector);
	}
	double min2 = pop->getMin();
	double max2 = pop->getMax();
	for (int i = 0; i < pop->getDimensions(); i++) {
		while (trialVector[i] < pop->getMin() || trialVector[i] > pop->getMax()) {
			if (trialVector[i] < pop->getMin()) {
				if (pop->getMin() == 0) {
					min2 = max2;
					trialVector[i] = fmod(abs(trialVector[i]), min2);
				}
				else {
					trialVector[i] = fmod(trialVector[i], min2);
				}
			}
			else {
				trialVector[i] = fmod(trialVector[i], max2);
			}
		}
	}
	setParent1(trialVector);
	setParent2(population[index]);
	
}

/**
* Performs crossover between the parent and the noisy vector
*
* @param  index an integer value of the parents index in the population
* @param  CR  a  double representing the crossover rate
*/
void DiffAlgorithm::crossover(int index, double CR)
{
	int num = pop->getDimensions();
	random_device rd{};
	mt19937 engine{ rd() };
	uniform_real_distribution<double> dist{ 0, 1 };
	uniform_int_distribution<int> dist1{ 1, num };
	if (dist(engine) < CR) {
		int d = dist1(engine);
		double * child1 = new double[pop->getDimensions()];
		for (int i = 0; i <= d - 1; i++) {
			child1[i] = getParent1()[i];
		}
		for (int j = d; j < pop->getDimensions(); j++) {
			child1[j] = pop->getPopulation()[index][j];
		}
		setChild1(child1);
	}
	else {
		setChild1(parent1);
	}
	
}

/**
* Performs binomial crossover between the parent and the noisy vector
*
* @param  CR  a  double representing the crossover rate
*/
void DiffAlgorithm::bincrossover(double CR)
{
	double num = pop->getDimensions();
	random_device rd{};
	mt19937 engine{ rd() };
	double * parent1 = getParent1();
	double * parent2 = getParent2();
	uniform_real_distribution<double> dist{ 0, 1 };
	uniform_real_distribution<double> dist1{ 1, num };
	double * child1 = new double[pop->getDimensions()];
	for (int i = 0; i < pop->getDimensions(); i++) {
		if (dist(engine) < pop->getCrossoverRate()) {
			child1[i] = parent1[i];
		}
		else {
			child1[i] = parent2[i];
		}
	}
		setChild1(child1);
		
}

/**
* Calculates the best solution
*
* @param  population  a  2D double array representing current population
* @param  foo  a pointer to the current fitness function
*/
void DiffAlgorithm::getBestSolution(double ** population, double(*foo)(int dim, double myArray[]))
{
	double * fitness = pop->solveFitness(pop->getDimensions(), population, pop->getPopSize(), pop->getMin(), pop->getMax(), foo);
	int index = 0;

	for (int i = 0; i < pop->getPopSize(); i++)
	{
		if (fitness[i] < fitness[index])
			index = i;
	}
	if (fitness[index] < pop->getBestFitness()) {
		pop->setbestFitness(fitness[index]);
	}
	pop->setbestValue(population[index]);
	
}

/**
* Runs the instance of the Differential evolutionary algorithm
*
* @param  strategy  a  integer value representing current mutation strategy being ran
* @param  min  a double representing the minimum of the range
* @param  max  a double representing the maximum of the range
* @param  name  a  string representing name of the current fitness function
* @param  foo  a pointer to the current fitness function
*/
double DiffAlgorithm::runDiffAlgorithm(int strategy, double min, double max, std::string name, double(*foo)(int dim, double myArray[]))
{
	ofstream myfile;
	fileReader();
	string filename = name + "strategy"+ to_string(strategy) + "dim" + to_string(pop->getDimensions()) + "DiffAlgorithm.csv";
	pop->setbestFitness(DBL_MAX);
	pop->setMin(min);
	pop->setMax(max);
	if (name.compare("Shekels Foxhole") == 0) {
		pop->setDimensions(10);
	}
	myfile.open(filename, ios::app); // openfile
	if (myfile.is_open() == false) {
		cout << "Could not open file!" << endl;
	}
	else {
		pop->generatePopulation( pop->getPopSize(), pop->getDimensions(), min, max);
		double ** population = pop->getPopulation();
		int t = 1;
		while (t <= pop->getIterations()) {
			for (int s = 0; s < pop->getPopSize(); s++) {
				mutate(s, strategy, pop->getPopulation(), pop->getMin(), pop->getMax(), foo);
				if (strategy <= 5) {
					crossover(s, pop->getCrossoverRate());
				}
				else {
					bincrossover(pop->getCrossoverRate());
				}

				select(s, pop->getPopulation(), foo);
				population[s] = getChild1();
				pop->setPopulation(population);
			}
			t++;
		}
		double* fitness = pop->solveFitness(pop->getDimensions(), pop->getPopulation(), pop->getPopSize(), pop->getMin(), pop->getMax(), foo);
		double min1 = *min_element(fitness, fitness + pop->getPopSize());
		pop->setbestFitness(min1);
		myfile << pop->getBestFitness() << ",";
		return min1;
	}
	myfile.close();
	delete pop;
	
	return 0.0;
}

/**
* Sets the the first parent
*
* @param  parentone  an array of type double
*/
void DiffAlgorithm::setParent1(double * parentone)
{
	parent1 = parentone;
}

/**
* Sets the second parent
*
* @param  parenttwo  an array of type double
*/
void DiffAlgorithm::setParent2(double * parenttwo)
{
	parent2 = parenttwo;
}

/**
* Returns the first parent
*
* @return      the first parent
*/
double * DiffAlgorithm::getParent1()
{
	return parent1;
}

/**
* Returns the second parent
*
* @return      the second parent
*/
double * DiffAlgorithm::getParent2()
{
	return parent2;
}

/**
* Sets the first child
*
* @param  childone  an array of type double
*/
void DiffAlgorithm::setChild1(double * childone)
{
	child1 = childone;
}

/**
* Sets the second child
*
* @param  childtwo  an array of type double
*/
void DiffAlgorithm::setChild2(double * childtwo)
{
	child2 = childtwo;
}

/**
* Returns the first child
*
* @return      The first child
*/
double * DiffAlgorithm::getChild1()
{
	return child1;
}

/**
* Returns the second child
*
* @return      the second child
*/
double * DiffAlgorithm::getChild2()
{
	return child2;
}

bool myfunction(int i, int j) {
	return (i == j);
}
