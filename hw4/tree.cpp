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
	/****************/
	/*還沒做epsilon***/
	/****************/
	double epsilon;
	char * epsilon_c;
	int number_of_recur = 1;  //跑幾次迴圈
	char * fileName = NULL;   //用來讀檔案名
	if( argc == 3 )
	{
		fileName = argv[1];
		epsilon_c = argv[2];
		epsilon =  atof(epsilon_c) ;
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
			/*
			istringstream ss(line);
			char word[100];
			int result;
			bool flag = true;
			將資料tokenize
			while(ss > word)
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
					sscanf(word, "%d%*c%lf", &index, &n );
					a.features[index] = n;	
					flag = true;
				}
			}
			*/
			container.push_back(a);
		}
		make_decision(number_of_recur, epsilon , biggest_index, container);
	}
	pfile.close();
	return 0;
}