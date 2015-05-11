#ifndef LOCATIONOFMINCON_H
#define LOCATIONOFMINCON_H

struct locationOfMinCon
{
	int index_for_example;
	int index_for_features;
	double total_confusion;
	double threshold;
	locationOfMinCon(int a=0, int b=0, int c=100, int d=0): index_for_example(a), index_for_features(b), total_confusion(c), threshold(d){}
};

#endif