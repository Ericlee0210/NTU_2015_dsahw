#include <cstdlib>   //atof()
#include <iostream> //printf()
#include <fstream>  //fstream fopen()
using namespace std;



int main(int argc, char *argv[])
{
	FILE * pfile;
	double epsilon;
	char * epsilon_c;
	char * fileName = NULL;
	if( argc == 3 )
	{
		fileName = argv[1];
		epsilon_c = argv[2];
		epsilon = atof(epsilon_c);
	}
	else
	{
		printf("arrguments are wrong!!\n");
		return 0;
	}
	pfile = fopen(fileName, "r");
	if(!pfile)
	{
		printf("can't open %s .\n", fileName);
		return 0;
	}
	else
	{
		//讀檔
	}
	fclose(pfile);
	return 0;
}