#include <iostream>
#include "NEHAlgorithm.h"
#include <string>
#include <ctime>
#include <fstream>

using namespace std;

int main()
{
	for (int i = 1; i <= 120; i++) {
		string fname;

		fname.assign("/FSS/test/" + to_string(i) + ".txt");
		NEHAlgorithm run = NEHAlgorithm(fname);
		cout << run.runFSSAlgorithm() << endl;
		cout << run.runFSSBAlgorithm() << endl;
		cout << run.runFSSNWAlgorithm() << endl;
		cout << "finished " << i << " file" << endl;
	}
	return 0;
}