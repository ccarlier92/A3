#ifndef AND_H
#define AND_H


#include "connector.h"

class And : public Connector{
	private:
	
		Base * previous;
		Base * next;
	
	public :
		And():Connector(){};
		bool execute();
		void print_args();
};

#endif
