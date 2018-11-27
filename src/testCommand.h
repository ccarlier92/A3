#ifndef TESTCOMMAND_H
#define TESTCOMMAND_H

#include "command.h"

class Test : public Command{
	public :
		Test(std::vector<std::string> args):Command(args){};
		bool execute();
		bool is_flag(std::string arg);
};

#endif
