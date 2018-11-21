#ifndef EXIT_H
#define EXIT_H

#include "command.h"

class Exit : public Command{
	public :
		Exit(std::vector<std::string> args):Command(args){};
		bool execute();
};

#endif
