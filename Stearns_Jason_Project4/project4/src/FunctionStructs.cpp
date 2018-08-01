#include "FunctionStructs.h"
#include <string.h>
#include <vector>
#include <string>
#include <cmath>
#include <vector>
#include "Functions.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

/**
* Instantiates the benchmarkfunctions struct
*
* @param  name  a name of type string
* @param  min  a value of type double representing the functions minimum
* @param  max  a value of type double representing the functions maximum
* @param  foo  a pointer to a fitness function
* @param  bmf  a benchmarkfunction object
* @return      a benchmark function object
*/
benchmarkfunctions instantiateStruct(string name, double min, double max, double(*foo)(int dim, double myArray[]), benchmarkfunctions bmf)
{
	bmf.name = name;
	bmf.min = min;
	bmf.max = max;
	bmf.foo = foo;
	return bmf;
}

/**
* sets the values of a struct array equal to the values of the 15 fitness functions
*
* @return      a pointer to a benchmarkfunctions object
*/
benchmarkfunctions * createFunctionStruct()
{
    
    benchmarkfunctions1[0] = instantiateStruct("Schwfel", -512, 512, schwefelFun, benchmarkfunctions1[0]); // set struct values
    benchmarkfunctions1[1] = instantiateStruct("1st De Jong", -100, 100, istDeJongFun, benchmarkfunctions1[1]);
    benchmarkfunctions1[2] = instantiateStruct("Rosenbrock", -100, 100, rosenbrockFun, benchmarkfunctions1[2]);
    benchmarkfunctions1[3] = instantiateStruct("Rastrigin", -30, 30, rastriginFun, benchmarkfunctions1[3]);
    benchmarkfunctions1[4] = instantiateStruct("Grienwangk", -500, 500, griewangk, benchmarkfunctions1[4]);
    benchmarkfunctions1[5] = instantiateStruct("Sine Envelope Sine Wave", -30, 30, sineEnvelopeSinceWaveFun, benchmarkfunctions1[5]);
    benchmarkfunctions1[6] = instantiateStruct("Stretch V Sine Wave", -30, 30, stretchedVSineWaveFun, benchmarkfunctions1[6]);
    benchmarkfunctions1[7] = instantiateStruct("Ackley One", -32, 32, ackleysOneFun, benchmarkfunctions1[7]);
    benchmarkfunctions1[8] = instantiateStruct("Ackley Two", -32, 32, ackleysTwoFun, benchmarkfunctions1[8]);
    benchmarkfunctions1[9] = instantiateStruct("Egg Holder", -500, 500, eggHolderFun, benchmarkfunctions1[9]);
    benchmarkfunctions1[10] = instantiateStruct("Rana", -500, 500, ranaFun, benchmarkfunctions1[10]);
    benchmarkfunctions1[11] = instantiateStruct("Pathological", -100, 100, pathologicalFun, benchmarkfunctions1[11]);
    benchmarkfunctions1[12] = instantiateStruct("Michalewicz", 0, _Pi, michaleqiczFun, benchmarkfunctions1[12]);
    benchmarkfunctions1[13] = instantiateStruct("Masters Cosine Wave", -30, 30, mastersCosineWaveFun, benchmarkfunctions1[13]);
	benchmarkfunctions1[14] = instantiateStruct("Shekels Foxhole", 0, 10, shekelsFoxholesFun, benchmarkfunctions1[14]);

    return benchmarkfunctions1;
}
