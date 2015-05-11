#include <cstdlib>   //atof()
#include <iostream> //printf()
#include <fstream>  //ifstream
#include <sstream>  //istringstream
#include <string>
#include <ctime>
#include <algorithm>
#include "forest_func.h"
#include "structure.h"
#include "exampleClass.h"

using namespace std;

int main(int argc, char *argv[])
{
	std::ifstream  pfile;
	srand(time(NULL));
	int howManyTrees;
	char * howManyTrees_c;
	int number_of_recur = 1;  //跑幾次迴圈
	char * fileName = NULL;   //用來讀檔案名
	if( argc == 3 )
	{
		fileName = argv[1];
		howManyTrees_c = argv[2];
		howManyTrees =  atoi(howManyTrees_c) ;
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

		int size_of_container = container.size();
		int total_example_I_should_extract = size_of_container/3;

		
		std::cout << "int forest_predict(double *attr)\n";
		std::cout << "{\n";
		std::cout << "    int number_of_yes=0, number_of_no=0;\n"; 
		
		for(int i=0; i<howManyTrees; i++)
		{
			knuthShuffle(container.begin(), container.end());
			newVec knuthShuffleOrderContainer(container.begin(), container.begin()+total_example_I_should_extract-1);
			make_decision(number_of_recur, i, 0 , biggest_index, knuthShuffleOrderContainer);
		}

		std::cout << "    //voting\n";
		std::cout << "    if( number_of_yes > number_of_no)\n";
		std::cout << "        return 1;\n";
		std::cout << "    else\n";
		std::cout << "        return -1;\n";
		std::cout << "}";
		
	}
	pfile.close();
	return 0;
}