#include <fstream>
#include <iostream>
#include <cmath>
#include <ctime>
#include <algorithm>
#include "forest_func.h"
#include "structure.h"
#include "locationOfMinCon.h"
#include "exampleClass.h"


void knuthShuffle(newVec::iterator begin, newVec::iterator end)
{
	for(unsigned int n = end-begin-1; n>=1; --n)
	{
		unsigned int k = rand()% (n+1);
		if(k!=n)
		{
			iter_swap(begin+k, begin+n);
		}
	}
}


class cmp_obj
{
public:
	cmp_obj(int a): index(a){}
	bool operator()(example& s, example& t)
	{
		return (s.features[index] < t.features[index]);
	}
	int index;
};


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


double calCon(int i, int j, newVec& tree, double& th)
{
	int leftYN[2]  = {0,0};  //左邊for yes, 前面為no, 後為yes
	int rightYN[2] = {0,0};  //右邊for no, 前面為no, 後為yes

	if(j==0)
		th = tree[0].features[i] - 1;
	else
		th = (tree[j].features[i]+ tree[j-1].features[i])/2;

	//統計當基準為tree[j].features[i]時，左右兩邊的Y/N共多少
	for(newVec::iterator q = tree.begin(); q!=tree.end(); q++)
	{
		double e = 0.0000001;
		/****************************************************/
		/*這邊有個問題，features數值等於基準時，要算左邊還是右邊？***/
		/****************************************************/
		if( fabs(q->features[i] - th) < e ||
			     q->features[i] < th
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

void findCon(int i, int j, double confusion, locationOfMinCon& c, double& threshold)
{
	if( confusion < c.total_confusion) 
	{
		c.index_for_example = j;
		c.index_for_features = i;
		c.total_confusion = confusion;
		c.threshold = threshold;
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

void make_decision(int number_of_recur, int theBirthOfTree , double epsilon, int biggest_index,  newVec & tree)
{
	double e = 0.0000001;

	//跑第一次，要印出function函數名字與argument
	if(number_of_recur ==1)
	{	
		indentation(number_of_recur);
		std::cout << "//tree" << theBirthOfTree <<"_predict:\n";
	}

	int i, j; //i for every features, j for every example
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
		std::cout << "number_of_yes++;\n"; 
		return;
	}
	if(number_of_yes==0 && number_of_no!=0)
	{
		//std::cout << "為啥莫名其妙結束了!?";
		indentation(number_of_recur);
		std::cout << "number_of_no++;\n";
		return;
	}

	//confusion < epsilon的狀況
	double confusionIsSmallerThanE = confusion(number_of_yes, number_of_no);
	if(confusionIsSmallerThanE < epsilon)
	{
		if(number_of_yes > number_of_no)
		{
			indentation(number_of_recur);
			std::cout << "number_of_yes++;\n";
			return;
		}
		else if(number_of_yes < number_of_no)
		{
			indentation(number_of_recur);
			std::cout << "number_of_no++;\n";
			return;
		}
		else
		{
			double random_number = double(rand())/1.0;
			if(random_number>=0.5)
			{
				indentation(number_of_recur);
				std::cout << "number_of_yes++;\n";
				return;
			}
			else
			{
				indentation(number_of_recur);
				std::cout << "number_of_no++;\n";
				return;
			}
		}
	}

	//std::cout << "其實跑到這!!";
	locationOfMinCon tmp;  //裡面包含 index for example, index for features, double for confusion
	tmp.total_confusion =100;  //初始比較值，

	double threshold = 0.0;

	//找到切哪一刀，將tree劃分為二
	for(i=0; i<=biggest_index; i++)
	{
		//std::cout << number_of_recur <<  " searching " << i << std::endl;
		sort( tree.begin(), tree.end(), cmp_obj(i) );
		threshold = tree[0].features[i]-1;
		//for(int p=0; p<number_of_example; p++)
		//{
		//	std::cout << tree[p].features[i] << " ";
		//}
		//std::cout << std::endl;
		double biggest_features = tree[0].features[i];

		for(j=0; j<number_of_example; j++)
		{
			if ( fabs( tree[j].features[i] - biggest_features ) < e )
				continue;
			else
			{
				if(j==number_of_example-1)
					threshold = tree[j].features[i]+1;
				biggest_features = tree[j].features[i];
				double confusion = calCon(i, j, tree, threshold);
				findCon(i, j, confusion, tmp, threshold); 				
			}
		}
	}
	
	//if(tmp.threshold == 1)
	//{
	//	std::cout << number_of_recur << std::endl;
	//	std::cout << tmp.index_for_features;
	//}
		



	//無法切了，無論怎麼切都無法一分為二，其中一邊都是0Y0N，confusion超大	
	/**********************************************/
	/*這邊有個問題，yes與no數量一樣時，要return 多少？***/
	/**********************************************/
	if(tmp.total_confusion >= 100)
	{
		if(number_of_yes >= number_of_no)   //<<<<<<<<<問題所在
		{
			indentation(number_of_recur);
			std::cout << "number_of_yes++;\n";
			return;
		}
		else
		{
			indentation(number_of_recur);
			std::cout << "number_of_no++;\n";
			return;
		}
	}

	int index_for_features_cpy = tmp.index_for_features;
	//std::cout << "index_for_features= " << tmp.index_for_features << std::endl;
	
	newVec left_subtree;
	newVec right_subtree;

	//產生subtree
	for(newVec::iterator q= tree.begin(); q!=tree.end(); q++)
	{
		/****************************************************/
		/*這邊有個問題，features數值等於基準時，要算左邊還是右邊？***/
		/****************************************************/
		if( fabs( q->features[index_for_features_cpy] - tmp.threshold ) < e || 
			      q->features[index_for_features_cpy] < tmp.threshold 
		  ) 
			right_subtree.push_back(*q);
		else
			left_subtree.push_back(*q);
	}

	indentation(number_of_recur);
	std::cout << "if(attr[" << index_for_features_cpy << "] " << "> " << tmp.threshold << ")\n";
	indentation(number_of_recur);
	std::cout << "{\n";
	make_decision(number_of_recur+1, theBirthOfTree, epsilon, biggest_index, left_subtree);
	indentation(number_of_recur);
	std::cout << "}\n";


	indentation(number_of_recur);
	std::cout << "else\n";
	indentation(number_of_recur);
	std::cout << "{\n";
	make_decision(number_of_recur+1, theBirthOfTree, epsilon, biggest_index, right_subtree);
	indentation(number_of_recur);
	std::cout << "}\n";
	
	return;
}