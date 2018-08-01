#pragma once
#include <vector>
#include <string>
#include "Population.h"
class GeneticAlgorithm
{
public:
	Population *pop = new Population();
	GeneticAlgorithm();
	~GeneticAlgorithm();
	double runGeneticAlgorithm(double min, double max, std::string name, double(*foo)(int dim, double myArray[]));
	void reduce(double** population, double ** newpopulation, double EliteSN, double(*foo)(int dim, double myArray[]));
	void select(double ** population, double(*foo)(int dim, double myArray[]));
	void mutate(double * child1, double * child2);
	void crossover(double* parent1, double* parent2, double CR);
	void fileReader();
	int * sortbyCost(double ** population, double(*foo)(int dim, double myArray[]));
	int selectParent(double ** population, double(*foo)(int dim, double myArray[]));
	void getFitness(double ** population, double(*foo)(int dim, double myArray[]));
	void getBestSolution(double**population, double(*foo)(int dim, double myArray[]));
 //Get Methods - Gets Values of Private Feilds
	double * getParent1();
	double * getParent2();
	double * getChild1();
	double * getChild2();
//	Set Methods - Sets Values of Private Feilds
	void setParent1(double parentone[]);
	void setParent2(double parenttwo[]);
	void setChild1(double childone[]);
	void setChild2(double childtwo[]);
private:
	double * parent1;
	double * parent2;
	double * child1;
	double * child2;
};
typedef struct
	{
		double value; int index;
	}strs;
int cmp(const void *a, const void *b);

