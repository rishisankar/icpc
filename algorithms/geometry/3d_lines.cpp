/*
Included in template
  - projection of point onto line (tested)
  - check if colinear point on line segment/ray (tested for rays)
	- distance between point and line/ray/segment (tested for rays)
	- distance between line segment and line/ray/segment (tested for rays)

Not fully tested :(
*/

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
	ld dist() const { return sqrt((ld)dist2()); }
	//Azimuthal angle (longitude) to x-axis in interval [-pi, pi]
	ld phi() const { return atan2(y, x); } 
	//Zenith angle (latitude) to the z-axis in interval [0, pi]
	ld theta() const { return atan2(sqrt(x*x+y*y),z); }
	P unit() const { return *this/(T)dist(); } //makes dist()=1
	//returns unit vector normal to *this and p
	P normal(P p) const { return cross(p).unit(); }
	//returns point rotated 'angle' radians ccw around axis
	P rotate(ld angle, P axis) const {
		ld s = sin(angle), c = cos(angle); P u = axis.unit();
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

/*
Check if a *colinear* point P is on the ray starting at a and going in direction of b
*/
bool pointOnRay(Point3D<ld> P, Point3D<ld> a, Point3D<ld> b) {
	Point3D<ld> v1 = P-a;
	Point3D<ld> v2 = b-a;
	return v1.dot(v2) >= 0;	
}

/*
Check if a *colinear* point P is on the line segment [a,b]
*/
bool pointOnSegment(Point3D<ld> P, Point3D<ld> a, Point3D<ld> b) {
	return pointOnRay(P,a,b) && pointOnRay(P,b,a);
}

/*
Distance between Point P and other linear thing

type = 0: line segment [a,b]
type = 1: ray starting at a in direction of b
type = 2: line connecting a,b
*/
ld distPoint(Point3D<ld> P, Point3D<ld> a, Point3D<ld> b, int type) {
  Point3D<ld> proj = projection(P, a, b);
  if (type == 2) {
    return (P-proj).dist();
  } else if (type == 1) {
		if (pointOnRay(proj, a, b)) {
			return (P-proj).dist();
		} else {
			return (P-a).dist();
		}
	} else {
		if (pointOnSegment(proj, a, b)) {
			return (P-proj).dist();
		} else {
			return min((P-a).dist(), (P-b).dist());
		}
	}
}

ld distLineSegmentHelper(Point3D<ld> a, Point3D<ld> b, Point3D<ld> c, Point3D<ld> d, int type, ld i) {
	ld nx = a.x + i*(b.x-a.x);
	ld ny = a.y + i*(b.y-a.y);
  ld nz = a.z + i*(b.z-a.z);
	Point3D<ld> np(nx,ny,nz);
	return -distPoint(np, c, d, type);
}

/*
Distance between line segment [a,b] and other linear thing

type = 0: line segment [c,d]
type = 1: ray starting at c in direction of d
type = 2: line connecting c,d

// see avoidingasteroids from naq21
// idea: use ternary search between end points of line segment
*/
ld distLineSegment(Point3D<ld> a, Point3D<ld> b, Point3D<ld> c, Point3D<ld> d, int type) {
  ld l = 0; 
  ld r = 1;
	  ld eps = 1e-9; // ternary search error limit
    while (r - l > eps) {
      ld m1 = l + (r - l) / 3;
      ld m2 = r - (r - l) / 3;
      ld f1 = distLineSegmentHelper(a,b,c,d,type,m1);
      ld f2 = distLineSegmentHelper(a,b,c,d,type,m2);
      if (f1 < f2) l = m1;
      else r = m2;
    }
    return -distLineSegmentHelper(a,b,c,d,type,l); // returns min dist
}
