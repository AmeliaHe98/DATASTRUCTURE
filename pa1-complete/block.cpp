#include "block.h"
#include <iostream>

//Returns the width of the current block.
int Block::width() const{
    return data[0].size();
}

// Returns the height of the current block.
int Block::height() const{
    return data.size();
}

//From im, grabs the rows by cols block of pixels whose upper left corner is position (upLeftX,upLeftY).
void Block::build(PNG & im, int upLeftX, int upLeftY, int cols, int rows) {
    for(int y=0; y<rows; y++){ // Starts from a row;
        vector<HSLAPixel> row;  // HSLAPixel is an object, it can only be saved by pointer; col save a row of HSLAPixes
        for (int x = 0; x<cols; x++){
            HSLAPixel* p = im.getPixel(upLeftX+x, upLeftY+y);
            row.push_back(*p);
        }
        data.push_back(row); // save a row of HSLAPixes
    }
    return;
}

//Draws the current block at position (upLeftX,upLeftY) in im.
void Block::render(PNG & im, int upLeftX, int upLeftY) const {
    for(int y = 0; y<height(); y++){
        for(int x = 0; x<width();x++){
            HSLAPixel* curr = im.getPixel(upLeftX+x,upLeftY+y);
            *curr = data[y][x];
        }
    }
    
    return;
}
