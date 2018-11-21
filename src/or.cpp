#include "or.h"

bool Or::execute(){

 	if (this->previous->execute())
		return(false);
	else
		return(this->next->execute());
}


void Or::print_args()
{
	this->previous->print_args();
	std::cout<<" || ";
	this->next->print_args();
}
