#include <iostream>
#include <vector>
#include <string> 

class Process{
	public :
		//constructor
		Process(char PROC, int INIT, int CPU, int NUM, int IO) : PROC_ID(PROC), INIT_ARR(INIT), CPU_BURST(CPU), NUM_BURST(NUM), IO_TIME(IO);
		
		//should be useful shit here that interacts with the variables
		
	private : 
		char PROC_ID;
		int INIT_ARR;
		int CPU_BURST;
		int NUM_BURST;
		int IO_TIME;
}