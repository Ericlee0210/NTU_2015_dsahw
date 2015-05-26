#include <iostream>
#include <cstdio>
#include <string>
#include <string.h>
#include "binomial_heap.h"


int main()
{
	
	l_int nmb_of_cmpr;
	l_int judging_parameter;

	scanf("%llu%llu", &nmb_of_cmpr, &judging_parameter);
	
	//printf("cms= %llu,  w=%llu\n", nmb_of_cmpr, judging_parameter);
	BinomialHeap<task>* ary[nmb_of_cmpr];
	for(l_int i=0; i<nmb_of_cmpr; i++) ary[i] = new BinomialHeap<task>;
	//*************//
	//很奇怪        //
	//*************//
	std::string cmd;
	getline(std::cin, cmd);

	while( getline(std::cin, cmd) )
	{
		char* cstring, *tmp;
		cstring = new char[cmd.size()+1];
		strncpy(cstring, cmd.c_str(), cmd.size()+1);
		//printf("cstring = %s\n", cstring);
		
		l_int cm ,cm2;
		l_int id;
		l_int p;

		tmp = strtok(cstring, " ");
		//printf("tmp= %s\n", tmp);
 		if( strcmp( tmp, "assign" )==0 )
 		{
			tmp = strtok( NULL, "");
			//printf("%s\n", tmp);
			sscanf(tmp, "%llu %llu %llu", &cm , &id, &p);
			//printf("cm= %llu, id= %llu, p= %llu\n", cm, id, p);
			task element(id, p);
			ary[cm]->insert(element);
			printf("There are %llu tasks on computer %llu.\n", ary[cm]->size, cm);
		}
		else if( strcmp( tmp, "execute" )==0 ){
			tmp = strtok( NULL, "");
			sscanf(tmp, "%llu", &cm);
			task element = ary[cm]->show_max_e();
			l_int max_p = element.p;
			while(ary[cm]->size > 0 && ary[cm]->show_max_e().p == max_p){
				task pop_e = ary[cm]->pop();
				printf("Computer %llu executed task %llu.\n", cm , pop_e.id );
			}
		}
		else if( strcmp( tmp, "merge" )==0 ){
			tmp = strtok( NULL, "");
			sscanf(tmp, "%llu %llu", &cm, &cm2);
			if(ary[cm2]->size >= judging_parameter){
				ary[cm]->merge( *(ary[cm2]) );
				printf("The largest priority number is now %llu on %llu.\n", ary[cm]->show_max_e().p, cm);
			}
			else
				printf("Merging request failed.\n");
		}
		delete[] cstring;
	}

	return 0;	
}
