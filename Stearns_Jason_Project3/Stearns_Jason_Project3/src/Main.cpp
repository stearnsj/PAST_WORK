// ConsoleApplication2.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "run.h"
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  



int main(int argc, char *argv[])
{
	
	run Run = run();
	Run.runProject3();

	return 0;
}

