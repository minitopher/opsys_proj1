#include <iostream>
#include <vector>
#include <string> 

class Process{
	public :
		//constructor
		Process();
		
		void add_process(char PROC, int INIT, int CPU, int NUM, int IO);
		//should be useful shit here that interacts with the variables
		
		char getPROC(){
			return PROC_ID;
		}
		int getINIT(){
			return INIT_ARR;
		}
		int getCPU(){
			return CPU_BURST;
		}
		int getNUM(){
			return NUM_BURST;
		}
		int getIO(){
			return IO_TIME;
		}
		
	private : 
		char PROC_ID;
		int INIT_ARR;
		int CPU_BURST;
		int NUM_BURST;
		int IO_TIME;
};