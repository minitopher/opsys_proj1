#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <cstdlib>
#include <limits>
#include <iomanip>

#include "process.h"

//Project members: leec21 hendrd


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

std::string queue(std::vector<Process> processes, char current){
	std::string temp = "[Q";
	if (processes.size() == 0){
		temp.append(" <empty>");
	} else if (processes.size() == 1 && processes[0].getPROC() == current){
		temp.append(" <empty>");
	}
	else{
		for (unsigned int i = 0; i < processes.size(); i++){
			if (processes[i].getPROC() == current){
				continue;
			}
			temp.append(" ");
			temp += processes[i].getPROC();
		}
	}
	temp.append("]");
	return temp;

}
	
	


void FCFS(std::vector<Process> &processes,  std::ofstream &fout){
	
	double CPU_average = 0;
	for (unsigned int i = 0; i < processes.size(); i++){
		CPU_average += double(processes[i].getCPU());
	}
	CPU_average = CPU_average/double(processes.size());

	double init_average = 0;
	std::vector<double> waits;
	std::vector<double> turnarounds;

	int context_switch = 0;
	double turn_avg = 0;
	//First come first serve
	//MAKE A READY QUEUE AND ADD ALL PROCESS INTO IT
	int t_cs = 0;
	std::vector<Process> readyQueue;
	char timeHolder;
	int counter = 0;
	std::cout <<"time " << t_cs << "ms: Simulator started for FCFS [Q <empty>]" << std::endl;
	bool end = false;
	while (end == false){
		for(std::vector<Process>::iterator it = processes.begin(); it != processes.end(); it++){
			if(it->getINIT() == 0){
				bool found = false;
				for(std::vector<Process>::iterator check = readyQueue.begin(); check != readyQueue.end(); check++){
					if(it->getPROC() == check->getPROC()){
						found = true;
						if(it->getPROC() != timeHolder){
							it->increaseWait();
						}
					}
				}
				if(found == false){
					readyQueue.push_back(*it);
					if(it->hasARRIVED()){
						std::cout <<"time " << it->getNewTime() << "ms: Process "<< it->getPROC() << " completed I/O; added to ready queue [Q";
						std::vector<Process>::iterator write = readyQueue.begin();
						if(write == readyQueue.end()){
							std::cout << " <empty>";
						}
						for(write = readyQueue.begin(); write != readyQueue.end(); write++){
							if(timeHolder != write->getPROC()){
								std::cout << " " << write->getPROC();
							}
						}
						std::cout<< "]" << std::endl;
					}
					else{
						std::cout <<"time " << counter << "ms: Process "<< it->getPROC() << " arrived and added to ready queue [Q";
						std::vector<Process>::iterator write = readyQueue.begin();
						if(write == readyQueue.end()){
							std::cout << " <empty>";
						}
						for(write = readyQueue.begin(); write != readyQueue.end(); write++){
							if(timeHolder != write->getPROC()){
								std::cout << " " << write->getPROC();
							}
						}
						std::cout<< "]" << std::endl;
						it->setARRIVED();
					}
				}
			}
			else{
				it->subINIT();
			}
		}
		//CPU BURST
		std::vector<Process>::iterator holder = readyQueue.begin();
		if(holder != readyQueue.end()){
			if(timeHolder == '^'){
				timeHolder = holder->getPROC();
				t_cs += 4;
				context_switch++;
				std::cout <<"time " << t_cs << "ms: Process "<< holder->getPROC() << " started using the CPU [Q";
				std::vector<Process>::iterator write = readyQueue.begin();
				if(write == readyQueue.end()){
					std::cout << " <empty>";
				}
				for(write = readyQueue.begin(); write != readyQueue.end(); write++){
					if(timeHolder != write->getPROC()){
						std::cout << " " << write->getPROC();
					}
					else if(readyQueue.size() == 1){
						std::cout << " <empty>";
					}
				}
				std::cout<< "]" << std::endl;
			}
			else if(timeHolder != holder->getPROC()){
				timeHolder = holder->getPROC();
				t_cs += 4;
				context_switch++;
				std::cout <<"time " << t_cs << "ms: Process "<< holder->getPROC() << " started using the CPU [Q";
				std::vector<Process>::iterator write = readyQueue.begin();
				if(write == readyQueue.end()){
					std::cout << " <empty>";
				}
				for(write = readyQueue.begin(); write != readyQueue.end(); write++){
					if(timeHolder != write->getPROC()){
						std::cout << " " << write->getPROC();
					}
					else if(readyQueue.size() == 1){
						std::cout << " <empty>";
					}
				}
				std::cout<< "]" << std::endl;
			}
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
								std::cout << " <empty>";
							}
							for(write = readyQueue.begin(); write != readyQueue.end(); write++){									
								if(timeHolder != write->getPROC()){
									std::cout << " " << write->getPROC();
								}
								else if(readyQueue.size() == 1){
									std::cout << " <empty>";
								}
							}
							std::cout<< "]" << std::endl;
							t_cs += 3;	
							waits.push_back(finder->getWait());
							turnarounds.push_back(finder->getWait() + finder->getCPUReplace() + 8);
							processes.erase(finder);  //if those are the same, erase 
							break;
						}
					}
					readyQueue.erase(holder);
				}
				else{
					std::cout <<"time " << t_cs << "ms: Process "<< holder->getPROC() << " completed a CPU burst; " << holder->getNUM() - 1;
					if(holder->getNUM() - 1 == 1){
						std::cout << " burst to go [Q";
					}
					else{
						std::cout << " bursts to go [Q";
					}
					std::vector<Process>::iterator write = readyQueue.begin();
					if(write == readyQueue.end()){
						std::cout << " <empty>";
					}
					for(write = readyQueue.begin(); write != readyQueue.end(); write++){
						if(timeHolder != write->getPROC()){
							std::cout << " " << write->getPROC();					
						}
						else if(readyQueue.size() == 1){
							std::cout << " <empty>";
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
							break;
						}
					}
					write = readyQueue.begin();
					std::cout <<"time " << t_cs << "ms: Process "<< holder->getPROC() << " switching out of CPU; will block on I/O until time " << temp + 4 << "ms [Q";
					if(write == readyQueue.end()){
						std::cout << " <empty>";
					}
					for(write = readyQueue.begin(); write != readyQueue.end(); write++){
						if(timeHolder != write->getPROC()){
							std::cout << " " << write->getPROC();
						}
						else if(readyQueue.size() == 1){
							std::cout << " <empty>";
						}
					}
					std::cout<< "]" << std::endl;
					t_cs += 3;					
					finder->setNewTime((temp + 4));
					timeHolder = '^';
					readyQueue.erase(holder);
				}
			}
		
		}
		t_cs ++;
		counter += 1;	
		if(processes.size() == 0){
			std::cout <<"time " << t_cs << "ms: Simulator ended for FCFS" << std::endl;
			end = true;
		}
	}
	
	for(unsigned int i = 0; i < waits.size(); i++){
		init_average += waits[i];
	}
	init_average /= waits.size();
	
	for(unsigned int i = 0; i < turnarounds.size(); i++){
		turn_avg += turnarounds[i];
	}
	turn_avg /= turnarounds.size();

	fout << std::fixed;
	fout << "Algorithm FCFS" << std::endl;
	fout << "-- average CPU burst time: " << std::setprecision(2) << CPU_average << " ms" << std::endl;
	fout << "-- average wait time: " << std::setprecision(2) << init_average << " ms" << std::endl;
	fout << "-- average turnaround time: " << std::setprecision(2) << turn_avg <<" ms" << std::endl;
	fout << "-- total number of context switches: " << context_switch << std::endl;
	fout << "-- total number of preemptions: " << 0 << std::endl;
}
void ShortestRemainingTime(std::vector<Process> processes, std::ofstream &fout){
	double CPU_average = 0;
	for (unsigned int i = 0; i < processes.size(); i++){
		CPU_average += double(processes[i].getCPU());
	}
	CPU_average = CPU_average/double(processes.size());

	double init_average = 0;
	std::vector<double> waits;
	std::vector<double> turnarounds;
	int context_switch = 0;
	double turn_avg = 0;
	int preemptions = 0;
	//Shortest Remaining Time
	//MAKE A READY QUEUE AND ADD ALL PROCESS INTO IT
	std::vector<Process> readyQueue;
	bool end = false;
	int t_cs = 0;
	char timeHolder;
	bool preempted = false;
	int counter = 0;
	std::cout <<"time " << t_cs << "ms: Simulator started for SRT [Q <empty>]" << std::endl;
	while (end == false){
		for(std::vector<Process>::iterator it = processes.begin(); it != processes.end(); it++){
			if(it->getINIT() == 0){
				bool found = false;
				for(std::vector<Process>::iterator check = readyQueue.begin(); check != readyQueue.end(); check++){
					if(it->getPROC() == check->getPROC()){
						found = true;
						if(it->getPROC() != timeHolder){
							it->increaseWait();
						}
					}
				}
				if(found == false){
					if( readyQueue.begin() == readyQueue.end()){		//if theres nothing in the queue yet just add it to the beginning
						readyQueue.push_back(*it);
						if(it->hasARRIVED()){
							std::cout <<"time " << it->getNewTime() << "ms: Process "<< it->getPROC() << " completed I/O; added to ready queue [Q";
							std::vector<Process>::iterator write = readyQueue.begin();
							if(write == readyQueue.end()){
								std::cout << " <empty>";
							}
							for(write = readyQueue.begin(); write != readyQueue.end(); write++){
								if(timeHolder != write->getPROC()){
									std::cout << " " << write->getPROC();
								}
							}
							std::cout<< "]" << std::endl;
						}
						else{
							std::cout <<"time " << counter << "ms: Process "<< it->getPROC() << " arrived and added to ready queue [Q";
							std::vector<Process>::iterator write = readyQueue.begin();
							if(write == readyQueue.end()){
								std::cout << " <empty>";
							}
							for(write = readyQueue.begin(); write != readyQueue.end(); write++){
								if(timeHolder != write->getPROC()){
									std::cout << " " << write->getPROC();
								}
							}
							std::cout<< "]" << std::endl;
							it->setARRIVED();
						}
					}
					else{
						unsigned int location = getSRT(readyQueue, it ->getCPU());		//find where the new process belongs in the queue
						std::vector<Process>::iterator iter = readyQueue.begin();
						if (location == 0){										//If it ends up being the shortest amount of time, just add it to the front
							readyQueue.insert(iter, *it);
						}
						else{
							unsigned int count = 1;											//Else find that location and insert dat boi
							for(iter = readyQueue.begin(); iter != readyQueue.end(); iter++){
								if(location == count){							
									iter++;
									readyQueue.insert(iter, *it);
									break;
								}
								count++;
							}
						}
						if(location == readyQueue.size() - 1){
							if(it->hasARRIVED()){
								std::cout <<"time " << it->getNewTime() << "ms: Process "<< it->getPROC() << " completed I/O; added to ready queue [Q";
								std::vector<Process>::iterator write = readyQueue.begin();
								if(write == readyQueue.end()){
									std::cout << " <empty>";
								}
								for(write = readyQueue.begin(); write != readyQueue.end(); write++){
									if(timeHolder != write->getPROC()){
										std::cout << " " << write->getPROC();
									}
								}
								std::cout<< "]" << std::endl;
							}
							else{
								std::cout <<"time " << counter << "ms: Process "<< it->getPROC() << " arrived and added to ready queue [Q";
								std::vector<Process>::iterator write = readyQueue.begin();
								if(write == readyQueue.end()){
									std::cout << " <empty>";
								}
								for(write = readyQueue.begin(); write != readyQueue.end(); write++){
									if(timeHolder != write->getPROC()){
										std::cout << " " << write->getPROC();
									}
								}
								std::cout<< "]" << std::endl;
								it->setARRIVED();
							}
						}
						else{
							if(it->hasARRIVED()){
								std::cout <<"time " << it->getNewTime() << "ms: Process "<< it->getPROC() << " completed I/O and will preempt ";
								std::cout << timeHolder << " [Q";
								std::vector<Process>::iterator write = readyQueue.begin();
								if(readyQueue.size() == 2){
									std::cout<< " <empty>";
								}
								for(write = readyQueue.begin(); write != readyQueue.end(); write++){
									if(timeHolder != write->getPROC() && it->getPROC() != write->getPROC()){
										std::cout << " " << write->getPROC();
									}
								}
								std::cout<< "]" << std::endl;
								preempted = true;
								preemptions++;
							}
							else{
								std::cout <<"time " << counter << "ms: Process "<< it->getPROC() << " arrived and will preempt ";
								std::cout << timeHolder << " [Q";
								std::vector<Process>::iterator write = readyQueue.begin();
								if(readyQueue.size() == 2){
									std::cout << " <empty>";
								}
								for(write = readyQueue.begin(); write != readyQueue.end(); write++){
									if(timeHolder != write->getPROC() && it->getPROC() != write->getPROC()){
										std::cout << " " << write->getPROC();
									}
								}
								std::cout<< "]" << std::endl;
								it->setARRIVED();
								preempted = true;
								preemptions++;
							}
						}
					}
				}
			}
			else{
				it->subINIT();
			}
		}
		//CPU BURST
		std::vector<Process>::iterator holder;
		if(preempted){
			for(holder = readyQueue.begin(); holder != readyQueue.end(); holder++){
				if(holder->getPROC() == timeHolder){
					holder->setPre(true);
				}
			}
			preempted = false;
		}
		
		holder = readyQueue.begin();
		if(holder != readyQueue.end()){
			if(timeHolder == '^'){
				timeHolder = holder->getPROC();
				t_cs += 4;
				context_switch++;
				std::cout <<"time " << t_cs << "ms: Process "<< holder->getPROC() << " started using the CPU ";
				if(holder->isPreempted()){
					std::cout << "with " << holder->getCPU() << "ms remaining ";
					holder->setPre(false);
				}
				std::cout<< "[Q";
				std::vector<Process>::iterator write = readyQueue.begin();
				if(write == readyQueue.end()){
					std::cout << " <empty>";
				}
				for(write = readyQueue.begin(); write != readyQueue.end(); write++){
					if(timeHolder != write->getPROC()){
						std::cout << " " << write->getPROC();
					}
					else if(readyQueue.size() == 1){
						std::cout << " <empty>";
					}
				}
				std::cout<< "]" << std::endl;
			}
			else if(timeHolder != holder->getPROC()){
				timeHolder = holder->getPROC();
				context_switch++;
				t_cs += 4;
				std::cout <<"time " << t_cs << "ms: Process "<< holder->getPROC() << " started using the CPU ";
				if(holder->isPreempted()){
					std::cout << "with " << holder->getCPU() << "ms remaining ";
					holder->setPre(false);
				}
				std::cout<< "[Q";
				std::vector<Process>::iterator write = readyQueue.begin();
				if(write == readyQueue.end()){
					std::cout << " <empty>";
				}
				for(write = readyQueue.begin(); write != readyQueue.end(); write++){
					if(timeHolder != write->getPROC()){
						std::cout << " " << write->getPROC();
					}
					else if(readyQueue.size() == 1){
						std::cout << " <empty>";
					}
				}
				std::cout<< "]" << std::endl;
			}
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
								std::cout << " <empty>";
							}
							for(write = readyQueue.begin(); write != readyQueue.end(); write++){									
								if(timeHolder != write->getPROC()){
									std::cout << " " << write->getPROC();
								}
								else if(readyQueue.size() == 1){
									std::cout << " <empty>";
								}
							}
							std::cout<< "]" << std::endl;
							t_cs += 3;
							waits.push_back(finder->getWait());
							turnarounds.push_back(finder->getWait() + finder->getCPUReplace() + 8);							
							processes.erase(finder);  //if those are the same, erase 
							break;
						}
					}
					readyQueue.erase(holder);
				}
				else{
					std::cout <<"time " << t_cs << "ms: Process "<< holder->getPROC() << " completed a CPU burst; " << holder->getNUM() - 1;
					if(holder->getNUM() - 1 == 1){
						std::cout << " burst to go [Q";
					}
					else{
						std::cout << " bursts to go [Q";
					}
					std::vector<Process>::iterator write = readyQueue.begin();
					if(write == readyQueue.end()){
						std::cout << " <empty>";
					}
					for(write = readyQueue.begin(); write != readyQueue.end(); write++){
						if(timeHolder != write->getPROC()){
							std::cout << " " << write->getPROC();					
						}
						else if(readyQueue.size() == 1){
							std::cout << " <empty>";
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
							break;
						}
					}
					write = readyQueue.begin();
					std::cout <<"time " << t_cs << "ms: Process "<< holder->getPROC() << " switching out of CPU; will block on I/O until time " << temp + 4 << "ms [Q";
					if(write == readyQueue.end()){
						std::cout << " <empty>";
					}
					for(write = readyQueue.begin(); write != readyQueue.end(); write++){
						if(timeHolder != write->getPROC()){
							std::cout << " " << write->getPROC();
						}
						else if(readyQueue.size() == 1){
							std::cout << " <empty>";
						}
					}
					std::cout<< "]" << std::endl;
					t_cs += 3;
					finder->setNewTime(temp + 4);
					timeHolder = '^';
					readyQueue.erase(holder);
				}
			}
		
		}
		t_cs ++;
		counter += 1;
		if(processes.size() == 0){
			std::cout <<"time " << t_cs << "ms: Simulator ended for SRT" << std::endl;
			end = true;
		}
	}
	
	for(unsigned int i = 0; i < waits.size(); i++){
		init_average += waits[i];
	}
	init_average /= waits.size();
	
	for(unsigned int i = 0; i < turnarounds.size(); i++){
		turn_avg += turnarounds[i];
	}
	turn_avg /= turnarounds.size();
	
	fout << std::fixed;
	fout << "Algorithm SRT" << std::endl;
	fout << "-- average CPU burst time: " << std::setprecision(2) << CPU_average << " ms" << std::endl;
	fout << "-- average wait time: " << std::setprecision(2) << init_average << " ms" << std::endl;
	fout << "-- average turnaround time: " << std::setprecision(2) << turn_avg << " ms" << std::endl;
	fout << "-- total number of context switches: " << context_switch << std::endl;
	fout << "-- total number of preemptions: " << preemptions << std::endl;
}

void RoundRobin(std::vector<Process> processes, std::ofstream &fout){
	
	double CPU_average = 0;
	for (unsigned int i = 0; i < processes.size(); i++){
		CPU_average += double(processes[i].getCPU());
	}
	CPU_average = CPU_average/double(processes.size());

	double init_average = 0;
	for (unsigned int i = 0; i < processes.size(); i++){
		init_average += double(processes[i].getINIT());
	}
	init_average = init_average/double(processes.size());

	int context_switch = 0;
	int preemptions = 0;
	
	float turn_time = CPU_average + init_average + 8;
		
	int time = 0;
	std::vector<Process> readyQueue;
	int t_slice = 70;
	std::vector<char> already_added;
	char current = '^';

	std::vector<Process>::iterator finder;
	bool previously_in_queue;

	int add_remove_time = 0;
	bool done_a_r = true;

	bool terminate = false;

	bool already_going = false;

	std::cout << "time 0ms: Simulator started for RR [Q <empty>]" << std::endl;
	while (time >= 0){
		//Check to see if processes is empty, if so, break the loop and return
		
		if (processes.size() == 0){
			break;
		}
		
		if (readyQueue.size() == 0){
			current = '^';
		}
		//Check if the current process is done and needs to do another burst, if there's another process, start on it.
		
		if (readyQueue.size() != 0){
			if (readyQueue[0].getCPU() <= 0){
				t_slice = 70;
				if (readyQueue[0].getNUM() == 1){
				//remove from the readyQueue, and remove the process for good from processes
					for (finder = processes.begin(); finder != processes.end(); finder++){
						if (finder->getPROC() == readyQueue[0].getPROC()){
							processes.erase(finder);
							break;
						}	
					}

					std::cout << "time " << time << "ms: Process " << readyQueue[0].getPROC() << " terminated " << queue(readyQueue, current) << std::endl;
					
					readyQueue.erase(readyQueue.begin());

				}
				else if(readyQueue[0].getNUM() > 1){
					//process still needs to go through more bursts, removes it from queue anyways
					for (finder = processes.begin(); finder != processes.end(); finder++){
						if(finder->getPROC() == readyQueue[0].getPROC()){
							finder->subNUM();
							finder->new_INIT(time+4);
							break;
						}
					}	
					readyQueue.erase(readyQueue.begin());

					std::cout << "time " << time << "ms: Process " << finder->getPROC() << " completed a CPU burst; " << finder->getNUM() << (finder->getNUM()  == 1 ? " burst" : " bursts") << " to go " << queue(readyQueue, current) << std::endl;

						std::cout << "time " << time << "ms: Process " << finder->getPROC() << " switching out of CPU; will block on I/O until time " <<  finder->getINIT() << "ms " << queue(readyQueue, current) << std::endl;
					
				}
				
				if (readyQueue.size() != 0){
					current = readyQueue.begin()->getPROC();
				}
				terminate = true;
			}

		}

		//Add process to queue if its init_time = to the current time;
		for(std::vector<Process>::iterator it = processes.begin(); it != processes.end(); it++){		//Same as FCFS
			if(it->getINIT() == time){															//Adds the process when the join time matches
				bool found = false;
				for(std::vector<Process>::iterator check = readyQueue.begin(); check != readyQueue.end(); check++){	
					if(it->getPROC() == check->getPROC()){
						found = true;
					}
				}
				if(found == false){
					readyQueue.push_back(*it);
					//std::cout << it->getCPU() << std::endl;
					previously_in_queue = false;
					for (std::vector<char>::iterator it2 = already_added.begin(); it2 != already_added.end(); it2++){
						if (*it2 == it->getPROC()){
							std::cout << "time " << time << "ms: Process " << it->getPROC() << " completed I/O; added to ready queue " << queue(readyQueue, current) << std::endl;
							previously_in_queue = true;
						}
					}

					if (previously_in_queue == false){
						std::cout << "time " << time << "ms: Process " << it->getPROC() << " arrived and added to ready queue " << queue(readyQueue, current) << std::endl;
						already_added.push_back(it->getPROC());
					}
				}
				
				if (readyQueue.size() == 1){
					t_slice = 70;
				}

				already_going = false;
			
			}
		}

		//if a process starts on the ready queue with at t_slice of 70, get started


		if (terminate){
			done_a_r = false;
			if (add_remove_time == 4 && done_a_r == false){
				done_a_r = true;
				add_remove_time = 0;
			}else if(add_remove_time < 4 && done_a_r == false){
				add_remove_time++;
				time++;
				continue;
			}
			terminate = false;
			
		}

		//Check to see if t_slice is 0, means that the timeslice is over and next in queue should be given a timeslice of 70.
		if (t_slice == 0){
			if (readyQueue.size() > 1 ){
				done_a_r = false;
				if (add_remove_time == 4 && done_a_r == false){
					done_a_r = true;
					add_remove_time = 0;
				}else if(add_remove_time < 4 && done_a_r == false){
					add_remove_time++;
					time++;
					continue;
				}
			
				t_slice = 70;
				preemptions++;
				std::cout << "time " << time - 4 << "ms: Time slice expired; process " << readyQueue[0].getPROC() << " preempted with " << readyQueue[0].getCPU() << "ms to go " << queue(readyQueue, current) << std::endl;
			already_going = false;
			readyQueue.push_back(*readyQueue.begin());
			readyQueue.erase(readyQueue.begin());
			}else if (readyQueue.size() == 1){
				t_slice = 70;
				already_going = true;
				std:: cout << "time " << time << "ms: Time slice expired; no preemption because ready queue is empty " << queue(readyQueue, current) << std::endl;
			}
			
		}

		if (t_slice == 70 && readyQueue.size() != 0 && !already_going){
			current = readyQueue[0].getPROC();
			

			done_a_r = false;
			if (add_remove_time == 4 && done_a_r == false){
				done_a_r = true;
				add_remove_time = 0;
			}else if(add_remove_time < 4 && done_a_r == false){
				add_remove_time++;
				time++;
				continue;
			}
			

			if (readyQueue[0].getCPU() != readyQueue[0].get_replaceCPU()){
				context_switch += 1;
				std::cout << "time " << time << "ms: Process " << readyQueue[0].getPROC() << " started using the CPU with " << readyQueue[0].getCPU() << "ms remaining " << queue(readyQueue, current) << std::endl;
			}else{
				context_switch += 1;
				std::cout << "time " << time << "ms: Process " << readyQueue[0].getPROC() << " started using the CPU " << queue(readyQueue, current) << std::endl;
			}
		}

		
		//If everything else checks out, decrease 1 from timeslice and add 1 to time		
		if (readyQueue.size() != 0){
			t_slice--;
			readyQueue[0].subCPU();
			time++;
		}else{
			t_slice--;
			time++;
		}
		
	}

	std::cout << "time " << time +3 << "ms: Simulator ended for RR" << std::endl;


	
	fout << std::fixed;
	fout << "Algorithm RR" << std::endl;
	fout << "-- average CPU burst time: " << std::setprecision(2) << CPU_average << " ms" << std::endl;
	fout << "-- average wait time: " << std::setprecision(2) << init_average << " ms" << std::endl;
	fout << "-- average turnaround time: " << std::setprecision(2) << turn_time << " ms"  << std::endl;
	fout << "-- total number of context switches: " << context_switch << std::endl;
	fout << "-- total number of preemptions: " << preemptions << std::endl;
}



int main(int argc, char* argv[]){
	//argv[1] should be the input file, and (i think?) argv[2] should be output file
	
	std::ifstream input( argv[1] );
	std::ofstream output( argv[2] );
	std::vector<Process> processes;
	for (std::string line; getline (input, line); ){
		if (line[0] == '#' || line[0] == '\n' || line[0] == ' ' || line.size() == 0){
			continue;
		}else{

			char PROC;
			int INIT;
			int CPU;
			int NUM;
			int IO;
			
			std::vector<char> arr;
			
			PROC = line[0];
			unsigned int i = 2;

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
	
	std::vector<Process> fcfs = processes;	//temp is a copy of processes, idk if this actually matters, but whatever
	std::vector<Process> SRT = processes;
	std::vector<Process> RR = processes;
	FCFS(fcfs, output);	//goes through first come first serve
	std::cout<<std::endl;
	ShortestRemainingTime(SRT, output);
	std::cout<<std::endl;
	RoundRobin(RR, output);

	output.close();
	
	
	//something something output file idk
}
