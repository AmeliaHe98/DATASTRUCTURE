

#ifndef HSLAPIXEL_H
#define HSLAPIXEL_H


namespace cs221util{
class HSLAPixel{
public:
    double h,s,l,a;
    // Default Constructor
    HSLAPixel();
    HSLAPixel(double h0, double s0, double l0);
    HSLAPixel(double h0, double s0, double l0, double a0);
}

;
}
#endif /* HSLAPixel_h */
