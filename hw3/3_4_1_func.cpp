#include <iostream>
#include <deque>
#include <string>
#include <cctype>
#include "3_4_1_func.h"
using namespace std;
string c2str(const char & a)
{
	string tmp(1,a);
	return tmp;
}

bool isoperator(const char & a)
{
	if( a=='*' || a=='/' || a=='%' ||
	    a=='+' || a=='-' || a=='&' ||
	    a=='^' || a=='|' || a=='<' ||
	    a=='>' || a=='(' || a==')' ||
	    a=='~' || a=='!'              )
		return true;
	else
		return false;
}

int precedence(const string & a) //判斷該運算子優先順序
{
	if (a == "||")
	  return 1;
	else if (a == "&&")
	  return 2;
	else if (a == "|")
	  return 3;
	else if (a == "^")
	  return 4;
	else if (a == "&")
	  return 5;
	else if (a == "<<" || a == ">>")
	  return 6;
	else if (a == "+"  || a == "-")
	  return 7;
	else if (a == "*"  || a == "/" || a == "%")
	  return 8;
	else if (a == "~"  || a == "!" || a == "p" || a == "m")
	  return 9;
	else return 0;
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
	while( isdigit( input[i+1] ) ){   //掃到數字，全部讀完
		i++;
		char it = input[i];
		string tmp2(1,it);
		tmp+=tmp2;
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
		//cout << "i =" << i << endl;
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
		else if( isspace(it) )
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
			else if( it=='<' || it== '>' )
			{
				string tmp = c2str(it);
				string tmp2;
				int cnt = i+1; //把下個 < / >掃進來
				it = input[cnt];
				if(it == '<' || it == '>')
				{
					tmp2 =  c2str(it);
					i++;
				}
				else
				{
					//cout << "wrong input of "<< "< / > " << endl;
					return;					
				}
				tmp+=tmp2;
				check(optr_con, oprd_con, tmp);
			}
			else if( it=='|' )
			{
				string tmp = c2str(it);
				string tmp2;
				int cnt = i+1; //檢查下個it是不是 |
				it = input[cnt];
				if(it == '|' )
				{
					i++;
					tmp2 =  c2str(it);
					tmp+=tmp2;
					check(optr_con, oprd_con, tmp);
				}	
				else
					check(optr_con, oprd_con, tmp);		
			}
			else if( it=='&' )
			{
				string tmp = c2str(it);
				string tmp2;
				int cnt = i+1; //檢查下個it是不是&
				it = input[cnt];
				if(it == '&' )
				{
					i++;
					tmp2 =  c2str(it);
					tmp+=tmp2;
					check(optr_con, oprd_con, tmp);
				}	
				else
					check(optr_con, oprd_con, tmp);		
			}
			else if( it=='*' || it=='/' || it=='%' || it=='^' || it=='~' || it=='!')
			{
				string tmp = c2str(it);
				check(optr_con, oprd_con, tmp);
			}
		}
	}
}

int caculate_pstfix(intStack& result, newStack & oprd_con)
{
	for(newStack::iterator i=oprd_con.begin(); i!=oprd_con.end(); ++i)
	{
		string element = *i;
		if( isdigit( element[0] ) )
		{
			int value = stoi(*i);    //將srt轉為數字
			result.push_back(value); //將數字放到stack
		}
		else
		{
			if( *i=="p" )
			{
				continue;
			}
			else if( *i=="m" )
			{
				int tmp = result.back();
				tmp = -(tmp);
				result.pop_back();    //把result.back() pop掉
				result.push_back(tmp);//再放回去數字
			}
			else if( *i=="~" )
			{
				int tmp = result.back();
				tmp = ~tmp;
				result.pop_back();
				result.push_back(tmp);
			}
			else if( *i=="!" )
			{
				if(result.back()==0)
				{
					int tmp = 1;
					result.pop_back();
					result.push_back(tmp);
				}
				else
				{
					int tmp = 0;
					result.pop_back();
					result.push_back(tmp);
				}
			}
			else if( *i==">>")
			{
				int tmp = result.back();
				result.pop_back();
				int tmp2 = result.back();
				result.pop_back();
				int newTmp = (tmp2>>tmp);
				result.push_back(newTmp);
			}
			else if( *i=="<<")
			{
				int tmp = result.back();
				result.pop_back();
				int tmp2 = result.back();
				result.pop_back();
				int newTmp = (tmp2<<tmp);
				result.push_back(newTmp);
			}	
			else if( *i=="&")
			{
				int tmp = result.back();
				result.pop_back();
				int tmp2 = result.back();
				result.pop_back();
				int newTmp = (tmp2&tmp);
				result.push_back(newTmp);
			}
			else if( *i=="|")
			{
				int tmp = result.back();
				result.pop_back();
				int tmp2 = result.back();
				result.pop_back();
				int newTmp = (tmp2|tmp);
				result.push_back(newTmp);
			}
			else if( *i=="^")
			{
				int tmp = result.back();
				result.pop_back();
				int tmp2 = result.back();
				result.pop_back();
				int newTmp = (tmp2^tmp);
				result.push_back(newTmp);
			}
			else if( *i=="||")
			{
				int tmp = result.back();
				result.pop_back();
				int tmp2 = result.back();
				result.pop_back();
				if(tmp==0 && tmp2==0)
				{
					int newTmp = 0;
					result.push_back(newTmp);
				}
				else
				{
					int newTmp = 1;
					result.push_back(newTmp);
				}
			}
			else if( *i=="&&")
			{
				int tmp = result.back();
				result.pop_back();
				int tmp2 = result.back();
				result.pop_back();
				if(tmp!=0 && tmp2!=0)
				{
					int newTmp = 1;
					result.push_back(newTmp);
				}
				else
				{
					int newTmp = 0;
					result.push_back(newTmp);
				}
			}	
			else if( *i=="+")
			{
				int tmp = result.back();
				result.pop_back();
				int tmp2 = result.back();
				result.pop_back();
				int newTmp = (tmp2+tmp);
				result.push_back(newTmp);
			}
			else if( *i=="-")
			{
				int tmp = result.back();
				result.pop_back();
				int tmp2 = result.back();
				result.pop_back();
				int newTmp = (tmp2-tmp);
				result.push_back(newTmp);
			}
			else if( *i=="*")
			{
				int tmp = result.back();
				result.pop_back();
				int tmp2 = result.back();
				result.pop_back();
				int newTmp = (tmp2*tmp);
				result.push_back(newTmp);
			}
			else if( *i=="/")
			{
				int tmp = result.back();
				result.pop_back();
				int tmp2 = result.back();
				result.pop_back();
				int newTmp = (tmp2/tmp);
				result.push_back(newTmp);
			}
			else if( *i=="%")
			{
				int tmp = result.back();
				result.pop_back();
				int tmp2 = result.back();
				result.pop_back();
				int newTmp = (tmp2%tmp);
				result.push_back(newTmp);
			}
		}
	}
	return result.back();
}