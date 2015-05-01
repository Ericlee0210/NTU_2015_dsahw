#include <iostream>
#include <deque>
#include <string>
#include <cctype>
#include "3_4_2_container.h"
#include "3_4_2_func.h"

using namespace std;

int main()
{
	string input = "";
	while(getline(cin,input)){
		double value;
		newStack optr_con;
		newStack oprd_con;
		dStack result; //stack用來算結果的
		in2post(optr_con, oprd_con, input);
		//show postfix expression
		printf("Postfix Exp: ");
		for(deque<string>::iterator i=oprd_con.begin(); i!=oprd_con.end(); ++i)
		{
			if(*i=="p")
				cout << "+" << " ";
			else if(*i=="m")
				cout << "-" << " ";
			else if(isdigit(i->at(0)))
			{
				double tmp = stod(*i);
				printf("%.6f ", tmp);
			}
			else
				cout << *i << " ";
		}
		printf("\n");
		//show result
		printf("RESULT: ");
		value = caculate_pstfix(result , oprd_con);
		printf("%.6f", value);
		printf("\n");
 	}
}