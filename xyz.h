#ifndef xyz_header
#define xyz_header

#include <cmath>

struct XYZ {
  public:
    double x;
    double y;
    double z;
  
    XYZ();
    XYZ(double, double, double);
    
    void normalise();
};

XYZ operator + (const XYZ&, const XYZ&);
XYZ operator - (const XYZ&, const XYZ&);
XYZ operator * (double, const XYZ&);
double operator * (const XYZ&, const XYZ&);
XYZ cross(const XYZ&, const XYZ&);
XYZ rotate(const XYZ&, const XYZ&, double);

bool pbc(const XYZ&, const XYZ&, const XYZ&, XYZ&);

#endif
