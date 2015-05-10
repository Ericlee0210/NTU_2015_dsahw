#include <fstream>
#include <iostream>
#include <cmath>
#include <ctime>
#include "func.h"
#include "structure.h"
#include "locationOfMinCon.h"
#include "exampleClass.h"


double confusion(double a, double b)
{
	if(a == 0 && b == 0)
		return 100;
	else
	{
		double tmp1 = (a / (a+b)) * (a / (a+b));
		double tmp2 = (b / (a+b)) * (b / (a+b));
		return ( 1 - tmp1 - tmp2 );
	}
}

double totalConfusion(double a, double b, double c, double d)
{
	double tmp1 = (a+b)/ (a+b+c+d);
	double tmp2 = (c+d)/ (a+b+c+d);

	return ( tmp1*confusion(a,b) + tmp2*confusion(c, d) );
}


double calCon(int i, int j, newVec& tree)
{
	int leftYN[2]  = {0,0};  //左邊for yes, 前面為no, 後為yes
	int rightYN[2] = {0,0};  //右邊for no, 前面為no, 後為yes

	//統計當基準為tree[j].features[i]時，左右兩邊的Y/N共多少
	for(newVec::iterator q = tree.begin(); q!=tree.end(); q++)
	{
		double e = 0.0000001;
		/****************************************************/
		/*這邊有個問題，features數值等於基準時，要算左邊還是右邊？***/
		/****************************************************/
		if( fabs(q->features[i] - tree[j].features[i]) < e ||
			 q->features[i] < tree[j].features[i]
		)  //左邊有多少Y/N
		{
			if(q->result==1)
				rightYN[1]++;
			else
				rightYN[0]++;
		}
		else //左邊有多少Y/N
		{
			if(q->result==1)
				leftYN[1]++;
			else
				leftYN[0]++;			
		}
	}

	//開始計算總共的confusion
	double total_confusion = totalConfusion(leftYN[0], leftYN[1], rightYN[0], rightYN[1]);
	tree[j].confusion[i] = total_confusion;

	return tree[j].confusion[i];
}

void findCon(int i, int j, double confusion, locationOfMinCon& c)
{
	if( confusion < c.total_confusion) 
	{
		c.index_for_example = j;
		c.index_for_features = i;
		c.total_confusion = confusion;
	}
	return;
}

void indentation(int number_of_recur)
{
	for(int i=0; i<number_of_recur; i++)
	{
		std::cout << "    ";
	}
}

void make_decision(int number_of_recur, double epsilon,  newVec & tree)
{
	//跑第一次，要印出function函數名字與argument
	if(number_of_recur ==1)
	{
		std::cout << "int tree_predict(double *attr)\n";
		std::cout << "{\n";
	}

	int i, j; //i for every example, j for every features
	int number_of_example = tree.size();

	//統計目前tree的yes / no數量
	int number_of_yes=0, number_of_no=0;
	for(newVec::iterator s=tree.begin(); s!=tree.end(); s++)
	{
		if(s->result==1)
			number_of_yes++;
		else
			number_of_no++;	
	}

	//for subtree，已經沒得切哩~~
	if(number_of_yes!=0 && number_of_no==0)
	{
		//std::cout << "為啥莫名其妙結束了!?";
		indentation(number_of_recur);
		std::cout << "return 1;\n"; 
		return;
	}
	if(number_of_yes==0 && number_of_no!=0)
	{
		//std::cout << "為啥莫名其妙結束了!?";
		indentation(number_of_recur);
		std::cout << "return -1;\n";
		return;
	}

	//confusion < epsilon的狀況
	double confusionIsSmallerThanE = confusion(number_of_yes, number_of_no);
	if(confusionIsSmallerThanE < epsilon)
	{
		if(number_of_yes > number_of_no)
		{
			indentation(number_of_recur);
			std::cout << "return 1;\n";
			return;
		}
		else if(number_of_yes < number_of_no)
		{
			indentation(number_of_recur);
			std::cout << "return -1;\n";
			return;
		}
		else
		{
			double random_number = double(rand())/1.0;
			if(random_number>=0.5)
			{
				indentation(number_of_recur);
				std::cout << "return 1;\n";
				return;
			}
			else
			{
				indentation(number_of_recur);
				std::cout << "return -1;\n";
				return;
			}
		}
	}

	//std::cout << "其實跑到這!!";
	locationOfMinCon tmp;  //裡面包含 index for example, index for features, double for confusion
	tmp.total_confusion =100;  //初始比較值，

	//找到切哪一刀，將tree劃分為二
	for(i=0; i<maxfeatures; i++)
	{
		for(j=0; j<number_of_example; j++)
		{
			double confusion = calCon(i, j, tree);
			findCon(i, j, confusion, tmp); 
		}
	}
	
	//無法切了，無論怎麼切都無法一分為二，其中一邊都是0Y0N，confusion超大	
	/**********************************************/
	/*這邊有個問題，yes與no數量一樣時，要return 多少？***/
	/**********************************************/
	if(tmp.total_confusion >= 100)
	{
		if(number_of_yes >= number_of_no)   //<<<<<<<<<問題所在
		{
			indentation(number_of_recur);
			std::cout << "return 1;\n";
			return;
		}
		else
		{
			indentation(number_of_recur);
			std::cout << "return -1;\n";
			return;
		}
	}

	int index_for_example_cpy = tmp.index_for_example;
	//std::cout << "index_for_example_cpy= " <<  tmp.index_for_example << std::endl;
	int index_for_features_cpy = tmp.index_for_features;
	//std::cout << "index_for_features= " << tmp.index_for_features << std::endl;
	double value_of_features = tree[index_for_example_cpy].features[index_for_features_cpy];
	
	newVec left_subtree;
	newVec right_subtree;

	//產生subtree
	for(newVec::iterator q= tree.begin(); q!=tree.end(); q++)
	{
		double e = 0.0000001;
		/****************************************************/
		/*這邊有個問題，features數值等於基準時，要算左邊還是右邊？***/
		/****************************************************/
		if( fabs( q->features[index_for_features_cpy] - tree[index_for_example_cpy].features[index_for_features_cpy] ) < e || 
			q->features[index_for_features_cpy] < tree[index_for_example_cpy].features[index_for_features_cpy] 
		  ) 
			right_subtree.push_back(*q);
		else
			left_subtree.push_back(*q);
	}

	indentation(number_of_recur);
	std::cout << "if(attr[" << index_for_features_cpy << "] " << "> " << value_of_features << ")\n";
	indentation(number_of_recur);
	std::cout << "{\n";
	make_decision(number_of_recur+1, epsilon, left_subtree);
	indentation(number_of_recur);
	std::cout << "}\n";


	indentation(number_of_recur);
	std::cout << "else\n";
	indentation(number_of_recur);
	std::cout << "{\n";
	make_decision(number_of_recur+1, epsilon, right_subtree);
	indentation(number_of_recur);
	std::cout << "}\n";

	if(number_of_recur==1)
		std::cout << "}";

	return;
}