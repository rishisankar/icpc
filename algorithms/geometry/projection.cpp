#include <bits/stdc++.h>
using namespace std; 
typedef long double ld;

template<class T> struct Point3D {
	typedef Point3D P;
	typedef const P& R;
	T x, y, z;
	explicit Point3D(T x=0, T y=0, T z=0) : x(x), y(y), z(z) {}
	bool operator<(R p) const {
		return tie(x, y, z) < tie(p.x, p.y, p.z); }
	bool operator==(R p) const {
		return tie(x, y, z) == tie(p.x, p.y, p.z); }
	P operator+(R p) const { return P(x+p.x, y+p.y, z+p.z); }
	P operator-(R p) const { return P(x-p.x, y-p.y, z-p.z); }
	P operator*(T d) const { return P(x*d, y*d, z*d); }
	P operator/(T d) const { return P(x/d, y/d, z/d); }
	T dot(R p) const { return x*p.x + y*p.y + z*p.z; }
	P cross(R p) const {
		return P(y*p.z - z*p.y, z*p.x - x*p.z, x*p.y - y*p.x);
	}
	T dist2() const { return x*x + y*y + z*z; }
	double dist() const { return sqrt((double)dist2()); }
	//Azimuthal angle (longitude) to x-axis in interval [-pi, pi]
	double phi() const { return atan2(y, x); } 
	//Zenith angle (latitude) to the z-axis in interval [0, pi]
	double theta() const { return atan2(sqrt(x*x+y*y),z); }
	P unit() const { return *this/(T)dist(); } //makes dist()=1
	//returns unit vector normal to *this and p
	P normal(P p) const { return cross(p).unit(); }
	//returns point rotated 'angle' radians ccw around axis
	P rotate(double angle, P axis) const {
		double s = sin(angle), c = cos(angle); P u = axis.unit();
		return u*dot(u)*(1-c) + (*this)*c - cross(u)*s;
	}
};


/*
Projection of point P onto line containing points a,b
*/
Point3D<ld> projection(Point3D<ld> P, Point3D<ld> a, Point3D<ld> b) {
  // projection of point on line: A + dot(AP,AB) / dot(AB,AB) * AB
	Point3D<ld> v = b-a;
  ld scale = v.dot(P-a) / v.dot(v);
	return Point3D<ld>(a.x+scale*v.x, a.y+scale*v.y, a.z+scale*v.z);
}

int main() {
  Point3D<ld> P(5, 1, 0);
  Point3D<ld> a(0,0,0);
  Point3D<ld> b(10,0,0);
  Point3D<ld> res = projection(P, a, b);
  cout << res.x << ' ' << res.y << ' ' << res.z << '\n';
}