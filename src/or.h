#ifndef OR_H
#define OR_H

#include "connector.h"

class Or : public Connector{
	
	private:
		Base * previous;
		Base * next;
	
	public :
		Or():Connector(){};
		bool execute();
		void print_args();
};

#endif
