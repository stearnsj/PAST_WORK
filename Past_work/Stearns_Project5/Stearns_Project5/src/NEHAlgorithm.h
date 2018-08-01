#include <vector>
#include <ctime>
#include <fstream>
using namespace std;
class NEHAlgorithm
{
public:
	//! A constructor.
	/*!
	Constructs the NEHAlgorithmclass, and assigns the values.
	\param The name of the file of which to read from.
	*/
	NEHAlgorithm(string fname);
	//! A destructor.
	/*!
	Clears the memory.
	*/
	~NEHAlgorithm();
	//! Returns An array of sorted jobs
	/*!
	\param no parameters
	\return An array containing the jobs sorted from largest to smallest
	*/
	int * sortbyTime();
	//! A normal member taking in the scheduleand the current index of the job and returning optimal job order.
	/*!
	\param A flowshop schedule
	\param the current job index
	\return The optimal job order for FSS
	*/
	vector<int> sortFSSbyTime(vector<int> sequence, int nextIndex);
	//! A normal member taking in the scheduleand the current index of the job and returning optimal job order.
	/*!
	\param A flowshop schedule
	\param the current job index
	\return The optimal job order for FSSB
	*/
	vector<int> sortFSSBbyTime(vector<int> sequence, int nextIndex);
	//! A normal member taking in the scheduleand the current index of the job and returning optimal job order.
	/*!
	\param A flowshop schedule
	\param the current job index
	\return The optimal job order for FSSNW
	*/
	vector<int> sortFSSNWbyTime(vector<int> sequence, int nextIndex);
	//! Returns The Makespan for FSS Algorithm
	/*!
	\param no parameters
	\return The Makespan for FSS Algorithm
	*/
	float runFSSAlgorithm();
	//! Returns The Makespan for FSSB Algorithm
	/*!
	\param no parameters
	\return The Makespan for FSSB Algorithm
	*/
	float runFSSBAlgorithm();
	//! Returns The Makespan for FSSNW Algorithm
	/*!
	\param no parameters
	\return The Makespan for FSSNW Algorithm
	*/
	float runFSSNWAlgorithm();
private:
	//! The processing time matrix.
	float** m_ProcessTime;
	//! The completion time matrix.
	float** m_CompletionTime;
	//! The number of jobs.
	int m_Jobs;
	//! The number of machines.
	int m_Machines;
	//! The file name.
	string filename;
	//! A counter for the number of function calls.
	int counter = 0;
	//! Clock for the timing of execution time.
	clock_t start;
	//! The duration of the algorithm.
	double duration;
};
//! Struct for sorting jobs
/*!
\param sum of the execution time of the job on all machines
\param Job Number
\return A struct
*/
typedef struct
{
	float value; int index;
}strs;
