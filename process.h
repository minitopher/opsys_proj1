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
		int getTime(){
			return INIT_ARR + CPU_BURST + NUM_BURST + IO_TIME;
		}
		void subINIT(){
			INIT_ARR -= 1;
		}
		
	private : 
		char PROC_ID;
		int INIT_ARR;
		int CPU_BURST;
		int NUM_BURST;
		int IO_TIME;
};