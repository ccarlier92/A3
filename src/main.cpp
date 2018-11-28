#include <iostream>
#include "parser.h"
#include "connector.cpp"
#include "command.cpp"
#include "and.cpp"
#include "or.cpp"
#include "semiColon.cpp"
#include "prompt.h"
#include "parenthesis.cpp"
#include "testCommand.cpp"

int  main()
{
	int result = 0;
	while (result == 0)
	{	
		std::string command ="";
		prompt();
		std::getline(std::cin,command);
		
		Base * res;

		//Call the tokenizer class
		typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

		boost::char_separator<char> delimiters(" ","&|;#()");	/*The blank will disappear in the parsed result but '&','|',';',and '#' will be keeped as token*/
		tokenizer tokens(command,delimiters);		//split into tokens
		
		Base * new_base = Parse(tokens, tokens.begin(),false);
		if(new_base != NULL)
		{
			bool res = new_base->execute();
		}
	}
	return 0; 
}
