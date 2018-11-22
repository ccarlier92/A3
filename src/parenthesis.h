#ifndef PARENTHESIS_H
#define PARENTHESIS_H

#include "base.h"

class Parenthesis : public Base{
  	private:
    		Base * child;
    
	public :
		Parenthesis(Base * child): child(child),Base(){};
		bool execute();
		void print_args();
};

#endif
