
#include "HSLAPixel.h"

namespace cs221util {

HSLAPixel:: HSLAPixel(){
h = 0;	
s = 0;
l = 1.0;
a = 1.0;
}


HSLAPixel:: HSLAPixel(double h0, double s0, double l0){
    h = h0;
    s = s0;
    l = l0;
}
HSLAPixel:: HSLAPixel(double h0, double s0, double l0, double a0){
    h = h0;
    s = s0;
    l = l0;
    a = a0;
}
}
