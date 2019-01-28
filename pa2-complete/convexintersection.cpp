#include "convexintersection.h"
#include <iostream>
using namespace std;
// determines whether a point p1 is inside or outside
// of a line segment defined by sp1 and sp2
// sp1 and sp2 should be consistently provided
// from the convex hull algorithm such that the edges
// are listed in a CCW direction
// p1 belongs to the subject polygon
// sp1 and sp2 belong to the clipping polygon
bool inside(Point p1, Point sp1, Point sp2) {
    double result = (sp2.x - sp1.x)*(p1.y - sp1.y) - (sp2.y - sp1.y)*(p1.x - sp1.x);
    
    if (result >= 0) return true;
    return false;
}

// computes the point of intersection between the line segment
// defined by s1 and s2, and the infinite line defined by
// i1 and i2.
// Assume that this will only be called when the intersection exists.
Point computeIntersection(Point s1, Point s2, Point i1, Point i2){
  
  double xResult=0;
  double yResult=0;
  
  double num = (s1.x*s2.y - s1.y*s2.x) * (i1.x - i2.x) - (s1.x - s2.x) * (i1.x*i2.y - i1.y*i2.x);
  double den = (s1.x-s2.x)*(i1.y-i2.y) - (s1.y-s2.y)*(i1.x-i2.x);
  xResult = num/den;
  
  num = (s1.x*s2.y - s1.y*s2.x) * (i1.y-i2.y) - (s1.y-s2.y) * (i1.x*i2.y - i1.y*i2.x);
  den = (s1.x-s2.x) * (i1.y-i2.y) - (s1.y-s2.y) * (i1.x-i2.x);
  yResult = num/den;
  
  return Point(xResult,yResult);
  
}

// returns a vector containing a sequence of points defining
// the intersection of two convex polygons poly1 and poly2
// Inputs: poly1 and poly2 - sequences of points defining the
//                           borders of convex polygons
vector<Point> getConvexIntersection(vector<Point>& v1, vector<Point>& v2){
  
  vector<Point> result;
  vector<Point> temp;
  
  Point s1,s2,i1,i2;
  
  //non-intersection case
  for(unsigned  int i=0; i<v1.size();i++){   //4
    unsigned int n=0;
    //check v1[i]
    for(unsigned int j=0; j< v2.size();j++){  //4
      if(j==v2.size()-1){
        if(inside(v1[i],v2[j],v2[0])){
          n++;
        }
        
      }else{
        if(inside(v1[i],v2[j],v2[j+1])){
          n++;
        }
        
      }
    }
    //if v1[i] inside ,add to temp
    
    if(n==v2.size())
      temp.push_back(v1[i]);
    
  }
  
  
  for(unsigned  int i=0; i<v2.size();i++){   //4
    unsigned int n=0;
    //check v1[i]
    for(unsigned int j=0; j< v1.size();j++){  //4
      if(j==v1.size()-1){
        if(inside(v2[i],v1[j],v1[0])){
          n++;
        }
        
      }else{
        if(inside(v2[i],v1[j],v1[j+1])){
          n++;
        }
        
      }
    }
    if(n==v1.size())
      temp.push_back(v2[i]);
    
  }
  
  std::cout<<"v2:temp_size:  "<<temp.size()<<'\n';	
  
  //Point computeIntersection(Point s1, Point s2, Point i1, Point i2){
  //get the intersection
  
  
  for(unsigned int i=0; i<v1.size();i++){
    //set two point s1,s2
    if(i==v1.size()-1){
      s1=v1[i];
      s2=v1[0];
    }else{
      s1=v1[i];
      s2=v1[i+1];
    }
    
    for(unsigned int j=0; j<v2.size();j++){
      if(j==v2.size()-1){
        i1=v2[j];
        i2=v2[0];
      }else{
        i1=v2[j];
        i2=v2[j+1];
      }
      if(doIntersect(s1,s2,i1,i2)){
        Point newp = computeIntersection(s1,s2,i1,i2);
        temp.push_back(newp);
      }
      
    }
    
    
  }
  
  sortByAngle(temp);
  return temp;
  
  
}

// Given three colinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
bool onSegment(Point p, Point q, Point r)
{
  if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
      q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
    return true;
  
  return false;
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point p, Point q, Point r)
{
  // See https://www.geeksforgeeks.org/orientation-3-ordered-points/
  // for details of below formula.
  int val = (q.y - p.y) * (r.x - q.x) -
    (q.x - p.x) * (r.y - q.y);
  
  if (val == 0) return 0;  // colinear
  
  return (val > 0)? 1: 2; // clock or counterclock wise
}

bool doIntersect(Point p1, Point q1, Point p2, Point q2)
{
  // Find the four orientations needed for general and
  // special cases
  int o1 = orientation(p1, q1, p2);
  int o2 = orientation(p1, q1, q2);
  int o3 = orientation(p2, q2, p1);
  int o4 = orientation(p2, q2, q1);
  
  // General case
  if (o1 != o2 && o3 != o4)
    return true;
  
  // Special Cases
  // p1, q1 and p2 are colinear and p2 lies on segment p1q1
  if (o1 == 0 && onSegment(p1, p2, q1)) return true;
  
  // p1, q1 and p2 are colinear and q2 lies on segment p1q1
  if (o2 == 0 && onSegment(p1, q2, q1)) return true;
  
  // p2, q2 and p1 are colinear and p1 lies on segment p2q2
  if (o3 == 0 && onSegment(p2, p1, q2)) return true;
  
  // p2, q2 and q1 are colinear and q1 lies on segment p2q2
  if (o4 == 0 && onSegment(p2, q1, q2)) return true;
  
  return false; // Doesn't fall in any of the above cases
}

