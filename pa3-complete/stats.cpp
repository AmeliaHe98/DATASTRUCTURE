#include "stats.h"
#include <cmath>
#include <vector>
#include <iostream>
using namespace std;

/* returns the sums of all pixel values across all color channels.
 * useful in computing the score of a rectangle*/
long stats::getSum(char channel, pair<int,int> ul, pair<int,int> lr){
    int x1 = ul.first;
    int y1 = ul.second;
    int x2 = lr.first;
    int y2 = lr.second;

    if(channel == 'r'){
        if(x1 == 0 && y1 == 0){
            return sumRed[x2][y2];
        }
        if(x1 == 0  && y1 != 0){
            return sumRed[x2][y2] - sumRed[x2][y1-1];
        }
        if(y1 == 0 && x1 != 0 ){
            return sumRed[x2][y2] - sumRed[x1-1][y2];
        }
        return sumRed[x2][y2] - sumRed[x2][y1-1] -
        sumRed[x1-1][y2] + sumRed[x1-1][y1 -1];

    }

    else if(channel == 'g'){
        if(x1 == 0 && y1 == 0){
            return sumGreen[x2][y2];;
        }
        if(x1 == 0  && y1 != 0){
            return sumGreen[x2][y2] - sumGreen[x2][y1-1];
        }
        if(y1 == 0 && x1 != 0 ){
            return sumGreen[x2][y2] - sumGreen[x1-1][y2];
        }
        return sumGreen[x2][y2] - sumGreen[x2][y1-1] -
        sumGreen[x1-1][y2] + sumGreen[x1-1][y1 -1];

    }
    else if(channel == 'b'){
        if(x1 == 0 && y1 == 0){
            return sumBlue[x2][y2];
        }
        if(x1 == 0  && y1 != 0){
            return sumBlue[x2][y2] - sumBlue[x2][y1-1];
        }
        if(y1 == 0 && x1 != 0 ){
            return sumBlue[x2][y2] - sumBlue[x1-1][y2];
        }
        return sumBlue[x2][y2] - sumBlue[x2][y1-1] -
        sumBlue[x1-1][y2] + sumBlue[x1-1][y1 -1];

    }
    else{
        return 0;
    }
}

/* returns the sums of squares of all pixel values across all color channels.
 * useful in computing the score of a rectangle*/
long stats::getSumSq(char channel, pair<int,int> ul, pair<int,int> lr){
    
    if(channel == 'r'){
        
        if(ul.first == 0 && ul.second == 0){
            return sumsqRed[lr.first][lr.second];
        }
        
        if(ul.first == 0){
            return sumsqRed[lr.first][lr.second] - sumsqRed[lr.first][ul.second-1];
        }
        
        if(ul.second == 0){
            
            return sumsqRed[lr.first][lr.second] - sumsqRed[ul.first-1][lr.second];
        }
        
        return sumsqRed[lr.first][lr.second] - sumsqRed[lr.first][ul.second-1] -
        sumsqRed[ul.first-1][lr.second] + sumsqRed[ul.first-1][ul.second -1];
    }
    
    else if(channel == 'g'){
        
        if(ul.first == 0 && ul.second == 0){
            return sumsqGreen[lr.first][lr.second];
        }
        
        if(ul.first == 0){
            return sumsqGreen[lr.first][lr.second] - sumsqGreen[lr.first][ul.second-1];
        }
        
        if(ul.second == 0){
            
            return sumsqGreen[lr.first][lr.second] - sumsqGreen[ul.first-1][lr.second];
        }
        return sumsqGreen[lr.first][lr.second] - sumsqGreen[lr.first][ul.second-1] -
        sumsqGreen[ul.first-1][lr.second] + sumsqGreen[ul.first-1][ul.second -1];
    }
    
    else if(channel == 'b'){
        if(ul.first == 0 && ul.second == 0){
            return sumsqBlue[lr.first][lr.second];
        }
        
        if(ul.first == 0){
            return sumsqBlue[lr.first][lr.second] - sumsqBlue[lr.first][ul.second-1];
        }
        
        if(ul.second == 0){
            
            return sumsqBlue[lr.first][lr.second] - sumsqBlue[ul.first-1][lr.second];
        }
        return sumsqBlue[lr.first][lr.second] - sumsqBlue[lr.first][ul.second-1] -
        sumsqBlue[ul.first-1][lr.second] + sumsqBlue[ul.first-1][ul.second -1];
        
    }
    else{
        return 0;
    }
    
}


// initialize the private vectors so that, for each color,  entry
// (x,y) is the cumulative sum of the the color values from (0,0)
// to (x,y). Similarly, the sumSq vectors are the cumulative
// sum of squares from (0,0) to (x,y).
stats::stats(PNG & im)
{
    int width = im.width();
    int height = im.height();
    long sum_R = 0;
    long sum_G = 0;
    long sum_B = 0;
    
    long sq_R = 0;
    long sq_G = 0;
    long sq_B = 0;
    
    // first row
    
    
    // initialize all vectors into 0 ,
    for(int x=0;x<width; x++){
        vector<long> col;
        for(int y=0; y<height; y++){
            col.push_back(0);
        }
        sumRed.push_back(col);
        sumGreen.push_back(col);
        sumBlue.push_back(col);
        sumsqRed.push_back(col);
        sumsqGreen.push_back(col);
        sumsqBlue.push_back(col);
    }
    
    
    for (int x=0 ; x<width; x++){
        RGBAPixel *p = im.getPixel(x,0);
        sum_R = sum_R + p->r;
        sum_G = sum_G + p->g;
        sum_B = sum_B + p->b;
        
        sq_R = sq_R + p->r*p->r ;
        sq_G = sq_G + p->g*p->g ;
        sq_B = sq_B + p->b*p->b ;
        
        
        sumRed[x][0]   = sum_R;
        sumGreen[x][0] = sum_G;
        sumBlue[x][0]  = sum_B;
        
        sumsqRed[x][0]  = sq_R;
        sumsqGreen[x][0]= sq_G;
        sumsqBlue[x][0] = sq_B;
    }
    
    // first col
    sum_R = 0;
    sum_G = 0;
    sum_B = 0;
    
    sq_R = 0 ;
    sq_G = 0 ;
    sq_B = 0 ;
    
    for (int y=0 ; y<height; y++){
        RGBAPixel *p = im.getPixel(0,y);
        sum_R = sum_R + p->r;
        sum_G = sum_G + p->g;
        sum_B = sum_B + p->b;
        
        sq_R = sq_R + p->r*p->r ;
        sq_G = sq_G + p->g*p->g ;
        sq_B = sq_B + p->b*p->b ;
        
        sumRed[0][y] = sum_R;
        sumGreen[0][y] = sum_G;
        sumBlue[0][y] = sum_B;
        
        sumsqRed[0][y]  = sq_R;
        sumsqGreen[0][y]= sq_G;
        sumsqBlue[0][y] = sq_B;
    }
    
    // general
    for (int x=1; x<width;x++){
        for(int y=1; y<height; y++){
            RGBAPixel *p = im.getPixel(x,y);
            long accR = sumRed[x-1][y]   + sumRed[x][y-1]   + p->r - sumRed[x-1][y-1];
            long accG = sumGreen[x-1][y] + sumGreen[x][y-1] + p->g - sumGreen[x-1][y-1];
            long accB = sumBlue[x-1][y]  + sumBlue[x][y-1]  + p->b - sumBlue[x-1][y-1];
            
            long acc_sq_R= sumsqRed[x-1][y]   + sumsqRed[x][y-1]   + p->r*p->r - sumsqRed[x-1][y-1];
            long acc_sq_G= sumsqGreen[x-1][y] + sumsqGreen[x][y-1] + p->g*p->g - sumsqGreen[x-1][y-1];
            long acc_sq_B= sumsqBlue[x-1][y]  + sumsqBlue[x][y-1]  + p->b*p->b - sumsqBlue[x-1][y-1];
            
            sumRed[x][y]  = accR;
            sumGreen[x][y]= accG;
            sumBlue [x][y]= accB;
            
            sumsqRed[x][y]  = acc_sq_R;
            sumsqGreen[x][y]= acc_sq_G;
            sumsqBlue[x][y] = acc_sq_B;
        }
    }
}

// given a rectangle, compute its sum of squared deviations from
// mean, over all color channels. Will be used to make split when
// building tree.
long stats::getScore(pair<int,int> ul, pair<int,int> lr){
    
    long stDevR = 0;
    long stDevB = 0;
    long stDevG = 0;
    long red = getSum('r',ul,lr);
    long blue = getSum('b',ul,lr);
    long green = getSum('g',ul,lr);
    long areaR = rectArea(ul,lr);
    if (areaR ==0){
        return 1;
    }
    stDevR = getSumSq('r',ul,lr) - ((red*red)/areaR);
    stDevB = getSumSq('b',ul,lr) - ((blue*blue)/areaR);
    stDevG = getSumSq('g',ul,lr) - ((green*green)/areaR);

    return stDevR + stDevB + stDevG;
    
}

// given a rectangle, return the average color value over the
// rectangle as a pixel. stDev -> variability
RGBAPixel stats::getAvg(pair<int,int> ul, pair<int,int> lr){
    long sumR = getSum('r', ul, lr);
    long sumG = getSum('g', ul, lr);
    long sumB = getSum('b', ul, lr);
    long numPixel = rectArea(ul,lr);
    //calculate avg for each color channel
    long avgR = sumR/numPixel;
    long avgB = sumB/numPixel;
    long avgG = sumG/numPixel;
    
    //put it into single pixel
    return RGBAPixel(avgR,avgG,avgB);
    
}

// given a rectangle, return the number of pixels in the rectangle
long stats::rectArea(pair<int,int> ul, pair<int,int> lr){
    long xlimit = lr.first - ul.first + 1;
    long ylimit = lr.second - ul.second + 1;
        return xlimit*ylimit;

}

