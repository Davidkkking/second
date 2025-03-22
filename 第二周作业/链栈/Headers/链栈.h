#ifndef LINKSTACK_H
#define LINKSTACK_H

#include <stdexcept> 
struct StackNode {
    double data;         
    StackNode* next;    
};

void initStack(StackNode*& top);             
bool isEmpty(StackNode* top);                 
void push(StackNode*& top, double value);     
double pop(StackNode*& top);                  
double getTop(StackNode* top);               

#endif
