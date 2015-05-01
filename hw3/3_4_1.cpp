#include <iostream>
#include <deque>
#include <string>
#include <cctype>
#include "3_4_1_container.h"
#include "3_4_1_func.h"

using namespace std;

int main()
{
	string input = "";
	while(getline(cin,input)){
		int value;
		newStack optr_con;
		newStack oprd_con;
		intStack result; //stack用來算結果的
		in2post(optr_con, oprd_con, input);
		//show postfix expression
		printf("Postfix Exp: ");
		for(deque<string>::iterator i=oprd_con.begin(); i!=oprd_con.end(); ++i)
		{
			if(*i=="p")
				cout << "+" << " ";
			else if(*i=="m")
				cout << "-" << " ";
			else
				cout << *i << " ";
	
		}
		printf("\n");
		//show result
		printf("RESULT: ");
		value = caculate_pstfix(result , oprd_con);
		printf("%d", value);
		printf("\n");
 	}
}