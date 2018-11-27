
#include "testCommand.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

bool Test::execute()
{
  bool res = false;
  struct stat buffer;   
  
  if(is_flag(this->args[0]) == false || this->args[0] == "-e")
  {
    res = stat(this->args[1].c_str(), &buffer) == 0;
  }
  
  else if(this->args[0] == "-d")
  {
    res = S_ISDIR(buffer->st_mode);
  }
  
  else if(this->args[0] == "-f")
  {
    res = S_ISREG(buffer->st_mode);
  }
  
  else
  {
     std::cout<<"Invalid input"<<std::endl;
     return(false);
  }
  
std::cout<<"("<<res<<")"<<std::endl;
return(res);
}

bool Test::is_flag(char* value)
{
	bool res = false;
	if(value != NULL)
	{
	  if( value[0] == '-')
		{
			res = true;
		}
	}
  return res;
}
