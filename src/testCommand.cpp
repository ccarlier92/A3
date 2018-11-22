#include "testCommand.h"
#include <sys/stat.h>
#include <filesystem>

namespace fs = std::filesystem

bool Test::execute()
{
  bool res = false;
  
  if(this->args[0] == NULL || this->args[0] == "-e")
  {
    struct stat buffer;   
    res = stat(this->args[1].c_str(), &buffer) == 0;
  }
  
  else if(this->args[0] == "-d")
  {
    res = fs::is_directory(fs::status(this->args[1]));
  }
  
  else if(this->args[0] == "-f")
  {
    res = fs::is_regular_file(fs::status(this->args[1]));
  }
  
  else
  {
     std::cout<<"Invalid input"<<std::endl;
    return(false);
  }
  
std::cout<<"("<<res<<")"<<std::end;
return(res);
}
