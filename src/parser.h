#include "base.h"
#include "command.h"
#include "connector.h"
#include "and.h"
#include "or.h"
#include "semiColon.h"
#include "exit.h"
#include "exit.cpp"
#include "parenthesis.h"
#include "testCommand.h"

#include <boost/tokenizer.hpp>
#include <string>


Base * Parse(boost::tokenizer<boost::char_separator<char> > commands , boost::tokenizer<boost::char_separator<char> >::iterator it, bool in_parenthesis)
{
	//The base that will be returned	
	Base * res;
	
	std::vector<Base*> vect_commands;
	std::vector<Connector*> vect_connectors;
	
	bool valid_connector = true;		//Check if there are 2 characters for && and ||
	
	while( it != commands.end() && !(in_parenthesis && *it == ")"))				//Start parsing
	{
		
		
		//vect_commands.push_back(Parse_command(commands,it));
		//std::cout<<*it<<std::endl;
		std::vector<std::string> args;
		bool is_test = false;
		bool is_exit = false;			//Check if the command is exit or not
		
		//This loop gets a command, the executable and its arguments
		while((it != commands.end()) && ( *it != "&" && *it != "|" && *it != ";" && *it != "#" && *it != "("  && *it != ")" && *it != "[" ))
		{
			args.push_back(*it);
			if(*it == "exit" )	//if it is an exit command
			{
				is_exit = true;
			}
			else if(*it == "test" )	//if it is a test command
			{
				is_test = true;
			}
			it++;
		}

		if(args.size() != 0)			//Check if it was not a single command, a test, or an exit
		{
			Command *command;
			if(is_exit == true)
			{
				command = new Exit(args);	
			}
			else if (is_test == true)
			{
				std::cout<<"Test"<<std::endl;
				command = new Test(args);
			}
			else
			{
				command = new Command(args);
			}
			vect_commands.push_back(command);
		}

		if(it != commands.end() && !(in_parenthesis && *it == ")"))
		{
			//When a connector or comment token is reached
			if(*it == "#")
			{
				//Don't need what's next so break
				break;
			}
			
			if(*it == "[")
			{
				it++;
				std::vector<std::string> args;
				std::string test_arg = "test";
				args.push_back(test_arg);
				while(it != commands.end() && *it != "]")
				{
					args.push_back(*it);
					it++;
				}
				Base * test = new Test(args);
				test->print_args();
				std::cout<<"\n";
				vect_commands.push_back(test);
			}
			
			//if it is a connector ==> create it
			//add it to the vector
			//if & or | conectors, go to next iterator which will end up being skipped
			if(*it == "&")
			{	
				std::string prev_connector =*it;
				it++;
				if (it == commands.end() && !(in_parenthesis && *it == ")"))
				{
					valid_connector = false;
					break;
				}
				else if (prev_connector != *it)
				{
					valid_connector = false;
					break;
				}
				else
				{
					Connector * connector = new And();
					vect_connectors.push_back(connector);
				}
			}
			else if(*it == "|")
			{
				std::string prev_connector = *it;
				it++;
				if (it == commands.end() && !(in_parenthesis && *it == ")"))
				{
					valid_connector = false;
					break;
				}
				else if (prev_connector != *it)
				{
					valid_connector = false;
					break;
				}
				else
				{	
					Connector * connector = new Or();
					vect_connectors.push_back(connector);
				}
			}
			else if(*it == ";")
			{
				Connector * connector = new SemiColon();
				vect_connectors.push_back(connector);
			}	
			else if(*it == "(")
			{
				it++;
				if(it != commands.end())
				{
					std::cout<<"In Parenthesis"<<std::endl;
					Base * parenthesis = new Parenthesis(Parse(commands,it,true));
					parenthesis->print_args();
					int i =1;
					while ( i !=0)
					{
						it++;
						if ( *it == ")")
						{
						    i--;
						}
						else if (*it == "(")
						{
						    i++;
						}
					}
					std::cout<<"\n"<<*it<<std::endl;
					vect_commands.push_back(parenthesis);
				}
			}
		}		
		if(it != commands.end() && !(in_parenthesis && *it == ")"))
		{
			it++;
		}
	}
	
	//set the composite tree
	if ((vect_connectors.size()== (vect_commands.size()-1)) && (vect_commands.size()!=0) && (valid_connector == true))	//Check if the command line is a good input
	{ 
		if(vect_connectors.size()!=0) 	//means several commands
		{	
			for(int i = 0; i< vect_connectors.size(); i++)
			{
				//append the connectors to the right children (commands or connectors)
				if(i==0)
				{
					vect_connectors[i]->append(vect_commands[i],vect_commands[i+1]);
				}
				else
				{
					vect_connectors[i]->append(vect_connectors[i-1],vect_commands[i+1]);
				}
			}

			//return the connector on top of the tree, the last one
			res = vect_connectors[vect_connectors.size()-1];
		}
		else	//means one command
		{
			//return the only command
			res = vect_commands[0];
		}
	}
	else	//means the command line was inedaquate 
	{
		//return null
		res = NULL;
		if (vect_connectors.size()!= (vect_commands.size()-1))
		{
			std::cout<<"Invalid Input"<<std::endl;
			
		}
		else if(valid_connector == false)
		{
			std::cout<<"Invalid Connector"<<std::endl;
		}
	}
	return res;
}
				   
				  
