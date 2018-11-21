#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <iostream>

#include "base.h"

class Connector: public Base {
	protected :
		Base* previous;
		Base* next;

	public:
		Connector(): Base(){};
		virtual bool execute() =0;
		//virtual void print_args() =0;
		void append(Base * previous, Base * next);
};
#endif
