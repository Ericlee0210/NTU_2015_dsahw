#include <iostream>
#include <deque>
#include <string>
#include <cctype>
#include <cmath>
#include "3_4_2_func.h"
using namespace std;
string c2str(const char & a)
{
	string tmp(1,a);
	return tmp;
}

bool isoperator(const char & a)
{
	if( a=='s' || a=='c' || a=='e' ||
	    a=='l' || a=='p' || a=='f' ||
	    a=='+' || a=='-' || a=='*' || a==','  )
		return true;
	else
		return false;
}

int precedence(const string & a) //判斷該運算子優先順序
{
	if (a==",")
		return 1;
	else if (a == "+"  || a == "-")
		return 7;
	else if (a == "*" )
		return 8;
	else if (a == "p" || a == "m")
		return 9;
	else if( a == "sin"  || a == "cos"  ||
	 	     a == "exp"  || a == "log"  ||
	 	     a == "pow"  || a == "sqrt" ||
	 	     a == "fabs")
		return 10;
	else 
		return 0;
}

void push2Stack(newStack & x, const string & tmp)
{
	x.push_back(tmp);
}

void moveFromStack2Output(newStack & optr_con, newStack & oprd_con)
{
	//put them into oprd_con and clean optr_con
	oprd_con.push_back( optr_con.back() );
	optr_con.pop_back();
}

void show(newStack & optr_con, newStack & oprd_con) //將目前stack與output內容顯示出來
{
	printf("Output: ");
	for(deque<string>::iterator i=oprd_con.begin(); i!=oprd_con.end() ; ++i)
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
	printf("Stack: ");
	for(deque<string>::iterator i=optr_con.begin(); i!=optr_con.end() ; ++i)
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
}

void compare(newStack & optr_con, newStack & oprd_con,  const std::string & tmp) //比較優先順序
{
	if( precedence(optr_con.back())==9 && precedence(tmp)==9 )
		return;
	while( !optr_con.empty() &&  ( precedence(optr_con.back()) >= precedence(tmp) ) )
	{
		//printf("moving element from stack to ouput...\n");
		moveFromStack2Output(optr_con, oprd_con);
		show(optr_con, oprd_con);
	}
}

string makeDigit(unsigned int & i, const string & input)
{
	string tmp = c2str( input[i] );
	while( isdigit( input[i+1] ) ){   //掃到小數點為止
		i++;
		char it = input[i];
		string tmp2(1,it);
		tmp+=tmp2;
	}
	if(input[i+1]=='.')
	{
		i++;
		char it = input[i];
		string tmp2(1,it);
		tmp+=tmp2;
		while(isdigit(input[i+1]))
		{
			i++;
			char d = input[i];
			string tmp3(1,d);
			tmp+=tmp3;
		}
	}
	return tmp;
}

void check(newStack & optr_con, newStack & oprd_con,  std::string & tmp)
{
	if(!optr_con.empty())
	{
		//printf("check stack.top() whether is higher than the operator I got\n");
		compare(optr_con, oprd_con, tmp);
		//printf("checking is over!\n");
		if(tmp!=",")
			push2Stack(optr_con, tmp);
		show(optr_con, oprd_con);
	}
	else
	{
		push2Stack(optr_con, tmp);
		show(optr_con, oprd_con);
	}
}
void in2post(newStack & optr_con, newStack & oprd_con, const string & input) //將infix轉換為postfix
{
	for(unsigned int i=0; ;i++)
	{
		//掃每個字元
		//cout << "i = " << i << endl;
		char it = input[i];
		if(i==input.size())
		{
			//printf("at the end of string...\n");
			while(!optr_con.empty())
			{
				//printf("copy stack's element to output, and pop them\n");
				moveFromStack2Output(optr_con, oprd_con);
				show(optr_con, oprd_con);
			}
			break;
		}
		else if( isspace(it))
		{
			continue;
		}
		else if(it=='(')
		{
			string tmp = c2str(it);
			push2Stack(optr_con, tmp);
		}
		else if(it==')')
		{
			while(optr_con.back()!="(")
			{
				//printf("paranthesis get! Moveing element from stack to output\n");
				moveFromStack2Output(optr_con, oprd_con);
				show(optr_con, oprd_con);
			}
			optr_con.pop_back(); //刪除'('
		}
		else if( isdigit(it) )
		{
			string tmp = makeDigit(i, input); //產生數字
			//cout << "Now, I got " << tmp << endl;   //顯示目前遇到啥數字
			push2Stack(oprd_con, tmp);          //放進入oprd_con
			show(optr_con, oprd_con); 
		}
		else if( isoperator(it) )
		{
			if( it=='+' || it=='-' )
			{
				bool flag; 
				string tmp; //operator
				if(it=='+') flag=1; else flag=0; //判斷是+還是-
				if(i==0) //一開始就是unary + / -
				{
					if(flag)
					{
						tmp = c2str('p');
						//cout << "Now, I got " << '+' << endl;
					}
					else
					{
						tmp = c2str('m');
						//cout << "Now, I got " << '-' << endl;
					}
					push2Stack(optr_con, tmp);
				}
				else
				{
					int cnt = i-1;
					while(isspace(input[cnt]))
						cnt--;
					if( !( isdigit( input[cnt] ) || input[cnt]==')' ) ) //unary
					{
						if(flag)
						{
							tmp = c2str('p');
							//cout << "Now, I got " << '+' << endl;
						}
						else
						{
							tmp = c2str('m');
							//cout << "Now, I got " << '-' << endl;
						}
						//若stack不是空的則要小心，要看看是否把stack element倒出來
						check(optr_con, oprd_con, tmp);
					}
					else
					{
						tmp = c2str(it);
						//cout << "Now, I got " << tmp << endl;
						//若stack不是空的則要小心，要看看是否把stack element倒出來
						check(optr_con, oprd_con, tmp);
					}
				}
			}
			else if( it=='*' )
			{
				string tmp = c2str(it);
				check(optr_con, oprd_con, tmp);
			}
			else if(it==',')
			{
				string tmp = c2str(it);
				check(optr_con, oprd_con, tmp);
			}
			else if( it=='s' || it=='c' || it=='e' || it=='l' || it=='p' || it=='f' )
			{
				string tmp = c2str(it);
				while(!isspace(input[i+1]) && input[i+1]!='(' )
				{
					i++;
					string tmp2 = c2str(input[i]);
					tmp+=tmp2;
				}
				check(optr_con, oprd_con, tmp);
			}
		}
	}
}

double caculate_pstfix(dStack& result, newStack & oprd_con)
{
	for(newStack::iterator i=oprd_con.begin(); i!=oprd_con.end(); ++i)
	{
		if( isdigit( i->at(0) ) )
		{
			double value = stod(*i);    //將srt轉為數字
			result.push_back(value); //將數字放到stack
		}
		else
		{
			if( *i=="p" || *i==",")
			{
				continue;
			}
			else if( *i=="m" )
			{
				double tmp = result.back();
				tmp = -(tmp);
				result.pop_back();    //把result.back() pop掉
				result.push_back(tmp);//再放回去數字
			}	
			else if( *i=="+")
			{
				double tmp = result.back();
				result.pop_back();
				double tmp2 = result.back();
				result.pop_back();
				double newTmp = (tmp2+tmp);
				result.push_back(newTmp);
			}
			else if( *i=="-")
			{
				double tmp = result.back();
				result.pop_back();
				double tmp2 = result.back();
				result.pop_back();
				double newTmp = (tmp2-tmp);
				result.push_back(newTmp);
			}
			else if( *i=="*")
			{
				double tmp = result.back();
				result.pop_back();
				double tmp2 = result.back();
				result.pop_back();
				double newTmp = (tmp2*tmp);
				result.push_back(newTmp);
			}
			else if( *i=="fabs")
			{
				double tmp = result.back();
				tmp = fabs(tmp);
				result.pop_back();
				result.push_back(tmp);
			}
			else if( *i=="pow")
			{
				double tmp = result.back();
				result.pop_back();
				double tmp2 = result.back();
				result.pop_back();
				double newTmp = pow(tmp2, tmp);
				result.push_back(newTmp);
			}
			else if( *i=="sqrt")
			{
				double tmp = result.back();
				result.pop_back();
				double newTmp = sqrt(tmp);
				result.push_back(newTmp);
			}
			else if( *i=="exp")
			{
				double tmp = result.back();
				result.pop_back();
				double newTmp = exp(tmp);
				result.push_back(newTmp);
			}
			else if( *i=="log")
			{
				double tmp = result.back();
				result.pop_back();
				double newTmp = log(tmp);
				result.push_back(newTmp);
			}
			else if( *i=="sin")
			{
				double tmp = result.back();
				result.pop_back();
				double newTmp = sin(tmp);
				result.push_back(newTmp);
			}
			else if( *i=="cos")
			{
				double tmp = result.back();
				result.pop_back();
				double newTmp = cos(tmp);
				result.push_back(newTmp);
			}
		}
	}
	return result.back();
}