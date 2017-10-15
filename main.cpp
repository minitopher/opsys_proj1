#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <string>
#include<cstdlib>

#include "process.h"

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
			int i = 3;

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
	std::cout << processes.size() << std::endl;
	
	//something something output file idk
}