#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include "raw_data.h"



void printf_data(data* ptr)
{
	std::cout << ptr->click << " ";
	std::cout << ptr->impression << " ";
	std::cout << ptr->displayURL << "\t";
	std::cout << ptr->adID<< "\t";
	std::cout << ptr->advertiseID << "\t";
	std::cout << ptr->depth << "\t";
	std::cout << ptr->position << "\t";
	std::cout << ptr->queryID << "\t";
	std::cout << ptr->keywordID << "\t";
	std::cout << ptr->titleID << "\t"; 
	std::cout << ptr->descriptionID << "\t"; 
	std::cout << ptr->userID << "\t";
	std::cout << std::endl;
}

bool data::operator ==(const data & b)
{
	if( strcmp(displayURL, b.displayURL)==0   &&
		advertiseID	  == b.advertiseID        &&
		keywordID  	  == b.keywordID          &&
		titleID    	  == b.titleID            &&
		descriptionID == b.descriptionID   )
		return true;
	else
		return false;
}
