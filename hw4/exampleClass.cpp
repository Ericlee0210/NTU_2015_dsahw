#include "exampleClass.h"

void example::exampleInit()
{
	for(int i=0; i< maxfeatures; i++)
	{
		features[i] = 0;
	}
	for(int i=0; i< maxfeatures; i++)
	{
		confusion[i] = 99999;
	}
}