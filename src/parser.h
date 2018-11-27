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

Base * Parse_It(boost::tokenizer<boost::char_separator<char> > commands , boost::tokenizer<boost::char_separator<char> >::iterator it, bool in_parenthesis)
{
	//The base that will be returned	
	Base * res;
	
	std::vector<Base*> vect_commands;
	std::vector<Connector*> vect_connectors;
	
	bool valid_connector = true;		//Check if there are 2 characters for && and ||
	
	while( it != commands.end() && !(in_parenthesis && *it == ")"))				//Start parsing
	{
		if(in_parenthesis)
		{
			std::cout<<"Start Loop"<<std::endl;
		}
		
		vect_commands.push_back(Parse_commands(commands,it);
		/*std::vector<std::string> args;
		bool is_exit = false;			//Check if the command is exit or not
		
		//This loop gets a command, the executable and its arguments
		while((it != commands.end()) && ( *it != "&" && *it != "|" && *it != ";" && *it != "#" && *it != "("  && *it != ")" && *it != [ ))
		{
			args.push_back(*it);
			if(*it == "exit" )	//if it is an exit command
			{
				is_exit = true;
			}
			it++;
		}
		if(args.size() != 0)			//Check if it was not a single command or not
		{
			Command * command;
			if(is_exit == true)
			{
				command = new Exit(args);	
			}
			else
			{
				command = new Command(args);
				//command->print_args();
			}
			vect_commands.push_back(command);	//add the command to the vector
		}*/

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
				vect_commands.push_back(Parse_test(commands,it));
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
					Base * parenthesis = new Parenthesis(Parse_It(commands,it,true));
					vect_commands.push_back(parenthesis);
				}
				it++;
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
			std::cout<<"connectors "<<vect_connectors.size() <<std::endl;
			std::cout<< "commands "<<vect_commands.size()<<std::endl;
			/*for(int i=0;i< vect_commands.size();i++)
			{
				vect_commands[i]->print_args();
			}*/
		}
		else if(valid_connector == false)
		{
			std::cout<<"Invalid Connector"<<std::endl;
		}
	}
	return res;
}
				   
				   
Base * Parse_command (boost::tokenizer<boost::char_separator<char> > commands , boost::tokenizer<boost::char_separator<char> >::iterator it)
{				   
	std::vector<std::string> args;
	bool is_exit = false;			//Check if the command is exit or not
	bool is_test = false;
	//This loop gets a command, the executable and its arguments
	while((it != commands.end()) && ( *it != "&" && *it != "|" && *it != ";" && *it != "#" && *it != "("  && *it != ")" && *it != [ ))
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
		Command * command;
		if(is_exit == true)
		{
			command = new Exit(args);	
		}
		else if (is_test == true)
		{
			command = new Test(args);
		}
		else
		{
			command = new Command(args);
			//command->print_args();
		}
	}
	return command;	
}
				   
Base * Parse_test(boost::tokenizer<boost::char_separator<char> > commands , boost::tokenizer<boost::char_separator<char> >::iterator it)
{	
	it++;
	std::vector<std::string> args;
	while(it != commands.end() && *it != ])
	{
		args.push_back(it);
		it++;
	}
	Base * test = new Test(args);
	return test;
}

bool is_flag(std::string value)
{
	bool res = false;
	if(value.empty() == false)
	{
		if(value.size() == 2 && value[0] =="-")
		{
			res= true;
		}
	}
}
/*Base * Parse(std::string command_line)
{
	//The base that will be returned	
	Base * res;

	//Call the tokenizer class
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

	boost::char_separator<char> delimiters(" ","&|;#");	/The blank will disappear in the parsed result but '&','|',';',and '#' will be keeped as token
	tokenizer tokens(command_line,delimiters);		//split into tokens
	
	//To store the commands and connectors
	std::vector<Command*> vect_commands;
	std::vector<Connector*> vect_connectors;
	
	tokenizer::iterator it = tokens.begin();
	
	bool valid_connector = true;		//Check if there are 2 characters for && and ||
	
	while( it != tokens.end())				//Start parsing
	{
		std::string actual_token = *it;	
		std::vector<std::string> args;
		bool is_exit = false;			//Check if the command is exit or not
		
		//This loop gets a command, the executable and its arguments
		while((it != tokens.end()) && (( actual_token != "&") && (actual_token != "|") && (actual_token != ";") && (actual_token != "#")))
		{
			args.push_back(actual_token);
			if(actual_token == "exit" )	//if it is an exit command
			{
				is_exit = true;
			}
			it++;
			if(it != tokens.end())
			{
				actual_token = *it;
			}
		}
		if(args.size() != 0)			//Check if it was not a single command or not
		{
			Command * command;
			if(is_exit == true)
			{
				command = new Exit(args);	
			}
			else
			{
				command = new Command(args);
			}
			vect_commands.push_back(command);	//add the command to the vector
		}


		if(it != tokens.end())
		{
			//When a connector or comment token is reached
			if(actual_token == "#")
			{
				//Don't need what's next so break
				break;
			}
			
			//if it is a connector ==> create it
			//add it to the vector
			//if & or | conectors, go to next iterator which will end up being skipped
			if(actual_token == "&")
			{	
				it++;
				if (it == tokens.end())
				{
					valid_connector = false;
					break;
				}
				else if (actual_token != *it)
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
			else if(actual_token == "|")
			{
				it++;
				if (it == tokens.end())
				{
					valid_connector = false;
					break;
				}
				else if (actual_token != *it)
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
			else if(actual_token == ";")
			{
				Connector * connector = new SemiColon();
				vect_connectors.push_back(connector);
			}			
		}	
			
		if(it != tokens.end())
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
}*/

