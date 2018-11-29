#include "parenthesis.h"
#include <iostream>

bool Parenthesis::execute(){
	this->child->execute();
}


void Parenthesis::print_args()
{
	std::cout<<" ( ";
  	this->child->print_args();
  	std::cout<<" )";
}
