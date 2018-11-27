
#include "testCommand.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

bool Test::execute()
{
  bool res = false;
  struct stat buffer;   
	if(args[2] == NULL || (is_flag(args[1]) && args[1] == "-e"))
	{
		if(stat(args[1], &buffer) == 0)
		{
		       res = true;
		}  
	}
	else
	{
		if(is_flag(args[1]))
		{
			if(args[1] == "-d")
			{
				res = S_ISDIR(buffer.st_mode);
			}

			else if(args[1] == "-f")
			{
				res = S_ISREG(buffer.st_mode);
			}

			else
			{
				
				std::cout<<"Invalid input"<<std::endl<<args[1]<<std::endl;
			}  
		}
	}
	if(res == true)
	{
		std::cout<<"(TRUE)"<<std::endl;
	}
	else
	{
		std::cout<<"(FALSE)"<<std::endl;
	}

	return(res);
}

bool Test::is_flag(char* value)
{
	bool res = false;
	if(value != NULL)
	{
		std::cout <<std::endl<<value[0]<<std::endl;
	  	if(value[0] == '-')
		{
			res = true;
		}
	}
	if(res==false)
	{
		std::cout<<value<<" is not a flag"<<std::endl;
	}
	else
	{
		std::cout<<value<<" is a flag"<<std::endl;
	}
  	return res;
}
