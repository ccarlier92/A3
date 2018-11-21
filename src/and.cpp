#include "and.h"

bool And::execute(){
	if(this->previous->execute())
	{
		return(this->next->execute());
	}
	else
		return (false);
}


void And::print_args()
{
	this->previous->print_args();
	std::cout<<" && ";
	this->next->print_args();
}
