#include "stdafx.h"
#include "GeneticAlgorithm.h"
#include "Population.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <random>
#include <cmath>
#include <algorithm>
#include <functional>
#include <array>
#include <string>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;


GeneticAlgorithm::GeneticAlgorithm()
{

}


GeneticAlgorithm::~GeneticAlgorithm()
{
}

/**
* Reads from the input file to initialize and set the private feilds
* of the population class to the values for Genetic Algorithm
*
*/
void GeneticAlgorithm::fileReader()
{
	int dim, popSize, iter;
	double CR, MR, MRange, MPre, EliteRate;
	ifstream myfile;
	myfile.open("config.txt", std::fstream::in);
	if (myfile.is_open()) {
		myfile >> dim >> popSize >> CR >> MR >> MRange >> MPre >> EliteRate >> iter;
		pop->setDimensions(dim);
		pop->setPopSize(popSize);
		pop->setCrossoverRate(CR);
		pop->setMutaionRate(MR);
		pop->setMutationRange(MRange);
		pop->setMutPrec(MPre);
		pop->setEliteRate(EliteRate);
		pop->setIterations(iter);
		myfile.close();
	}
	else {
		cout << "File could not be opened!" << endl;
	}
}

/**
* Calculates the fitness aray for a given population
*
* @param  population  a  2D double array representing current population
* @param  foo  a pointer to the current fitness function
* @return      an array containing the fitess of each member of the population
*/
void GeneticAlgorithm::getFitness(double ** population, double(*foo)(int dim, double myArray[]))
{
	double* costs = pop->normalize(pop->getDimensions(), population, pop->getPopSize(), pop->getMin(), pop->getMax(), foo);
	double * fitness = new double[pop->getPopSize()];
	for (int s = 0; s < pop->getPopSize(); s++) {
		if (costs[s] >= 0) {
			fitness[s] = 1 / (1 + costs[s]);
		}
		else {
			fitness[s] = 1 + abs(costs[s]);
		}
	}
	double totalfitness = 0;
	for (int i = 0; i < pop->getPopSize(); i++) {
		totalfitness += fitness[i];
	}
	pop->setTotalFitness(totalfitness);
	pop->setFitness(fitness);
}

/**
* Selects the two parrents for crossover
*
* @param  population  a  2D double array representing current population
* @param  foo  a pointer to the current fitness function
* @return      an integer corisponding to the index of the parent
*/
int GeneticAlgorithm::selectParent(double ** population, double(*foo)(int dim, double myArray[]))
{
	double num = pop->getTotalFitness();
	random_device rd{};
	mt19937 engine{ rd() };
	uniform_real_distribution<double> dist{ 0, 1 };
	double r = (dist(engine));
	double * probs = pop->getProb();
	for (int i = 1; i < pop->getPopSize(); i++) {
		if (probs[i] > r) {
			return i - 1;
		}
	}
	return pop->getPopSize() - 1;
}

/**
* Confirms that the two selected parents are not the same parent
*
* @param  population  a  2D double array representing current population
* @param  foo  a pointer to the current fitness function
*/
void GeneticAlgorithm::select(double ** population, double(*foo)(int dim, double myArray[]))
{
	int val = selectParent(population, foo);
	int val2 = selectParent(population, foo);
	while (val == val2) {
		val2 = selectParent(population, foo);
	}
	setParent1(population[val]);
	setParent2(population[val2]);
}

/**
* performes crossover for the two parents resulting in two children
*
* @param  parent1  a  double array representing the first parent
* @param  parent2  a  double array representing the second parent
* @param  CR  a  double representing the crossover rate
*/
void GeneticAlgorithm::crossover(double * parent1, double * parent2, double CR)
{
	int num = pop->getDimensions();
	random_device rd{};
	mt19937 engine{ rd() };
	random_device rt{};
	mt19937 engine1{ rt() };
	parent1 = getParent1();
	parent2 = getParent2();
	uniform_real_distribution<double> dist{ 0, 1 };
	uniform_int_distribution<int> dist1{ 1, num };
	if (dist(engine) < CR) {
		int d = dist1(engine);
		double * child1 = new double[pop->getDimensions()];
		double * child2 = new double[pop->getDimensions()];
		for (int i = 0; i <= d - 1; i++) {
			child1[i] = parent1[i];
			child2[i] = parent2[i];
		}
		for (int j = d; j < pop->getDimensions(); j++) {
			child1[j] = parent2[j];
			child2[j] = parent1[j];
		}
		setChild1(child1);
		setChild2(child2);
	}
	else {
		setChild1(parent1);
		setChild2(parent2);
	}
}

/**
* Mutates several genes of each child
*
* @param  child1  a  double array representing the first child
* @param  child2  a  double array representing the second child
*/
void GeneticAlgorithm::mutate(double * child1, double* child2)
{
	int num = pop->getDimensions();
	random_device rd{};
	mt19937 engine{ rd() };
	uniform_real_distribution<double> dist{ 0, 1 };
	uniform_real_distribution<double> dist1{ -1, 1 };
	for (int i = 0; i < pop->getDimensions(); i++) {
		if (dist(engine) < pop->getMutationRate()) {
			child1[i] += dist(engine) * (pop->getMax() - pop->getMin()) * pop->getMutationRange() * pow((-1 * dist(engine)* pop->getMutPrec()), 2);
		}
	}
	for (int i = 0; i < pop->getDimensions(); i++) {
		if (dist(engine) < pop->getMutationRate()) {
			child2[i] += dist(engine) * (pop->getMax() - pop->getMin()) * pop->getMutationRange() * pow((-1 * dist(engine)* pop->getMutPrec()), 2);
		}
	}
	setChild1(child1);
	setChild2(child2);
}

/**
* Combines and reduces the old population with the new one.
*
* @param  population  a  2D double array representing current population
* @param  foo  a pointer to the current fitness function
* @return      an array containing the sorted indicies
*/
int * GeneticAlgorithm::sortbyCost(double**population, double(*foo)(int dim, double myArray[]))
{
	int popsize = pop->getPopSize();
	int * order = new int[pop->getPopSize()];
	double ** curpopulation = population;
	double * cost = new double[pop->getPopSize()];
	for (int j = 0; j < pop->getPopSize(); j++) {
		cost[j] = foo(pop->getDimensions(), population[j]);
	}
	strs *objects = (strs *)malloc(popsize * sizeof *objects);
	for (int i = 0; i < pop->getPopSize(); i++)
	{
		objects[i].value = cost[i];
		objects[i].index = i;
	}
	std::sort(objects, objects + pop->getPopSize(), std::less<strs>());
	for (int j = 0; j < pop->getPopSize(); j++) {
		order[j] = objects[j].index;

	}
	return order;
}

/**
* Combines and reduces the old population with the new one.
*
* @param  population  a  2D double array representing old population
* @param  newpopulation  a  2D double array representing new population after mutation and crossover
* @param  EliteSN  a double that represents the number of offspring to move to the next generation
* @param  foo  a pointer to the current fitness function
*/
void GeneticAlgorithm::reduce(double ** population, double ** newpopulation, double EliteSN, double(*foo)(int dim, double myArray[]))
{
	int * orderOld = sortbyCost(population, foo);
	int * orderNew = sortbyCost(newpopulation, foo);


	double ** newpopulation1 = pop->getNewPopulation();
	for (int s = 0; s < EliteSN; s++) {
		newpopulation1[s] = newpopulation[orderNew[s]];
	}
	pop->setPopulation(newpopulation1);
}

/**
* Calculates and sets the fittest member of the population
*
* @param  population  a  2D double array representing current population
* @param  foo  a pointer to the current fitness function
*/
void GeneticAlgorithm::getBestSolution(double ** population, double(*foo)(int dim, double myArray[]))
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

bool operator<(const strs &a, const strs &b)
{
	if ((a).value<(b).value)return true;
	else return false;
}

/**
* Runs the instance of the Genetic Algorithm class
*
* @param  min  a double representing the minimum of the range
* @param  max  a double representing the maximum of the range
* @param  name  a string value representing the name of the fitness function being ran

* @param  foo  a pointer to the current fitness function
* @return      the best fitness found
*/
double GeneticAlgorithm::runGeneticAlgorithm(double min, double max, string name, double(*foo)(int dim, double myArray[]))
{
	string filename  = name + to_string(pop->getDimensions()) + "GeneticAlgorithm.csv";
	ofstream myfile;
	fileReader();
	pop->setbestFitness(DBL_MAX);
	

	double eliteSN = pop->getEliteRate() * pop->getPopSize();
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
		getFitness(pop->getPopulation(), foo);
		pop->normalize(pop->getDimensions(), pop->getPopulation(), pop->getPopSize(), min, max, foo);
		int t = 1;
		while (t <= pop->getIterations()) {
			pop->setNewPopulation(pop->getPopulation());
			double ** newpopulation = pop->getNewPopulation();
			for (int s = 1; s <= pop->getPopSize(); s += 2) {
				select(pop->getPopulation(), foo);
				crossover(getParent1(), getParent2(), pop->getCrossoverRate());
				mutate(getChild1(), getChild2());
				newpopulation[s - 1] = getChild1();
				newpopulation[s] = getChild2();
			}
			pop->setNewPopulation(newpopulation);
			double * newPopulationCost = pop->normalize(pop->getDimensions(), newpopulation, pop->getPopSize(), min, max, foo);
			reduce(pop->getPopulation(), newpopulation, eliteSN, foo);
			getFitness(pop->getPopulation(), foo);
			getBestSolution(pop->getPopulation(), foo);
			t++;
		}
		myfile << pop->getBestFitness() << ",";
	}
	myfile.close();
	return 0.0;
}

/**
* Sets the the first parent
*
* @param  parentone  an array of type double
*/
void GeneticAlgorithm::setParent1(double * parentone)
{
	parent1 = parentone;
}

/**
* Sets the second parent
*
* @param  parenttwo  an array of type double
*/
void GeneticAlgorithm::setParent2(double * parenttwo)
{
	parent2 = parenttwo;
}

/**
* Returns the first parent
*
* @return      the first parent
*/
double * GeneticAlgorithm::getParent1()
{
	return parent1;
}

/**
* Returns the second parent
*
* @return      the second parent
*/
double * GeneticAlgorithm::getParent2()
{
	return parent2;
}

/**
* Sets the first child
*
* @param  childone  an array of type double
*/
void GeneticAlgorithm::setChild1(double * childone)
{
	child1 = childone;
}

/**
* Sets the second child
*
* @param  childtwo  an array of type double
*/
void GeneticAlgorithm::setChild2(double * childtwo)
{
	child2 = childtwo;
}

/**
* Returns the first child
*
* @return      The first child
*/
double * GeneticAlgorithm::getChild1()
{
	return child1;
}

/**
* Returns the second child
*
* @return      the second child
*/
double * GeneticAlgorithm::getChild2()
{
	return child2;
}


