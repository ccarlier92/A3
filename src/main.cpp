#include <iostream>
#include "parser.h"
#include "connector.cpp"
#include "command.cpp"
#include "and.cpp"
#include "or.cpp"
#include "semiColon.cpp"
#include "prompt.h"
int  main()
{
	int result = 0;
	while (result == 0)
	{	
		std::string command;
		prompt();
		std::getline(std::cin,command);
		
		Base * new_base = Parse(command);
		if(new_base != NULL)
		{
			bool res = new_base->execute();
		}
	}
	return 0; 
}
