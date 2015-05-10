#include <cstdlib>   //atof()
#include <iostream> //printf()
#include <fstream>  //ofstream
#include <sstream>  //istringstream
#include "func.h"
#include "structure.h"
#include "exampleClass.h"

using namespace std;

int main(int argc, char *argv[])
{
	FILE * pfile;
	ofstream outputfile;
	outputfile.open("tree_pred_func.cpp", ios::out);
	double epsilon;
	char * epsilon_c;
	int number_of_recur = 1;
	char line[60000];  //用來裝每一行資料
	char * fileName = NULL;
	if( argc == 3 )
	{
		fileName = argv[1];
		epsilon_c = argv[2];
		epsilon = atod(epsilon_c);
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
		newVec container;
		int number_of_line =0;
		while(fgets(line, sizeof(line), pfile))
		{
			example a; //裝一筆資料
			a.exampleInit();
			istringstream ss(line);
			char word[100];
			int result;
			bool flag = true;
			//將資料tokenize
			while(ss> word)
			{
				if(flag)
				{
					sscanf(word, "%d" , &result);  //每筆資料的result
					if(result > 0)
						a.result = 1;
					else
						a.result = 0;
					flag = false;
				}
				else
				{
					int index; //3:4.0000 3 is index, 4.0000 is n
					double n;
					sscanf(word, "%d%*c%f", &index, &n );
					a.features[index] = n;	
					flag = true;
				}
			}
			container.push_back(a);
		}
		make_decision(number_of_recur, container, outputfile);
	}
	fclose(pfile);
	outputfile.close();
	return 0;
}