/**
 * @file main.cpp
 * A simple C++ program that manipulates an image.
 *
 * @author CS 221: Basic Algorithms and Data Structures
**/

#include "chain.h"
#include "block.h"
#include "PNGutil.h"
#include "cs221util/PNG.h"
using namespace cs221util;

int main() {
   PNG png1;
    png1.readFromFile("images/rosegarden.png");
    Chain h(png1,1,16);
    h.rotate(0);
    PNG result10 = h.render(1,16);
    std::cout<<"--------Rotate-------"<<std::endl;
    result10.writeToFile("images/out-rotate.png");

   png1.readFromFile("images/rosegarden.png");
   PNG result1 = grayscale(png1);
   result1.writeToFile("images/out-ubcRose.png");

   Block b;
   b.build(png1,0,150,450,225);
    std::cout<<"------Build------"<<endl;
   b.render(result1,450,300);
   result1.writeToFile("images/out-blocktest.png");
    std::cout<<"-----Render-------"<<std::endl;
   Chain c(png1,1,16);
   for (int i = 1; i < c.size(); i*=2){
      c.moveToBack(1+c.size()*(i-1)/i, c.size()/(2*i));
   }
   PNG result2 = c.render(1,16);
   result2.writeToFile("images/out-moveToBack.png");

   Chain d(png1,2,8);
   d.swap(7,8);
   PNG result3 = d.render(2,8);
   result3.writeToFile("images/out-swapEasy.png");
    std::cout<<"--------Swap--------"<<std::endl;
   Chain e(png1,4,18);

   Chain g(e);
   Chain f(result1,4,18);
   std::cout<<"--------Twist-------"<<std::endl;
   g.twist(f);
   PNG result6 = g.render(4,18);
   PNG result7 = f.render(4,18);
   result6.writeToFile("images/out-twistSame1.png");
   result7.writeToFile("images/out-twistSame2.png");
    
    //define png
    PNG png2;
    png2.readFromFile("images/rosegarden.png");
    PNG result8 = ubcify(png2);
    std::cout<<"--------UBCIfy-------"<<std::endl;
    result8.writeToFile("images/out-ubcRose2.png");

   return 0;
}
