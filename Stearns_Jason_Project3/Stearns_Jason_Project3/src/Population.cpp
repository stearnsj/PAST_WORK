#include "stdafx.h"
#include "Population.h"
#include <random>
#define _USE_MATH_DEFINES
#include <cmath>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <string>
#include <algorithm>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;

Population::Population()
{
	
}


Population::~Population()
{


}

/**
* Returns a Array of type double containing dim random values randomly generated between
* min and max by the createArray function.
*
* @param  dim  an integer representing the number of dimensions
* @param  min  a double representing the minimum of the range
* @param  max  a double representing the maximum of the range
* @return      an array of dim doubles between min and max
*/
double * Population::createArray(int dim, double min, double max)
{
	random_device rd{};
	mt19937 engine{ rd() };
	uniform_real_distribution<double> dist{ min, max };
	double * myArray = new double[dim];
	for (int i = 0; i < dim; i++) {
		myArray[i] = (dist(engine));
	}
	
	return myArray;
	
}
/**
* Returns a two dimensional array of type double containing popsize arrays of
* dim elements, between the range of min to max.
*
* @param  popSize  an integer representing the size of the population
* @param  dim  an integer representing the number of dimensions
* @param  min  a double representing the minimum of the range
* @param  max  a double representing the maximum of the range
* @return      an 2D array of doubles of size dim by popSize representing a new population
*/
void Population::generatePopulation(int popSize, int dim, double min, double max)
{
	double ** myArray = new double*[popSize];
	for (int i = 0; i < popSize; i++) {
		myArray[i] = createArray(dim, min, max);
	}
	setPopulation(myArray);
}


/**
* Returns a array of type double containing the normalized values of
*  the fitnesses of each chromosome in the population.
*
* @param  dim  an integer representing the number of dimensions
* @param  population 2D array of type double containing the current population
* @param  popSize  an integer representing the size of the population
* @param  min  a double representing the minimum of the range
* @param  max  a double representing the maximum of the range
* @param  foo  a pointer to the current fitness function
* @return      an array of type double containing normalized fitness values
*/
double * Population::normalize(int dim, double ** population,  int popSize, double min, double max, double(*foo)(int dim, double myArray[])) // normalize only the fitness
{
	double minimum;
	double maximum;
	double ** myArray = population;
	double* myArray2 = solveFitness(dim, population, popSize, min, max, foo);
	minimum = *min_element(myArray2, myArray2 + getPopSize());
	maximum = *max_element(myArray2, myArray2 + getPopSize());
	double total = 0;
	double totalfitness = 0;
	for (int i = 0; i < getPopSize(); i++) {
		totalfitness += maximum - myArray2[i];
	}
	setTotalFitness(totalfitness);
	for (int j = 0; j < getPopSize(); j++) {
		myArray2[j] = (total + (maximum - myArray2[j]) / (totalfitness));
		total = myArray2[j];
	}
	setProb(myArray2);
	return myArray2;
}

/**
* Returns a array of type double containing dim elements representing
* the fitnesses of each member of the population.
*
* @param  dim  an integer representing the number of dimensions
* @param  population  an 2D double array containing the current population
* @param  popSize  an integer representing the size of the population
* @param  min  a double representing the minimum of the range
* @param  max  a double representing the maximum of the range
* @param  foo  a pointer to the current fitness function
* @return      an 2D array of doubles of size dim by popSize representing a new population
*/
double * Population::solveFitness(int dim, double ** Population, int popSize, double min, double max, double(*foo)(int dim, double myArray[]))
{
	double ** myArray = Population;
	double* myArray2 = new double[getPopSize()];
	for (int i = 0; i < getPopSize(); i++) {
		myArray2[i] = foo(dim, myArray[i]);
	}
	
	return myArray2;
}

/**
* Returns the Population Size
*
* @return      The current population size
*/
int Population::getPopSize()
{
	return popSize;
}

/**
* Sets the Population Size
*
* @param  popsize  a value of type integer
*/
void Population::setPopSize(int popsize)
{
	popSize = popsize;
}

/**
* Returns the number of dimensions
*
* @return     The current number of dimensions
*/
int Population::getDimensions()
{
	return dimensions;
}

/**
* Sets the number of dimensions
*
* @param  dimensions1  a value of type integer
*/
void Population::setDimensions(int dimensions1)
{
	dimensions = dimensions1;
}

/**
* Returns the Mutation Rate
*
* @return      The current Mutation Rate
*/
double Population::getMutationRate()
{
	return mutationRate;
}

/**
* Sets the Mutation Rate
*
* @param  mutRate  a value of type double
*/
void Population::setMutaionRate(double mutRate)
{
	mutationRate = mutRate;
}

/**
* Returns the Mutation Range
*
* @return      The current Mutation Range
*/
double Population::getMutationRange()
{
	return mutationRange;
}

/**
* Sets the Mutation Range
*
* @param  mutRange  a value of type double
*/
void Population::setMutationRange(double mutRange)
{
	mutationRange = mutRange;
}

/**
* Returns the Crossover Rate
*
* @return      The current CrossoverRate
*/
double Population::getCrossoverRate()
{
	return crossoverRate;
}

/**
* Sets the Crossover Rate
*
* @param  crossRate  a value of type double
*/
void Population::setCrossoverRate(double crossRate)
{
	crossoverRate = crossRate;
}

/**
* Returns the Mutation Precision
*
* @return      The current Mutation Precision
*/
double Population::getMutPrec()
{
	return mutationPrec;
}

/**
* Sets the Mutation Precision
*
* @param  mutationPrec1  a value of type double
*/
void Population::setMutPrec(double mutationPrec1)
{
	mutationPrec = mutationPrec1;
}

/**
* Returns the Elitism Rate
*
* @return      The current Elitism Rate
*/
double Population::getEliteRate()
{
	return eliteRate;
}

/**
* Sets the Elitism Rate
*
* @param  ER  a value of type double
*/
void Population::setEliteRate(double ER)
{
	eliteRate = ER;
}

/**
* Returns the Scaleing Factor
*
* @return      The current Scaleing Factor
*/
double Population::getScaleFactor()
{
	return scalefactor;
}

/**
* Sets the Scaleing Factor
*
* @param  scale  a value of type double
*/
void Population::setScaleFactor(double scale)
{
	scalefactor = scale;
}

/**
* Sets the Probability of each member of the population
*
* @param  Prob  an array of type double
*/
void Population::setProb(double* Prob)
{
	probabilties = Prob;
}

/**
* Returns the Probability array
*
* @return      The current Probability array
*/
double * Population::getProb()
{
	return probabilties;
}


/**
* Returns the number of iterations
*
* @return      The current number of iterations
*/
int Population::getIterations()
{
	return iterations;
}

/**
* Sets the number of iterations
*
* @param  iter  a value of type integer
*/
void Population::setIterations(int iter)
{
	iterations = iter;
}

/**
* Sets the Population
*
* @param  population  a 2D array of type double
*/
void Population::setPopulation(double ** population)
{
	globalPopulation = population;
}

/**
* Returns the Population
*
* @return      The current population
*/
double ** Population::getPopulation()
{
	return globalPopulation;
}

/**
* Sets the New Population
*
* @param  population  a 2D array of type double
*/
void Population::setNewPopulation(double ** population)
{
	newPopulation = population;
}

/**
* Returns the new population
*
* @return      The new population
*/
double ** Population::getNewPopulation()
{
	return newPopulation;
}

/**
* Sets the fitness array
*
* @param  fit  an array of type double
*/
void Population::setFitness(double * fit)
{
	fitness = fit;
}

/**
* Returns the fitness array
*
* @return      The current fitness array
*/
double * Population::getFitness()
{
	return fitness;
}

/**
* Sets the best fitness
*
* @param  bestFit  a value of type double
*/
void Population::setbestFitness(double bestFit)
{
	bestfitness = bestFit;
}

/**
* Returns the best fitness
*
* @return      The current best fitness
*/
double Population::getBestFitness()
{
	return bestfitness;
}

/**
* Sets the Best Value
*
* @param  bestVal  an array of type double
*/
void Population::setbestValue(double * bestVal)
{
	bestValue = bestVal;
}

/**
* Returns the Best Value
*
* @return      The current best value
*/
double * Population::getBestValue()
{
	return bestValue;
}

/**
* Sets the Cost Array
*
* @param  costtemp  an array of type double
*/
void Population::setCost(double * costtemp)
{
	cost = costtemp;
}

/**
* Returns the cost array
*
* @return      The current cost array
*/
double * Population::getCost()
{
	return cost;
}

/**
* Sets the minimum of the current fitness function
*
* @param  minimum  a value of type double
*/
void Population::setMin(double minimum)
{
	min = minimum;
}

/**
* Returns the minimum
*
* @return      The current minimum
*/
double Population::getMin()
{
	return min;
}

/**
* Sets the maximum of the current fitness function
*
* @param  maximum  a value of type double
*/
void Population::setMax(double maximum)
{
	max = maximum;
}

/**
* Returns the maximum
*
* @return      The current maximum
*/
double Population::getMax()
{
	return max;
}

/**
* Sets the total fitness
*
* @param  TotalFit  a value of type double
*/
void Population::setTotalFitness(double TotalFit)
{
	totalFitness = TotalFit;
}

/**
* Returns the total fitness
*
* @return      The current total fitness
*/
double Population::getTotalFitness()
{
	return totalFitness;
}
