#include <vector>
#include <algorithm>
#ifndef EXAMPLECLASS_H
#define EXAMPLECLASS_H
#define maxfeatures 1025

class example
{
public:
	int result;
	std::vector<double> features;
	std::vector<double> confusion;
	example(int max=1025, int c=0, int d=100): features(max, c), confusion(max, d){}
	friend void swap(example& a, example& b)
	{
		std::swap(a.result, b.result);
		a.features.swap(b.features);
		a.confusion.swap(b.confusion);
	}
};


#endif