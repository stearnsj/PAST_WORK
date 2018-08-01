#pragma once
#include <cstdlib>
#include <string.h>
#include <vector>
#include <string>
#pragma once
using namespace std;

typedef struct benchmarkfunctions { 
    string name; 
    double min; 
    double max; 
    double(*foo)(int dim, double myArray[]);
} benchmarkfunctions;
static benchmarkfunctions benchmarkfunctions1[15];
benchmarkfunctions instantiateStruct(string name, double min, double max, double(*foo)(int dim, double myArray[]), benchmarkfunctions bmf);
benchmarkfunctions * createFunctionStruct();


