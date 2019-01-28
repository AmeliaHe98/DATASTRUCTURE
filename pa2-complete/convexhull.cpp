//
//  convexhull.cpp
//  
//
//  Created by Amelia He on 2018-02-23.
//

#include "convexhull.h"
#include <cmath>
#include <vector>
#include "point.h"
#include "stack.h"
#include <iostream>
using namespace std;

void sortByAngle(vector<Point>& v){
    
    if(v.empty())
        return; //no element
    
    //find smallest point
    for(unsigned i = 1; i<v.size(); i++){
        if(v[i].y < v[0].y)
            swap(v[i],v[0]);
        if(v[i].y==v[0].y&&v[i].x<v[0].x){
            swap(v[i],v[0]);
        }
        }

    
    for(unsigned i = 0; i < v.size(); i++){
        int pos = i;
        while (pos>0 && findAngle(v[pos],v[pos-1],v[0])){
            swap(v[pos], v[pos-1]);
            pos--;
            }
        
    }
}


bool ccw(Point p1, Point p2, Point p3){
    int area = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
    //counter-clockwise
    if (area > 0)
         return false;
    //colinear
    else if (area == 0)
        return false;
    //clockwise
    else
        return true;
}

bool findAngle(Point p1, Point p2, Point orig){
    float angleP1 = atan2(p1.y - orig.y, p1.x - orig.x);
    float angleP2 = atan2(p2.y - orig.y, p2.x - orig.x);
    if(angleP1<angleP2)
        return true;
    if(angleP1==angleP2 && p1.x<p2.x)
        return true;
    else
        return false;
}


vector<Point> getConvexHull(vector<Point>& v){
    vector<Point> vertices;
    int n = v.size();
    if(n<3)
        return vertices;
        sortByAngle(v);
    // Create an empty stack and push first three points to it
    vertices.push_back(v[0]);
    vertices.push_back(v[1]);
    vertices.push_back(v[2]);
    // Process remaining n-3 points
    for (int i = 3; i < n; i++) {
        // Keep removing top while the angle formed by
        // points next-to-top, top, and points[i] makes a right (in clockwise) turn
        while (ccw(vertices[vertices.size() - 2], vertices.back(), v[i])) {
            vertices.pop_back();
        }
        vertices.push_back(v[i]);
    }
    return vertices;
    
}
