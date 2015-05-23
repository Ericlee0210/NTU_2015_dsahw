#include <iostream>
#include <string>
#include <string.h>
#include "binomial_heap.h"

int main()
{
	unsigned long long int nmb_of_cmpr;
	unsigned long long int judging_parameter;
	std::cin >> nmb_of_cmpr >> judging_parameter;
	string cmd;

	while( getline( std::cin, cmd ) )
	{
		char* cstring, *tmp, *tmp2;
		cstring = new char[cmd.size()+1];
		strncpy(cstring, cmd.c_str(), cmd.size()+1);
		sscanf(cstring, "")

		tmp = strtok(cstring, " ");
		if( strcmp( tmp, "assign" )==0 )
		{
			unsigned long long int cm;
			unsigned long long int id;
			unsigned long long int p;
			tmp = strtok( NULL, "");
			sscanf(tmp, "%lld %lld %lld", cm , id, p);
			//執行assign related function			
		}
		else if( strcmp( tmp, "execute" )==0 )
		{
			unsigned long long int cm;
			tmp = strtok( NULL, "");
			sscnaf(tmp, "%lld", cm);
			//Computer cm executed task id.
		}
		else if( strcmp( tmp, "merge" )==0 )
		{
			unsigned cm1, cm2;
			tmp = strtok( NULL, "");
			sscanf(tmp, "%lld %lld", cm1, cm2);
			//執行merge funcion
		}
		delete[] cstring;
	}

	return;	
}
