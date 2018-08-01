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
	popSize = 0;
	dimensions = 0;
	fitness = nullptr;
	swarm = nullptr;
	velocity = nullptr;
	partBest = nullptr;
}

Population::~Population()
{
	for (int i = 0; i < popSize; i++) {
		delete[] swarm[i];
		delete[] velocity[i];
	}
	delete[] partBest;
	delete[] swarm;
	delete[] velocity;
	delete[] fitness;
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
Population::Population(int popsize, int dim, double min, double max)
{	
	popSize = popsize;
	dimensions = dim;
	fitness = new double[popSize];
	swarm = new double*[popSize];
	velocity = new double*[popSize];
	partBest = new double*[popSize];
	for (int i = 0; i < popSize; i++) {
		swarm[i] = new double[dimensions];
		velocity[i] = new double[dimensions];
		for (int j = 0; j < dim; j++) {
			swarm[i][j] = min + (getrandomdouble(0,1))*(max - min);
			velocity[i][j] = getrandomdouble(0, 0.5 * (max - min));
		}
		partBest[i] = swarm[i];
	}
}
/**
* Creates a copy of a population
*
* @param  pop  a Population to be copied
* 
*/
Population::Population(const Population & pop)
{
	dimensions = pop.dimensions;
	popSize = pop.popSize;
	fitness = new double[popSize];
	swarm = new double*[popSize];
	velocity = new double*[popSize];
	for (int i = 0; i < popSize; i++) {     // generate copy by creating new array and copying values to new array from original array
		swarm[i] = new double[dimensions];
		velocity[i] = new double[dimensions];
		fitness[i] = pop.fitness[i];
	}
	for (int n = 0; n<popSize; n++) {
		for (int j = 0; j<dimensions; j++) {
			swarm[n][j] = pop.swarm[n][j];
			velocity[n][j] = pop.velocity[n][j];
		}
	}
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
void Population::solveFitness(int dim, int popSize, double min, double max, double(*foo)(int dim, double myArray[]))
{
	double* myArray2 = new double[popSize];
	for (int i = 0; i < popSize; i++) {
		myArray2[i] = foo(dim, swarm[i]);
	}
	setFitness(myArray2, popSize);
	delete[] myArray2;
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
* Sets the fitness array
*
* @param  fit  an array of type double
*/
void Population::setFitness(double fit[], int size)
{
	for (int i = 0; i < size; i++) {
		fitness[i] = fit[i];
	}
	
}

/**
* Returns the swarm martix
*
* @return      A Matrix containing the current swarm
*/
double ** Population::getSwarm()
{
	return this->swarm;
}

/**
* Sets a specific particle in the swarm
*
* @param  particle  an array containing a particle
* @param  index  an int representing the index of the swarm to be replaced with the new particle
* @param  dim  the number of dimensions
*/
void Population::setSwarm(double particle[], int index, int dim)
{
	for (int i = 0; i < dim; i++) {
		swarm[index][i] = particle[i];
	}
	
}

/**
* Returns the velocity of a given particle
*
* @param  dim  the number of dimensions
*
* @return      an array containing the particles' velocity( at a given index)
*/
double * Population::getVelocity(int index)
{
	return this->velocity[index];
}

/**
* Sets the velocity of a particle in the swarm
*
* @param  vel  an array containing velocity
* @param  index  an int representing the index of the corisponding paticle
* @param  dim  the number of dimensions
*/
void Population::setVelocity(double vel[], int index, int dim)
{
	for (int i = 0; i < dim; i++) {
		velocity[index][i] = vel[i];
	}
}

/**
* Returns the particles best value
*
* @param  index  the index of the particle
*
* @return      an array containing the particles' best value
*/
double * Population::getpBest(int index)
{
	return this->partBest[index];
}

/**
* Sets the best value of a particle in the swarm
*
* @param  pbest  an array containing the new best value
* @param  index  an int representing the index of the corisponding paticle
* @param  dim  the number of dimensions
*/
void Population::setpBest(double pbest[], int index, int dim)
{
	for (int i = 0; i < dim; i++) {
		partBest[index][i] = pbest[i];
	}
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
* returns a randomly generated integer
*
* @param  min  the minimum value to be returned
* @param  max  the maximum value to be returned
*
* @return      A random integer between min and max
*/
int Population::getrandomInt(int min, int max)
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
double Population::getrandomdouble(double min, double max)
{
	static random_device rd{};
	static mt19937 engine{ rd() };
	uniform_real_distribution<double> dist{ min, max };
	return dist(engine);
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
