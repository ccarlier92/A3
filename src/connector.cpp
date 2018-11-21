#include "connector.h"


void Connector::append(Base* previous, Base* next)
{
	this->previous = previous;
	this->next = next;
}
