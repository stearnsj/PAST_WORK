#pragma once
class Population
{
public:
	Population();
	~Population();
	/**
	 *	initializer functions- initializes the various parts of the population
	 */
	void generatePopulation(int popSize, int dim, double min, double max);
	double* solveFitness(int dim, double**Population, int popSize, double min, double max, double(*foo)(int dim, double myArray[]));
	double* normalize(int dim, double**Population, int popSize, double min, double max, double(*foo)(int dim, double myArray[]));
	double* createArray(int dim, double min, double max);
	/**
	 *	Get Methods - gets values of private feilds
	 */
	double** getPopulation();
	double** getNewPopulation();
	double* getFitness();
	double* getBestValue();
	double* getCost();
	double* getProb();
	double getMin();
	double getMax();
	double getTotalFitness();
	double getBestFitness();
	double getMutationRate();
	double getMutationRange();
	double getCrossoverRate();
	double getMutPrec();
	double getEliteRate();
	double getScaleFactor();
	int getPopSize();
	int getDimensions();
	int getIterations();
	/**
	 *	Set Methods - sets values of private feilds
	 */
	void setNewPopulation(double**population);
	void setCrossoverRate(double crossRate);
	void setPopulation(double **population);
	void setMutationRange(double mutRange);
	void setTotalFitness(double TotalFit);
	void setMutPrec(double mutationPrec);
	void setDimensions(int dimensions1);
	void setbestFitness(double bestFit);
	void setMutaionRate(double mutRate);
	void setbestValue(double* bestVal);
	void setScaleFactor(double scale);
	void setCost(double* costtemp);
	void setPopSize(int popsize);
	void setEliteRate(double ER);
	void setIterations(int iter);
	void setMin(double minimum);
	void setMax(double maximum);
	void setFitness(double*fit);
	void setProb(double* Prob);

private:
	double totalfitness, crossoverRate, mutationRate, mutationRange, mutationPrec, eliteRate, min, max, totalFitness, bestfitness, scalefactor;
	int popSize, dimensions, iterations;
	double** globalPopulation;
	double** newPopulation;
	double* fitness;
	double* cost;
	double* bestValue;
	double* probabilties;

};

