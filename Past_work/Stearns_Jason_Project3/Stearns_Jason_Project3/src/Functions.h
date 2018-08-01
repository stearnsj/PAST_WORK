#include "stdafx.h"
#include <cmath>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <vector>
#include <random>

using namespace std; 
#pragma once

double schwefelFun(int dim, double myArray[]);
double istDeJongFun(int dim, double myArray[]);
double rosenbrockFun(int dim, double myArray[]);
double rastriginFun(int dim, double myArray[]);
double griewangk(int dim, double myArray[]);
double sineEnvelopeSinceWaveFun(int dim, double myArray[]);
double stretchedVSineWaveFun(int dim, double myArray[]);
double ackleysOneFun(int dim, double myArray[]);
double ackleysTwoFun(int dim, double myArray[]);
double eggHolderFun(int dim, double myArray[]);
double ranaFun(int dim, double myArray[]);
double pathologicalFun(int dim, double myArray[]);
double michaleqiczFun(int dim, double myArray[]);
double mastersCosineWaveFun(int dim, double myArray[]);
double shekelsFoxholesFun(int dim, double myArray[]);
int getNumFunctions();

