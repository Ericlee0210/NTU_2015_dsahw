#ifndef EXAMPLECLASS_H
#define EXAMPLECLASS_H
#define maxfeatures 1025

class example
{
public:
	int result;
	double features[maxfeatures];
	double confusion[maxfeatures];
	void exampleInit();
};


#endif