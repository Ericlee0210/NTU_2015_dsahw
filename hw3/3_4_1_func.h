#ifndef FUNC_H
#define FUNC_H
#include "3_4_1_container.h"

std::string c2str(const char &);
bool isoperator(const char &);
void compare(newStack &, newStack &, const std::string &); //比較優先順序
void push2Stack(newStack &, const std::string &);  //將目前operator放入stack
void moveFromStack2Output(newStack &, newStack &); //把stack.top()拿出來放到output 
int precedence(const std::string &); //判斷該運算子優先順序
void show(newStack &, newStack &); //將目前stack與output內容顯示出來
std::string makeDigit(unsigned int &, const std::string &); //爬連續數字，產生數字string
void check(newStack &, newStack &,  std::string &);
void in2post(newStack &, newStack &, const std::string &); //將infix轉換為postfix
int caculate_pstfix(intStack&, newStack &);
#endif