#include <iostream>
using namespace std;
int *func(int& a, int&b)
{
	int* pc = new int;
	*pc = a-b;
	return pc;
}

int main()
{
	int a=10;
	int b=5;
	int* pc = func(a,b);
	cout << *pc;
	return 0;	
}