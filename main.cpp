#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <cstdlib>
#include <limits>

#include "process.h"

int getSRT(std::vector<Process> queue, int newTime){
	int location = 0;
	for(std::vector<Process>::iterator it = queue.begin(); it != queue.end(); it++){
		//FIND WHERE NEWTIME FITS INTO THE QUEUE
		if(it->getCPU() < newTime){
			location++;
		}
	}
	return location;
}

int totaltime(std::vector<Process> queue){
	int Longest = 0;
	for(std::vector<Process>::iterator it = queue.begin(); it != queue.end(); it++){
		//FIND THE MAXIMAL TOTAL TIME NEEDED
		Longest += it->getTime();
	}
	return Longest;
}

void FCFS(std::vector<Process> &processes){
	//First come first serve
	//MAKE A READY QUEUE AND ADD ALL PROCESS INTO IT
	int t_cs = 0;
	std::vector<Process> readyQueue;
	char timeHolder;
	std::cout <<"time " << t_cs << "ms: Simulator started for FCFS [Q <empty>]" << std::endl;
	int i = totaltime(processes);
	while (i > 0){
		for(std::vector<Process>::iterator it = processes.begin(); it != processes.end(); it++){
			if(it->getINIT() == 0){
				bool found = false;
				for(std::vector<Process>::iterator check = readyQueue.begin(); check != readyQueue.end(); check++){
					if(it->getPROC() == check->getPROC()){
						found = true;
					}
				}
				if(found == false){
					readyQueue.push_back(*it);
					std::cout <<"time " << t_cs << "ms: Process "<< it->getPROC() << " arrived and added to the ready queue [Q";
					std::vector<Process>::iterator write = readyQueue.begin();
					if(write == readyQueue.end()){
						std::cout << " <empty> ";
					}
					for(write = readyQueue.begin(); write != readyQueue.end(); write++){
						if(timeHolder != write->getPROC()){
							std::cout << " " << write->getPROC();
						}
					}
					std::cout<< "]" << std::endl;
				}
			}
			else{
				it->subINIT();
			}
		}
		//CPU BURST
		std::vector<Process>::iterator holder = readyQueue.begin();
		if(timeHolder == NULL){
			timeHolder = holder->getPROC();
			t_cs += 4;
			std::cout <<"time " << t_cs << "ms: Process "<< holder->getPROC() << " started using the CPU [Q";
			std::vector<Process>::iterator write = readyQueue.begin();
			if(write == readyQueue.end()){
				std::cout << " <empty> ";
			}
			for(write = readyQueue.begin(); write != readyQueue.end(); write++){
				if(timeHolder != write->getPROC()){
					std::cout << " " << write->getPROC();
				}
			}
			std::cout<< "]" << std::endl;
		}
		else if(timeHolder != holder->getPROC()){
			timeHolder = holder->getPROC();
			t_cs += 4;
			std::cout <<"time " << t_cs << "ms: Process "<< holder->getPROC() << " started using the CPU [Q";
			std::vector<Process>::iterator write = readyQueue.begin();
			if(write == readyQueue.end()){
				std::cout << " <empty> ";
			}
			for(write = readyQueue.begin(); write != readyQueue.end(); write++){
				if(timeHolder != write->getPROC()){
					std::cout << " " << write->getPROC();
				}
			}
			std::cout<< "]" << std::endl;
		}
		std::vector<Process>::iterator finder;
		
		if(holder != readyQueue.end()){						//while holder doesnt reach the end of the queue

			if(holder->getCPU() != 0){						//checks the current holder iterator and sees the remaining CPU time, continues if not 0
				holder->subCPU();	
			}				//subtracts 1 from the CPU burst time remaining
			else if(holder->getCPU() == 0){				//checks to see that the current holder is 0, goes through the process of deleting it
				if(holder->getNUM() == 1){				//if the number of processes is 1 continue on						
					for(finder = processes.begin(); finder != processes.end(); finder++){		//iterates through processes
						if(finder->getPROC() == holder->getPROC()){
							std::cout <<"time " << t_cs << "ms: Process "<< holder->getPROC() << " terminated [Q";
							std::vector<Process>::iterator write = readyQueue.begin();
							if(write == readyQueue.end()){
								std::cout << " <empty> ";
							}
							for(write = readyQueue.begin(); write != readyQueue.end(); write++){									
								if(timeHolder != write->getPROC()){
									std::cout << " " << write->getPROC();
								}								
							}
							std::cout<< "]" << std::endl;
							t_cs += 4;							
							processes.erase(finder);  //if those are the same, erase 
							break;
						}
					}
					readyQueue.erase(holder);
				}
				else{
					std::cout <<"time " << t_cs << "ms: Process "<< holder->getPROC() << " completed a CPU burst; " << holder->getNUM() - 1 << " bursts to go [Q";
					std::vector<Process>::iterator write = readyQueue.begin();
					if(write == readyQueue.end()){
						std::cout << " <empty> ";
					}
					for(write = readyQueue.begin(); write != readyQueue.end(); write++){
						if(timeHolder != write->getPROC()){
							std::cout << " " << write->getPROC();					
						}
					}
					std::cout<< "]" << std::endl;
					int temp;
					for(finder = processes.begin(); finder != processes.end(); finder++){
						if(finder->getPROC() == holder->getPROC()){
							finder->replaceCPU();
							finder->subNUM();
							finder->replaceINIT();
							temp = finder->getIO() + t_cs;
						}
					}
					std::cout <<"time " << t_cs << "ms: Process "<< holder->getPROC() << " switching out of CPU; will block on I/O until time " << temp + 4 << "ms [Q";
					if(write == readyQueue.end()){
						std::cout << " <empty> ";
					}
					for(write = readyQueue.begin(); write != readyQueue.end(); write++){
						if(timeHolder != write->getPROC()){
							std::cout << " " << write->getPROC();
						}						
					}
					std::cout<< "]" << std::endl;
					t_cs += 4;
					readyQueue.erase(holder);
				}
			}
		
		}
		
		i--;
		t_cs ++;
	}
	std::cout <<"time " << t_cs << "ms: Simulator ended for FCFS" << std::endl;
}
void ShortestRemainingTime(std::vector<Process> processes){
	//Shortest Remaining Time
	//MAKE A READY QUEUE AND ADD ALL PROCESS INTO IT
	std::vector<Process> readyQueue;
	int i = totaltime(processes);
	while (i > 0){
		for(std::vector<Process>::iterator it = processes.begin(); it != processes.end(); it++){
			if(it->getINIT() == 0){
				bool found = false;
				for(std::vector<Process>::iterator check = readyQueue.begin(); check != readyQueue.end(); check++){
					if(it->getPROC() == check->getPROC()){
						found = true;
					}
				}
				if(found == false){
					if( readyQueue.begin() == readyQueue.end()){		//if theres nothing in the queue yet just add it to the beginning
						readyQueue.push_back(*it);
					}
					else{
						int location = getSRT(readyQueue, it ->getCPU());		//find where the new process belongs in the queue
						if (location == 0){										//If it ends up being the shortest amount of time, just add it to the front
							std::vector<Process>::iterator iter = readyQueue.begin();
							readyQueue.insert(iter, *it);
						}
						else{
							int count = 1;											//Else find that location and insert dat boi
							for(std::vector<Process>::iterator iter = readyQueue.begin(); iter != readyQueue.end(); iter++){
								if(location == count){							
									iter++;
									readyQueue.insert(iter, *it);
									break;
								}
								count++;
							}
						}
					}
					std::cout << it->getPROC() << " ADDED TO READY QUEUE" << std::endl;
				}
			}
			else{
				it->subINIT();
			}
		}
		//CPU BURST
		std::vector<Process>::iterator holder = readyQueue.begin();		
		std::vector<Process>::iterator finder;
		
		if(holder != readyQueue.end()){						//while holder doesnt reach the end of the queue

			if(holder->getCPU() != 0){						//checks the current holder iterator and sees the remaining CPU time, continues if not 0
				holder->subCPU();							//subtracts 1 from the CPU burst time remaining
				
				if(holder->getCPU() == 0){					//checks to see that the current holder is 0, goes through the process of deleting it
				
					if(holder->getNUM() == 1){				//if the number of processes is 1 continue on						
						for(finder = processes.begin(); finder != processes.end(); finder++){		//iterates through processes
							if(finder->getPROC() == holder->getPROC()){
								std::cout<< finder->getPROC() << " HAS FINISHED BEING PROCESSED" << std::endl;
								processes.erase(finder);  //if those are the same, erase 
								break;
							}
						}
						readyQueue.erase(holder);
					}
					else{
						std::cout << holder->getPROC() << " WENT THROUGH CPU BURST BUT NEEDS MORE (" << holder->getNUM() - 1<< ") TIMES"<< std::endl;
						for(finder = processes.begin(); finder != processes.end(); finder++){
							if(finder->getPROC() == holder->getPROC()){
								finder->replaceCPU();
								finder->subNUM();
								finder->replaceINIT();
							}
						}
						readyQueue.erase(holder);
					}
				}
			}
		}
		
		i--;
	}
}

void RoundRobin(std::vector<Process> processes){
	std::vector<Process> readyQueue;
	int t_slice = 70;
	int i = totaltime(processes);
	int tt = 0;
	int t_slice_left = t_slice;
	
	std::vector<Process>::iterator finder;
	
	int j = 0;
	while (i > 0){

		for(std::vector<Process>::iterator it = processes.begin(); it != processes.end(); it++){		//Same as FCFS
			if(it->getINIT() == 0){																		//Adds the process when the join time matches
				bool found = false;
				for(std::vector<Process>::iterator check = readyQueue.begin(); check != readyQueue.end(); check++){
					if(it->getPROC() == check->getPROC()){
						found = true;
					}
				}
				if(found == false){
					readyQueue.push_back(*it);
					std::cout << it->getPROC() << " ADDED TO READY QUEUE" << std::endl;
					tt+=4;
				}
			}
			else{
				it->subINIT();
			}
		}

		if (processes[j].getCPU() == 0){
			t_slice_left = t_slice;
			if (processes[j].getNUM() == 1){
				for (finder = processes.begin(); finder != processes.end(); finder++){
					if (finder->getPROC() == processes[j].getPROC()){
						processes.erase(finder);
						break;
					}
				}
				readyQueue.erase(readyQueue.begin() + j);
			} else {
				for (finder = processes.begin(); finder != processes.end(); finder++){
					if(finder->getPROC() == processes[j].getPROC()){
						finder->replaceCPU();
						finder->subNUM();
						finder->replaceINIT();
						if (j + 1 == readyQueue.size()){
							j = 0;
						}else{
							j++;
						}
						printf("Re-adding to the queue\n");
						tt+=4;
					}
				}
			}
		}else if (t_slice_left == 0){
			t_slice_left = t_slice;
			if (readyQueue.size() == 1){

			}else{
				printf("Switching to next object in queue\n");
				if (j + 1 == readyQueue.size()){
					j = 0;
				}else{
					j++;
				}
				tt+=4;
			}
		}else if (t_slice_left > 0){
			printf("%d: 1ms of %c, with CPU of %d left and Timeslice of %d left\n", tt , processes[j].getPROC(), processes[j].getCPU(),t_slice_left);
			processes[j].subCPU();
			tt++;
			t_slice_left--;
		}
		
		i--;		
	}
	

int main(int argc, char* argv[]){
	//argv[1] should be the input file, and (i think?) argv[2] should be output file
	
	std::ifstream input( argv[1] );
	std::vector<Process> processes;
	for (std::string line; getline (input, line); ){
		if (line[0] == '#'){
			continue;
		}else{

			char PROC;
			int INIT;
			int CPU;
			int NUM;
			int IO;
			
			std::vector<char> arr;
			
			PROC = line[0];
			int i = 2;

			while (line[i] != '|'){
				arr.push_back(line[i]);
				i++;
			}
			std::string temp(arr.begin(), arr.end());
			INIT = std::atoi(temp.c_str());
            arr.clear();
			i++;
			
			while (line[i] != '|'){
				arr.push_back(line[i]);
				i++;
			}
			std::string temp1(arr.begin(), arr.end());
			CPU = std::atoi(temp1.c_str());
            arr.clear();
			i++;
			
			while (line[i] != '|'){
				arr.push_back(line[i]);
				i++;
			}
			std::string temp2(arr.begin(), arr.end());
			NUM = std::atoi(temp2.c_str());
            arr.clear();
			i++;
			
			while (i < line.size()){
				arr.push_back(line[i]);
				i++;
			}
			std::string temp3(arr.begin(), arr.end());
			IO = std::atoi(temp3.c_str());
			
			Process* p = new Process();
			p->add_process(PROC, INIT,CPU,NUM,IO);
			processes.push_back(*p);

		}
	}
	
	std::vector<Process> temp = processes;	//temp is a copy of processes, idk if this actually matters, but whatever
	FCFS(temp);								//goes through first come first serve

	
	
	//something something output file idk
}
