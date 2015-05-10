#include <cstdlib>   //atof()
#include <iostream> //printf()
#include <fstream>  //ifstream
#include <sstream>  //istringstream
#include <string>
#include <ctime>
#include "func.h"
#include "structure.h"
#include "exampleClass.h"

using namespace std;

int main(int argc, char *argv[])
{
	std::ifstream  pfile;
	srand(time(NULL));
	int howManyTrees;
	char * howManyTrees.c;
	int number_of_recur = 1;  //跑幾次迴圈
	char * fileName = NULL;   //用來讀檔案名
	if( argc == 3 )
	{
		fileName = argv[1];
		howManyTrees.c = argv[2];
		howManyTrees =  atoi(howManyTrees.c) ;
	}
	else
	{
		printf("arrguments are wrong!!\n");
		return 0;
	}
	pfile.open(fileName, ios::in);
	if(!pfile)
	{
		printf("can't open %s .\n", fileName);
		return 0;
	}
	else
	{
		newVec container;     //用來裝所有example的container
		string istring;  //搭配getline()，掃每一行文字
		
		int biggest_index = 1;

		while( getline(pfile, istring) )
		{
			example a; //裝一筆資料
			a.exampleInit();

			char * cstring, *tmp; 
			cstring = new char[istring.size()+1];
			strncpy(cstring, istring.c_str(), istring.size()+1);

			tmp = strtok(cstring, ": ");
			int result = atoi(tmp);
			if(result > 0)
				a.result = 1;
			else
				a.result = 0;
			tmp = strtok(NULL, ": ");

			while(tmp != NULL)
			{
				int index = atoi(tmp);
				if(index > biggest_index)
					biggest_index = index;
				tmp = strtok(NULL, ": ");
				//cout << "index= " << index << "   ";
				//cout << "features= " << static_cast<double> ( atof(tmp) ) << endl;
				a.features[index] =  atof(tmp) ;
				tmp = strtok(NULL, ": ");
			}

			delete[] cstring;
			container.push_back(a);
		}

		make_decision(number_of_recur, 0 , biggest_index, container);
	}
	pfile.close();
	return 0;
}