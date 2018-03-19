// AffineTest.cpp
// cs250 8/17

#include <iostream>
#include <iomanip>
#include <cmath>
#include "Affine.h"
using namespace std;


ostream& operator<<(ostream& s, const Hcoord& v) {
  return s << '[' << v.x << ',' << v.y << ',' << v.z << ',' << v.w << ']';
}


ostream& operator<<(ostream& s, const Matrix& A) {
  s << '{';
  for (int i=0; i < 4; ++i) {
    s << '{';
    for (int j=0; j < 4; ++j)
      s << A[i][j] << ((j < 3) ? ',' : '}');
    s << ((i < 3) ? ',' : '}');
  }
  return s;
}


int main(void) {
  const Point O;
  const float pi = 4.0f*atan(1.0f);
  cout << fixed << setprecision(3);

  Vector v(4,-5,3);
  Affine A = translate(v) * scale(3);
  cout << A << endl;

  Point P(9,-2,-7);
  Point Q = O + 3 * (P - O) + v;

  Point R = A*P;

  cout << abs(R-Q) << endl;

  Vector u(7,5,1);
  float t = 0.3f*pi;
  A = rotate(t,v) * translate(u);
  cout << A << endl;

#if 0
  Matrix a;
  Matrix b;
  a.row[0] = Hcoord(1.0f, 0.0f, 0.0f, 1.0f);
  a.row[1] = Hcoord(2.0f, 2.0f, 1.0f, 0.0f);
  a.row[2] = Hcoord(3.0f, 2.0f, 0.0f, 1.0f);
  a.row[3] = Hcoord(1.0f, 0.0f, 2.0f, 1.0f);

  b.row[0] = Hcoord(1.0f, 0.0f, 0.0f, 1.0f);
  b.row[1] = Hcoord(2.0f, 2.0f, 1.0f, 0.0f);
  b.row[2] = Hcoord(3.0f, 2.0f, 0.0f, 1.0f);
  b.row[3] = Hcoord(1.0f, 0.0f, 2.0f, 1.0f);

  cout << a*b << endl;
#endif

  v = normalize(v);
  Q = O + cos(t)*(P+u-O) + (1-cos(t))*dot(v,P+u-O)*v + sin(t)*cross(v,P+u-O);
  R = A*P;
  cout << abs(R-Q) << endl;
  
  Affine B = Affine(Vector(5,2,1),Vector(1,4,5),Vector(9,8,2),Point(4,4,3));
  cout << B << endl;

  Affine iB = inverse(B);
  Affine result = (iB*B);
  cout << result << endl;

  u = 3*P + 2*Q - 5*R;
  cout << u << endl;
  //P = 3*P + 2*Q - 7*R; // this should fail ...

  return 0;
}

