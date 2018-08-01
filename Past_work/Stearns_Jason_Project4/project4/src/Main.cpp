#include "run.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
int main(int argc, char *argv[])
{
	run Run = run();
	Run.runProject4();
	return 0;
}