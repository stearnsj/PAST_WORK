#define _USE_MATH_DEFINES
#include <cmath>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <vector>
#include <random>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;

/**
* Runs schwefel fitness function and calculates its value
*
* @param  dim  an integer epresenting the number of dimensions
* @param  myArray  an array of type double
* @return      the fitness of the array
*/

double schwefelFun(int dim, double myArray[]) {
    int i;
    double f = 0.0;
        for (i = 0; i < dim; i ++) {
            f += -(myArray[i]) * sin(pow(abs(myArray[i]), 0.5));
        }

    return f;
}

/**
* Runs 1st De Jong fitness function and calculates its value
*
* @param  dim  an integer epresenting the number of dimensions
* @param  myArray  an array of type double
* @return      the fitness of the array
*/
double istDeJongFun(int dim, double myArray[]) {
    double f = 0.0;
    int i;
        for (i = 0; i < dim; i ++) {
            f += pow(myArray[i], 2);
        }
    return f;
}

/**
* Runs Rosenbrock fitness function and calculates its value
*
* @param  dim  an integer epresenting the number of dimensions
* @param  myArray  an array of type double
* @return      the fitness of the array
*/
double rosenbrockFun(int dim, double myArray[]) {
    double f;
    int i;
        f = 0.0;
        for (i = 0; i < dim - 1; i ++) {
            f += 100 * pow((myArray[i+1] - (pow(myArray[i], 2.0))), 2.0) + (pow((1 - myArray[i]), 2.0));
        }
    return f;
}

/**
* Runs Rastrigin fitness function and calculates its value
*
* @param  dim  an integer epresenting the number of dimensions
* @param  myArray  an array of type double
* @return      the fitness of the array
*/
double rastriginFun(int dim, double myArray[]) {
    double f = 0.0;
    int i;

        for (i = 0; i < dim; i ++) {
            f += ((2 * dim) * (pow(myArray[i], 2.0) - (10 * cos((2 * _Pi) * myArray[i]))));
    }
    return f;
}

/**
* Runs Griewangk fitness function and calculates its value
*
* @param  dim  an integer epresenting the number of dimensions
* @param  myArray  an array of type double
* @return      the fitness of the array
*/
double griewangk(int dim, double myArray[]) {
    
    double l = 0.0;
    double k = 1.0;
    int i;
        for (i = 0; i < dim; i ++) {
            l += (pow(myArray[i], 2.0) / 4000.0);
            k *= (cos(myArray[i] / pow(i + 1, 0.5)));
        }
        double f = 1.0;
        f += (l - k);
    return f;
}

/**
* Runs Sine Envelope SineWave fitness function and calculates its value
*
* @param  dim  an integer epresenting the number of dimensions
* @param  myArray  an array of type double
* @return      the fitness of the array
*/
double sineEnvelopeSinceWaveFun(int dim, double myArray[]) {
    double f = 0.0;
    int i;
        for (i = 0; i < dim - 1; i ++) {
            f += ((-1) * ((0.5) + (pow(sin(pow(myArray[i], 2.0) + pow(myArray[i+1], 2.0) - 0.5), 2.0) / (pow(1 + 0.001 * (pow(myArray[i], 2.0) 
                + pow(myArray[i+1], 2.0)), 2.0)))));
        }
    return f;
}

/**
* Runs Stretched V Sine Wave fitness function and calculates its value
*
* @param  dim  an integer epresenting the number of dimensions
* @param  myArray  an array of type double
* @return      the fitness of the array
*/
double stretchedVSineWaveFun(int dim, double myArray[]) {
    double f = 0.0;
    int i;
        for (i = 0; i < dim - 1; i ++) {
            f += (pow((pow(myArray[i], 2.0) + pow(myArray[i+1], 2.0)), 0.25) * (pow(sin((50) * (pow(pow(myArray[i], 2.0) 
                + pow(myArray[i+1], 2.0), .1))), 2.0) + 1));
    }
    return f;
}

/**
* Runs Ackleys One fitness function and calculates its value
*
* @param  dim  an integer epresenting the number of dimensions
* @param  myArray  an array of type double
* @return      the fitness of the array
*/
double ackleysOneFun(int dim, double myArray[]) {
    double eulersConstant = exp(1.0);
    double f = 0.0;
    int i;
        for (i = 0; i < dim - 1; i ++) {
            f += pow(eulersConstant, -0.2) * (pow((pow(myArray[i], 2.0) + pow(myArray[i+1], 2.0)), 0.5) +
                (3 * ((cos(2 * (myArray[i])) + sin(2 * myArray[i+1])))));
        }
    return f;
}

/**
* Runs Ackleys two fitness function and calculates its value
*
* @param  dim  an integer epresenting the number of dimensions
* @param  myArray  an array of type double
* @return      the fitness of the array
*/
double ackleysTwoFun(int dim, double myArray[]) {
    double eulersConstant = exp(1.0);
    double f = 0.0;
    int i;
        for (i = 0; i < dim - 1; i ++) {
            f += 20 + eulersConstant - ((20) / (pow(eulersConstant, 0.2 * (pow(pow(myArray[i], 2.0) +
                pow(myArray[i+1], 2.0) + 1, 0.5) / 2)))) - pow(eulersConstant, (0.5 * (cos((2 * _Pi * myArray[i])) + cos(2 * _Pi * myArray[i+1]))));
        }
    return f;
}

/**
* Runs Egg Holder fitness function and calculates its value
*
* @param  dim  an integer epresenting the number of dimensions
* @param  myArray  an array of type double
* @return      the fitness of the array
*/
double eggHolderFun(int dim, double myArray[]) {
    double f = 0.0;
    int i;
        for (i = 0; i < dim - 1; i ++) {
            f += -(myArray[i]) * sin(pow(abs(myArray[i] - myArray[i+1] - 47), 0.5)) - (myArray[i+1] + 47) * 
                sin(pow(abs(myArray[i+1] + 47 + (myArray[i] / 2)), 0.5));
    }
    return f;
}

/**
* Runs Rana fitness function and calculates its value
*
* @param  dim  an integer epresenting the number of dimensions
* @param  myArray  an array of type double
* @return      the fitness of the array
*/
double ranaFun(int dim, double myArray[]) {
    double f = 0.0;
    int i;
        for (i = 0; i < dim - 1; i ++) {
            f += (myArray[i]) * sin(pow(abs(myArray[i+1] - myArray[i] + 1), 0.5)) * cos(pow(abs(myArray[i+1] + myArray[i] + 1), 0.5)) +
                (myArray[i+1] + 1) * cos(pow(abs(myArray[i+1] - myArray[i] + 1), 0.5)) * sin(pow(abs(myArray[i+1] + myArray[i] + 1), 0.5));
        }
    return f;
}

/**
* Runs Pathological fitness function and calculates its value
*
* @param  dim  an integer epresenting the number of dimensions
* @param  myArray  an array of type double
* @return      the fitness of the array
*/
double pathologicalFun(int dim, double myArray[]) {
    double f = 0.0;
    int i;
        for (i = 0; i < dim - 1; i ++) {
            f += 0.5 + ((pow(sin(pow(100 * pow(myArray[i], 2) + pow(myArray[i+1], 2), 0.5)), 2) - 0.5) /
                (1 + 0.001 * (pow(pow(myArray[i], 2) - 2 * myArray[i] * myArray[i+1] + pow(myArray[i+1], 2), 2))));
        }
    return f;
}

/**
* Runs Michaleqicz fitness function and calculates its value
*
* @param  dim  an integer epresenting the number of dimensions
* @param  myArray  an array of type double
* @return      the fitness of the array
*/
double michaleqiczFun(int dim, double myArray[]) {
    double f = 0.0;
    int i;
        for (i = 0; i < dim - 1; i ++) {
            f += sin(myArray[i]) * pow(sin(((i + 1) * pow(myArray[i], 2) / _Pi)), 20);
        }
        f = -(f);
    return f;
}

/**
* Runs Master Cosine Wave fitness function and calculates its value
*
* @param  dim  an integer epresenting the number of dimensions
* @param  myArray  an array of type double
* @return      the fitness of the array
*/
double mastersCosineWaveFun(int dim, double myArray[]) {
    double f = 0.0;
    double eulersConstant = exp(1.0);
    int i;
        for (i = 0; i < dim - 1; i ++) {
            f += pow(eulersConstant, ((-1 / 8) * (pow(myArray[i], 2) + pow(myArray[i+1], 2) + .05 * myArray[i+1] + myArray[i]))) *
                cos(4 * pow(pow(myArray[i], 2) + pow(myArray[i+1], 2) + (0.5 * myArray[i]) * myArray[i+1], 0.5));
        }
        f = -(f);
    return f;
}

/**
* Runs Shekels Foxholes fitness function and calculates its value
*
* @param  dim  an integer epresenting the number of dimensions
* @param  myArray  an array of type double
* @return      the fitness of the array
*/
double shekelsFoxholesFun(int dim, double myArray[]) {
    double f = 0.0;
    double l = 0.0;
    int i;
	double myArray2[30][10] = { { 9.681, 0.667, 4.783, 9.095, 3.517, 9.325, 6.544, 0.211, 5.122, 2.02 },
	{ 9.4,2.041,3.788,7.931,2.882,2.672,3.568,1.284,7.033,7.374 },
	{ 8.025,9.152,5.114,7.621,4.564,4.711,2.996,6.126,0.734,4.982 },
	{ 2.196,0.415,5.649,6.979,9.510,9.166,6.304,6.054,9.377,1.426 },
	{ 8.074,8.777,3.467,1.863,6.708,6.349,4.534,0.276,7.633,1.567 },
	{ 7.650,5.658,0.720,2.764,3.278,5.283,7.474,6.274,1.409,8.208 },
	{ 1.256,3.605,8.623,6.905,4.584,8.133,6.071,6.888,4.187,5.448 },
	{ 8.314,2.261,4.24,1.781,4.124,0.932,8.129,8.658,1.208,5.762 },
	{ 0.226,8.858,1.42,0.954,1.622,4.698,6.228,9.096,0.972,7.637 },
	{ 7.305,2.228,1.242,5.928,9.133,1.826,4.06,5.204,8.713,8.247 },
	{ 0.652,7.027,0.508,4.876,8.807,4.632,5.808,6.937,3.291,7.016 },
	{ 2.699,3.516,5.847,4.119,4.461,7.496,8.817,0.69,6.593,9.789 },
	{ 8.327,3.897,2.017,9.57,9.825,1.15,1.395,3.885,6.354,0.109 },
	{ 2.132,7.006,7.136,2.641,1.882,5.943,7.273,7.691,2.88,0.564 },
	{ 4.707,5.579,4.08,0.581,9.698,8.542,8.077,8.515,9.231,4.67 },
	{ 8.304,7.559,8.567,0.322,7.128,8.392,1.472,8.524,2.277,7.826 },
	{ 8.632,4.409,4.832,5.768,7.05,6.715,1.711,4.323,4.405,4.591 },
	{ 4.887,9.112,0.17,8.967,9.693,9.867,7.508,7.77,8.382,6.74 },
	{ 2.44,6.686,4.299,1.007,7.008,1.427,9.398,8.48,9.95,1.675 },
	{ 6.306,8.583,6.084,1.138,4.350,3.134,7.853,6.061,7.457,2.258 },
	{ 0.652,2.343,1.37,0.821,1.31,1.063,0.689,8.819,8.833,9.07 },
	{ 5.558,1.272,5.756,9.857,2.279,2.764,1.284,1.677,1.244,1.234 },
	{ 3.352,7.549,9.817,9.437,8.687,4.167,2.57,6.54,0.228,0.027 },
	{ 8.798,0.88,2.37,0.168,1.701,3.68,1.231,2.39,2.499,0.064 },
	{ 1.46,8.057,1.337,7.217,7.914,3.615,9.981,9.198,5.292,1.224 },
	{ 0.432,8.645,8.774,0.249,8.081,7.461,4.416,0.652,4.002,4.644 },
	{ 0.679,2.8,5.523,3.049,2.968,7.225,6.73,4.199,9.614,9.229 },
	{ 4.263,1.074,7.286,5.599,8.291,5.2,9.214,8.272,4.398,4.506 },
	{ 9.496,4.83,3.15,8.27,5.079,1.231,5.731,9.494,1.883,9.732 },
	{ 4.138,2.562,2.532,9.661,5.611,5.5,6.886,2.341,9.699,6.5 } };
	double myArray3[30] = { 1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0,14.0,15.0,16.0,17.0,18.0,19.0,20.0,21.0,22.0,23.0,24.0,25.0,26.0,27.0,28.0,29.0,30.0 };

    for (i = 0; i < 30; i ++) {

            for (int k = 0; k < 10; k ++) {
                l += pow((myArray[k] - myArray2[i][k]), 2);
            }
            f += ((1) / (myArray3[i] + l));
        }
        f = -(f);
    return f;
}
int getNumFunctions() {
    return 14;
}
