#include "parenthesis.h"

bool Parenthesis::execute(){
	this->child->execute();
}


void Parenthesis::print_args()
{
	std::cout<<" ( ";
  this->next->print_args()
  std::cout<<" )";
}
