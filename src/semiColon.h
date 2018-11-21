#ifndef SEMICOLON_H
#define SEMICOLON_H

#include "connector.h"

class SemiColon : public Connector{

	public:
		SemiColon():Connector(){};
		bool execute();
		void print_args();
};

#endif

