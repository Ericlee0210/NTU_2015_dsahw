#include <fstream>
#include "func.h"
#include "struture.h"
#include "exampleClass.h"

double calCon(int i, int j, newVec& tree)
{
	int leftYN[2]  = {0,0};  //前面為yes, 後為no
	int rightYN[2] = {0,0};  //前面為yes, 後為no

	//統計當基準為tree[j]時，左右兩邊的Y/N共多少
	for(newVec::iterator q = tree.begin(); q!=tree.end(); q++)
	{
		if(*q.features[i] <= tree[j].features[i])  //左邊有多少Y/N
		{
			if(*q.result==1)
				leftYN[0]++;
			else
				leftYN[1]++;
		}
		else //右邊有多少Y/N
		{
			if(*q.result==1)
				rightYN[0]++;
			else
				rightYN[1]++;			
		}
	}

	//開始計算左右兩邊的confusion

	//開始計算總共的confusion

	//return 數字;
}


void make_decision(int number_of_recur, newVec & tree, ofstream & outputfile)
{
	//跑第一次，要印出function函數名字與argument
	if(number_of_recur ==1)
		outputfile << "int tree_predict(double *attr){\n";

	int i, j; //i for every example, j for every features
	int number_of_example = tree.size();

	//統計目前yes / no數量
	int number_of_yes=0, number_of_no=0;
	for(int s=0; s<number_of_example; s++)
	{
		if(tree[s].result==1)
			number_of_yes++;
		else
			number_of_no++;
	}

	//已經沒得切哩~~
	if(number_of_yes!=0 || number_of_no==0)
	{
		//indentation(number_of_recur);
		outputfile << "reture 1;\n"; 
	}
	if(number_of_yes==0 || number_of_yes!=0)
	{
		//indentation(number_of_recur);
		outputfile << "reture 0;\n";
	}

	//confusion < epsilon的狀況
	//還沒做

	//whereIsMinCon tmp;  裡面包含 index for example, index for features, double for confusion
	//tmp.confusion =1;

	//找到切哪一刀，將tree劃分為二
	for(i=0; i<maxfeatures; i++)
	{
		for(j=0; j<number_of_example; j++)
		{
			double confusion = calCon(i, j, number_of_example, tree);  //function還沒寫
			findCon(i, j, tree, tmp);  //function還沒寫
		}
	}
}