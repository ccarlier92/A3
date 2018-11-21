#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>
#include "base.h"
#include <iostream>

class Command : public Base{
	private:
		char ** args;
		int length;
	public :
		Command(std::vector<std::string> vect_args) : Base()
		{
			args = new char* [vect_args.size()+1];         // allocate memory space for the array
			int i= 0;
			for( i = 0;i<vect_args.size(); i++)            
			{
				args[i] = new char[vect_args[i].size()+1]; // allocate memory space for each char*
				vect_args[i].copy(args[i],vect_args[i].size(),0); //copy vect_args element into args
				args[i][vect_args[i].size()] = '\0'; 
			}
			args[i] = NULL; // add the null final element
			this->length = vect_args.size();		//doesn't take the NULL char*
		};
		bool execute();
		void print_args();
};

#endif
