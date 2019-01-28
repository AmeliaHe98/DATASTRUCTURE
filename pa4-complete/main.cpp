
// File:        main.cpp
// Author:      cheeren
// Date:        2018-03-31
// Description: Partial test of PA4 functionality
//              Reads Point data from external files
//              Produces PNG images of the point sets


#include "path.h"
#include "cs221util/RGBAPixel.h"
#include "cs221util/PNG.h"

using namespace cs221util;
using namespace std;

int main()
{

	PNG origIm1;
	origIm1.readFromFile("images/snake.png");
	pair<int,int> start1(2,2);
    pair<int,int> end1(637,477);
	path snake(origIm1,start1,end1);
	PNG out1 = snake.render();
	out1.writeToFile("images/snakePath.png");

	PNG origIm2;
	origIm2.readFromFile("images/maze.png");
	pair<int,int> start2(3,10);
    pair<int,int> end2(637,477);
	path maze(origIm2,start2,end2);
	PNG out2 = maze.render();
	out2.writeToFile("images/mazePath.png");

	PNG origIm3;
	origIm3.readFromFile("images/sunshine.png");
	pair<int,int> start3(320,420);
    pair<int,int> end3(100,100);
	path sunshine(origIm3,start3,end3);
	PNG out3 = sunshine.render();
	out3.writeToFile("images/sunshinePath.png");
    
    PNG origIm4;
    origIm4.readFromFile("images/mazeO.png");
    pair<int,int> start4(750,750);
    pair<int,int> end4(1391,1358);
    path mazeO(origIm4,start4,end4);
    PNG out4 = mazeO.render();
    out4.writeToFile("images/mazeOPath.png");
    
    PNG origIm5;
    origIm5.readFromFile("images/small1.png");
    pair<int,int> start5(520,50);
    pair<int,int> end5(1049, 1300);
    path small1(origIm5,start5,end5);
    PNG out5 = small1.render();
    out5.writeToFile("images/small1Path.png");

  return 0;
}
