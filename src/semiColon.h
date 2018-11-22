#ifndef SEMICOLON_H
#define SEMICOLON_H

#include "connector.h"

class SemiColon : public Connector{
	
	private:
		Base * previous;
		Base * next;

	public:
		SemiColon():Connector(){};
		bool execute();
		void print_args();
};

#endif

