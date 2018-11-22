#include "parenthesis.h"

bool Parenthesis::execute(){
	this->child->execute();
}


void And::print_args()
{
	std::cout<<" ( ";
  this->next->print_args()
  std::cout<<" )";
}
