#include <fstream>
#ifndef FUNC_H
#define FUNC_H
#include "structure.h"
#include "exampleClass.h"
#include "locationOfMinCon.h"

void knuthShuffle(newVec::iterator begin, newVec::iterator end);
void make_decision(int, int, double , int, newVec &);
double calCon(int, int, newVec&, double&);
double confusion(double , double);
void findCon(int , int , double , locationOfMinCon&, double&);
void indentation(int);

#endif