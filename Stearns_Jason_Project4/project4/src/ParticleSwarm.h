#pragma once
class ParticleSwarm// merge existing code
{
public:
	ParticleSwarm();
	void PSOAlgorithm(double min, double max, double(*foo)(int dim, double myArray[]));
	void fileReader();
	int getrandomInt(int min, int max);
	double getrandomdouble(double min, double max);
	int numParticles, dim, iter;
	double c1, c2;
	double* pBest;
	double* gBest;
};

