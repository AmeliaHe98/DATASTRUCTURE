//
//  stack.cpp
//  
//
//  Created by Amelia He on 2018-02-23.
//
#include <iostream>
#include <vector>
#include "stack.h"
#include "point.h"
using std::vector;
using namespace std;


//returns vector size
int Stack::size()
{
    return st.size();
}

//checks if stack is empty
bool Stack::isEmpty()
{
    return st.empty();
}

//adds item to stack
void Stack::push(Point p)
{
    st.push_back(p);
    
}

//removes item at top of stack
Point Stack::pop() {
    if (isEmpty()) {
        return Point(0,0);
    }
    Point temp = st.back();
    st.pop_back();
    return temp;
}

//returns item at top of stack
Point Stack::peek() {
    if (isEmpty()) {
        return Point(0,0);
    }
    return st.front();
}


