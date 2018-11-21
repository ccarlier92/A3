#include "semiColon.h"

bool SemiColon::execute(){

	if(this->next)
		this->previous->execute();
		this->next->execute();
}


void SemiColon::print_args()
{
	this->previous->print_args();
	std::cout<<" ; ";
	this->next->print_args();
}
