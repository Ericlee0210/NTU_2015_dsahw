#include <fstream>
#ifndef FUNC_H
#define FUNC_H
#include "structure.h"
#include "exampleClass.h"
#include "locationOfMinCon.h"

//void indentation(number_of_recur);
void make_decision(int, double, newVec &);
double calCon(int, int, newVec&);
double confusion(double , double);
void findCon(int , int , double , locationOfMinCon&);
void indentation(int);

#endif