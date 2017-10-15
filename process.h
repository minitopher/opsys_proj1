#include <iostream>
#include <vector>
#include <string> 

class Process{
	public :
		//constructor
		Process();
		
		void add_process(char PROC, int INIT, int CPU, int NUM, int IO);
		//should be useful shit here that interacts with the variables
		
	private : 
		char PROC_ID;
		int INIT_ARR;
		int CPU_BURST;
		int NUM_BURST;
		int IO_TIME;
};