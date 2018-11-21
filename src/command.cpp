#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include<sys/types.h> 
#include <stdio.h>

#include "command.h"

bool Command::execute()
{
	bool res = true;
	int status;
	pid_t end_pid;
	pid_t child_pid = fork();
	if (child_pid < 0)					//child process creation failed
	{
		perror("Fork Process Failed");
		return false;
	}
	else if (child_pid == 0)					//execute child process
	{	
		if(execvp(args[0],args) <0)			//execution failed
		{
			perror("Execution Failed");
			res = false;
			exit(EXIT_FAILURE);
		}
	}
	else 
	{							//wait for the child process to end
		if(waitpid(child_pid,&status,0)<0)
		{
			perror("Waitpid Failed");
			res = false;
			exit(1);
		}
		if(WIFEXITED(status) == true)
		{
			if(WEXITSTATUS(status) != 0)
			{
				res = false;
         	        }	
		}
	}
	return res;	
}
void Command::print_args()
{
	for (int i = 0; i< this->length  ; i++)
	{	
		if(i!= this->length - 1)
		{
			std::cout<< args[i]<<" ";
		}
		else
		{
			std::cout<< args[i];
		}
	}	 
}
