#pragma once
class Population
{
public:
	Population();
	~Population();
	Population(int popSize, int dim, double min, double max);
	Population(const Population &pop);
	void solveFitness(int dim, int popSize, double min, double max, double(*foo)(int dim, double myArray[]));
	double* getFitness();
	int getrandomInt(int min, int max);
	double getrandomdouble(double min, double max);
	double getMin();
	double getMax();
	int getPopSize();
	int getDimensions();
	int getIterations();
	void setDimensions(int dimensions1);
	void setPopSize(int popsize);
	void setIterations(int iter);
	void setMin(double minimum);
	void setMax(double maximum);
	void setFitness(double fit[], int size);
	double** getSwarm();
	void setSwarm(double particle[], int index, int dim);
	double* getVelocity(int index);
	void setVelocity(double vel[], int index, int dim);
	double* getpBest(int index);
	void setpBest(double pbest[], int index, int dim);
private:
	double min, max;
	int popSize, dimensions, iterations;
	double* fitness;
	double** swarm;
	double** velocity;
	double** partBest;
};

