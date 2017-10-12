#include <iostream>
#include <vector>
#include <fstream>

#include "process.h"

int main(int argc, char* argv[]){
	//argv[1] should be the input file, and (i think?) argv[2] should be output file
	
	std::ifstream input( argv[1] );
	
	for (std::string line; getline (input, line); ){
		if (line[0] == '#'){
			continue;
		}else{
			//split that shit up by the | symbol, do some magic ass shit, and turn them into process objects.
		}
	}
	
	//something something output file idk
}