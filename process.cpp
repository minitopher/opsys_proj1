#include <cstdlib>
#include "process.h"

Process::Process(){
    
}

void Process::add_process(const char PROC, const int INIT, const int CPU, const int NUM, const int IO){
    PROC_ID = PROC;
    INIT_ARR = INIT;
    CPU_BURST = CPU;
    NUM_BURST = NUM;
    IO_TIME = IO;
	CPU_REPLACE = CPU_BURST;
	INIT_REPLACE = IO_TIME;
	ARR = false;
	pre = false;
}


//Some useful shit should probably go here, idk