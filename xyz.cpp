#include "xyz.h"

XYZ::XYZ() :
  x(0.0),
  y(0.0),
  z(0.0)
{
}

XYZ::XYZ(double xNew, double yNew, double zNew) :
  x(xNew),
  y(yNew),
  z(zNew)
{
}

void XYZ::normalise()
{
  double length = sqrt(x*x + y*y + z*z);
  x /= length;
  y /= length;
  z /= length;
}

XYZ operator + (const XYZ& a, const XYZ& b) {
  return XYZ(a.x + b.x,a.y + b.y,a.z + b.z);
}

XYZ operator - (const XYZ& a, const XYZ& b) {
  return XYZ(a.x - b.x,a.y - b.y,a.z - b.z);
}

XYZ operator * (double a, const XYZ& b) {
  return XYZ(a*b.x,a*b.y,a*b.z);
}

double operator * (const XYZ& a, const XYZ& b) {
  return a.x*b.x + a.y*b.y + a.z*b.z;
}

XYZ cross(const XYZ& a, const XYZ& b) {
  return XYZ(a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x);
}

XYZ rotate(const XYZ& r, const XYZ& n, double theta) {
  double c = cos(theta);
  double s = sin(theta);
  return (1.0-c)*(n*r)*n + c*r - s*cross(n,r);
}

bool pbc(const XYZ& xyzMin, const XYZ& xyzMax, const XYZ& r1, XYZ& r2) {
  double dx = xyzMax.x - xyzMin.x;
  double dy = xyzMax.y - xyzMin.y;
  double dz = xyzMax.z - xyzMin.z;
  double dxHalf = 0.5 * dx;
  double dyHalf = 0.5 * dy;
  double dzHalf = 0.5 * dz;

  bool wrapped = false;

  if (r2.x - r1.x > dxHalf) {
    r2.x -= dx;
    wrapped = true;
  }
  else if (r2.x - r1.x < -dxHalf) {
    r2.x += dx;
    wrapped = true;
  }
  if (r2.y - r1.y > dyHalf) {
    r2.y -= dy;
    wrapped = true;
  }
  else if (r2.y - r1.y < -dyHalf) {
    r2.y += dy;
    wrapped = true;
  }
  if (r2.z - r1.z > dzHalf) {
    r2.z -= dz;
    wrapped = true;
  }
  else if (r2.z - r1.z < -dzHalf) {
    r2.z += dz;
    wrapped = true;
  }

  return wrapped;
}
