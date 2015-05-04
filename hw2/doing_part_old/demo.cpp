#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <map>
#include <vector>
#include "func.h"
using namespace std;

int main(int argc, char *argv[])
{
	bMap list;

	FILE * pfile;
	char* filename;
	char funcName[20];

	//********************測試URL是否獨立*********************************
	//map<char[30], data> test;		
	//******************************************************************


	if(argc>1)
		filename = argv[1];
	else
	{
		cout << "can't read argument!" << endl;
		return 0;
	}
	
	pfile = fopen(filename, "r");
	if(!pfile)
	{
		cout << "open file failed!" << endl;
		return 0;
	}
	else
	{
		long long int count =0;
		//int count=1;
		while( 1 )
		{
			if(feof(pfile)) break;
			data node;
			fscanf(pfile, "%d%d%s%llu%d%d%d%d%d%d%d%llu", &node.click, &node.impression, node.displayURL, &node.adID, &node.advertiseID, &node.depth, &node.position, &node.queryID, &node.keywordID, &node.titleID, &node.descriptionID, &node.userID);
			
			
			//********************存入 vector in map in map in map*********************************
			if(list[node.userID][node.adID][node.queryID].empty())
			{
				vector<data> a;
				a.push_back(node);
				list[node.userID][node.adID][node.queryID] = a;
			}
			else
			{
				list[node.userID][node.adID][node.queryID].push_back(node);
			}
			//********************存入 vector in map in map in map*********************************
			

			//map<uint_64, data>::iterator i = profit_list[node.adID].find(node.userID);
			//********************存入 vector in map in map*********************************
			//if(i ==profit_list[node.adID].end())
			//{
			//	profit_list[node.adID][node.userID] = node;
			//}
			//else
			//{
			//	profit_list[node.adID][node.userID].click += node.click;
			//	profit_list[node.adID][node.userID].impression += node.impression;
			//}
			//********************存入 vector in map in map*********************************
			
			//********************測試fscanf & map in map 功能*******************
			//cout << count++ << endl;
			if(count%1000000==0)
				cout << count << endl;
				//printf_data(&node);
			//******************************************************************
			count++;
		}
		cout << "parse succeed!" << endl;
	
		while(~scanf("%s", funcName))
		{
			if(strcmp(funcName,"get")==0)
			{
				uint_64 userID, adID;
				uint_16 queryID, position, depth;
				scanf("%lld%lld%d%d%d", &userID, &adID, &queryID, &position, &depth);
				get(list, userID, adID, queryID, position, depth);
			}
			
			else if(strcmp(funcName,"clicked")==0)
			{
				uint_64 userID;
				scanf("%llu", &userID);
				clicked(list, userID);
			}
			else if(strcmp(funcName,"impressed")==0)
			{
				uint_64 uID1, uID2;
				scanf("%llu%llu", &uID1, &uID2);
				impressed(list, uID1, uID2);
			}
			else if(strcmp(funcName,"profit")==0)
			{
				uint_64 adID;
				double theta;
				scanf("%llu%lf", &adID, &theta);
				profit(list, adID, theta);
			}
			else if(strcmp(funcName,"quit")==0)
			{
				quit();
				break;
			}	
		}
	}
	fclose(pfile);
	return 0;
}