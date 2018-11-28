
#include "testCommand.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

bool Test::execute()
{
  	int res = -1;
  	struct stat buffer;   
	if(args[2] == NULL)
	{
		if(stat(args[1], &buffer) == 0)
		{
			res = 1;
		}  
		else
		{
			res =0;
		}
	}
	else
	{
		if(is_flag(args[1]))
		{
			int status = stat(args[2], &buffer);
			if(!strcmp(args[1],"-e"))
			{
				if(status == 0)
				{
					res =1;
				}
				else
				{
					res =0;
				}
			}
			else if(!strcmp(args[1],"-d"))
			{
				//std::cout<<"test if "<<args[2] <<" is a directory"<<std::endl;
				res = S_ISDIR(buffer.st_mode);
			}
			else if(!strcmp(args[1], "-f"))
			{
				//std::cout<<"test if "<<args[2] <<" is a file"<<std::endl;
				res = S_ISREG(buffer.st_mode);
			}
			else
			{
				std::cout<<"Invalid input"<<std::endl<<args[1]<<std::endl;
			}  
		}
	}
	//std::cout<<res<<std::endl;
	if(res == 0)
	{
		std::cout<<"(FALSE)"<<std::endl;
	}
	else if (res>0)
	{
		std::cout<<"(TRUE)"<<std::endl;
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
