#pragma once
#include <string>
#include "Population.h"
class DiffAlgorithm
{
public:
	Population *pop = new Population();
	DiffAlgorithm();
	~DiffAlgorithm();
	double runDiffAlgorithm(int strategy, double min, double max, std::string name, double(*foo)(int dim, double myArray[]));
	void fileReader();
	void select(int index, double ** population, double(*foo)(int dim, double myArray[]));
	void mutate(int index, int strategy, double ** population, double min, double max, double(*foo)(int dim, double myArray[]));
	void crossover(int index, double CR);
	void bincrossover(double CR);
	void getBestSolution(double ** population, double(*foo)(int dim, double myArray[]));
	void setParent1(double * parentone);
	void setParent2(double * parenttwo);
	double * getParent1();
	double * getParent2();
	void setChild1(double * childone);
	void setChild2(double * childtwo);
	double * getChild1();
	double * getChild2();
private:
	double * parent1;
	double * parent2;
	double * child1;
	double * child2;
};

