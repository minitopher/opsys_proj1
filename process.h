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
			return INIT_ARR + (CPU_BURST * NUM_BURST) + (IO_TIME * NUM_BURST);
		}
		void subINIT(){
			INIT_ARR -= 1;
		}
		void subCPU(){
			CPU_BURST -= 1;
		}
		void subNUM(){
			NUM_BURST -= 1;
		}
		void replaceCPU(){
			CPU_BURST = CPU_REPLACE;
		}
		void replaceINIT(){
			INIT_ARR = INIT_REPLACE;
		}
		bool hasARRIVED(){
			return ARR;
		}
		void setARRIVED(){
			ARR = true;
		}
		bool isPreempted(){
			return pre;
		}
		void setPre(bool which){
			pre = which;
		}
		
	private : 
		char PROC_ID;
		int INIT_ARR;
		int CPU_BURST;
		int NUM_BURST;
		int IO_TIME;
		int CPU_REPLACE;
		int INIT_REPLACE;
		bool ARR;
		bool pre;
};