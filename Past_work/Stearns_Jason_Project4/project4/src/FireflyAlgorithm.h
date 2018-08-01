#pragma once
#include "Population.h"
class FireflyAlgorithm
{
public:
	FireflyAlgorithm();
	void fireFlyAlgorithm(double min, double max, double(*foo)(int dim, double myArray[]));
	void fileReader();
	double* getgBest();
	void setgBest(double globalBest[], int dim);
	int * sortbyFitness(Population &population, double(*foo)(int dim, double myArray[]));
	int getrandomInt(int min, int max);
	double getrandomdouble(double min, double max);
	double getIntensity(double firefly[], double v, int dim, double(*foo)(int dim, double myArray[]));
	int dim, numParticles, iter;
	double gama, alpha, betamin;
private:
	double* gBest;
};
typedef struct
{
	double value; int index;
}strs;

