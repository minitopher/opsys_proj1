#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <string>
#include<cstdlib>
#include <limits>

#include "process.h"

std::vector<Process>::iterator getSRT(std::vector<Process> queue){
	std::vector<Process>::iterator shortest;
	int SRT = std::numeric_limits<int>::max();
	for(std::vector<Process>::iterator it = queue.begin(); it != queue.end(); it++){
		//FIND FIRST ONE THAT ARRIVES FIRST
		if(it->getCPU() < SRT){
			shortest = it;
		}
	}
	return shortest;
}

int totaltime(std::vector<Process> queue){
	int Longest = 0;
	for(std::vector<Process>::iterator it = queue.begin(); it != queue.end(); it++){
		//FIND FIRST ONE THAT ARRIVES FIRST
		if(it->getTime() > Longest){
			Longest = it->getTime();
		}
	}
	return Longest;
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
	//std::cout << processes.size() << std::endl;
	/*	//SHOWS THAT GET FUNCTIONS WORK
	for(std::vector<Process>::iterator it = processes.begin(); it != processes.end(); it++){
		std::cout << it->getINIT() << std::endl;
	}
	*/
	
	
	//SHORTEST REMAINING TIME
	//MAKE A READY QUEUE AND ADD ALL PROCESS INTO IT
	std::vector<Process> readyQueue;
	//int i = totaltime(processes);
	int i = 100000;
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
		if(holder != readyQueue.end()){
			//std::cout << holder->getPROC() << " IS HOLDER" << std::endl;
			if(holder->getCPU() != 0){
				holder->subCPU();
				if(holder->getCPU() == 0){
					if(holder->getNUM() == 1){
						std::cout << holder->getPROC() << " WENT THROUGH CPU BURST" << std::endl;
						for(finder = processes.begin(); finder != processes.end(); finder++){
							if(finder->getPROC() == holder->getPROC()){
								processes.erase(finder);
							}
							std::cout<< "ERASED" << std::endl;
						}
						readyQueue.erase(holder);
					}
					else{
						std::cout << holder->getPROC() << " WENT THROUGH CPU BURST BUT NEEDS MORE" << holder->getNUM() << std::endl;
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

		
		//std::vector<Process>::iterator holder = getSRT(readyQueue);
		
		
		i--;
	}
	
	
	//something something output file idk
}