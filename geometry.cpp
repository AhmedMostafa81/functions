// Constants & Point Structure
using ld = long double;
const ld EPS = 1e-12;
const ld PI = acosl(-1.0L);

int sgn(ld x) { return (x > EPS) - (x < -EPS); }

struct P {
    ld x, y;
    P() {}
    P(ld _x, ld _y) : x(_x), y(_y) {}

    P operator + (const P& o) const { return P(x + o.x, y + o.y); }
    P operator - (const P& o) const { return P(x - o.x, y - o.y); }
    P operator * (ld k) const { return P(x * k, y * k); }
    P operator / (ld k) const { return P(x / k, y / k); }
};



//Dot Product
ld dot(P a, P b) { return a.x*b.x + a.y*b.y; }


//Cross Product
ld cross(P a, P b) { return a.x*b.y - a.y*b.x; }
ld cross(P a, P b, P c) { return cross(b - a, c - a); } // orientation


//Length & Distance
ld norm(P a) { return sqrtl(dot(a, a)); }
ld dist(P a, P b) { return norm(a - b); }


//Rotate Point by Angle
P rotate(P a, ld ang) {
    return P(a.x*cosl(ang) - a.y*sinl(ang),
            a.x*sinl(ang) + a.y*cosl(ang));
}


//Line Representation
struct Line {
    P v; ld c; // v = direction, cross(v, p) = c

    Line(P a, P b) { v = b - a; c = cross(v, a); }
};


//Check Parallel Lines
bool parallel(Line a, Line b) {
    return sgn(cross(a.v, b.v)) == 0;
}


//Line Intersection
bool lineIntersection(Line a, Line b, P &out) {
    ld d = cross(a.v, b.v);
    if (sgn(d) == 0) return false;
    out = (b.v * a.c - a.v * b.c) / d;
    return true;
}


//Check Point on Segment
bool onSegment(P a, P b, P p) {
    return sgn(cross(a, b, p)) == 0 &&
           sgn(dot(p - a, p - b)) <= 0;
}


//Segment Intersection
bool segInter(P a, P b, P c, P d) {
    ld d1 = cross(a, b, c), d2 = cross(a, b, d);
    ld d3 = cross(c, d, a), d4 = cross(c, d, b);

    if (sgn(d1)*sgn(d2) < 0 && sgn(d3)*sgn(d4) < 0) return true;
    if (sgn(d1)==0 && onSegment(a,b,c)) return true;
    if (sgn(d2)==0 && onSegment(a,b,d)) return true;
    if (sgn(d3)==0 && onSegment(c,d,a)) return true;
    if (sgn(d4)==0 && onSegment(c,d,b)) return true;
    return false;
}


//Distance Point → Line
ld distPointLine(P a, P b, P p) {
    return fabsl(cross(b - a, p - a)) / norm(b - a);
}

//Distance Point → Segment
ld distPointSeg(P a, P b, P p) {
    if (dot(b - a, p - a) < 0) return norm(p - a);
    if (dot(a - b, p - b) < 0) return norm(p - b);
    return distPointLine(a, b, p);
}


//Polygon Area
ld polygonArea(vector<P>& p) {
    ld a = 0;
    for (int i = 0; i < p.size(); i++)
        a += cross(p[i], p[(i+1)%p.size()]);
    return fabsl(a) / 2;
}

//Point in Polygon (Ray Casting)
bool pointInPoly(vector<P>& poly, P p) {
    bool in = false;
    for (int i = 0, j = poly.size()-1; i < poly.size(); j = i++) {
        if (onSegment(poly[i], poly[j], p)) return true;
        bool cond = ((poly[i].y > p.y) != (poly[j].y > p.y)) &&
                    (p.x < (poly[j].x - poly[i].x) * (p.y - poly[i].y) /
                     (poly[j].y - poly[i].y) + poly[i].x);
        if (cond) in = !in;
    }
    return in;
}

//Circle Structure
struct Circle {
    P o; ld r;
    Circle(P _o, ld _r) : o(_o), r(_r) {}
};

//Line–Circle Intersection
vector<P> lineCircle(P a, P b, Circle c) {
    P h = a + (b - a) * (dot(c.o - a, b - a) / dot(b - a, b - a));
    ld d = dist(h, c.o);
    if (d > c.r + EPS) return {};
    ld x = sqrtl(max((ld)0, c.r*c.r - d*d));
    P dir = (b - a) / norm(b - a);
    if (sgn(x) == 0) return {h};
    return {h - dir*x, h + dir*x};
}


//Circle–Circle Intersection Points
vector<P> circleCircle(Circle a, Circle b) {
    ld d = dist(a.o, b.o);
    if (d > a.r + b.r + EPS) return {};
    if (d < fabsl(a.r - b.r) - EPS) return {};

    ld x = (d*d - b.r*b.r + a.r*a.r) / (2*d);
    ld y = sqrtl(max((ld)0, a.r*a.r - x*x));

    P v = (b.o - a.o) / d;
    P p = a.o + v*x;
    P per(-v.y, v.x);

    if (sgn(y) == 0) return {p};
    return {p - per*y, p + per*y};
}

//Area of Circle
ld circleArea(ld r) { return PI * r * r; }


//Area of Intersection of Two Circles
ld circleIntersectionArea(Circle a, Circle b) {
    ld d = dist(a.o, b.o);
    if (d >= a.r + b.r) return 0;
    if (d <= fabsl(a.r - b.r)) {
        ld r = min(a.r, b.r);
        return PI * r * r;
    }
    ld alpha = acosl((a.r*a.r + d*d - b.r*b.r)/(2*a.r*d)) * 2;
    ld beta  = acosl((b.r*b.r + d*d - a.r*a.r)/(2*b.r*d)) * 2;
    return 0.5*a.r*a.r*(alpha - sinl(alpha)) +
           0.5*b.r*b.r*(beta - sinl(beta));
}


//Convex Hull (Monotone Chain)
/*
  Version 1: Keeps collinear points on edges
  cross(...) <= 0   →   cross(...) < 0

*/

bool cmpP(P a, P b){ return a.x<b.x || (a.x==b.x && a.y<b.y); }

vector<P> convexHull(vector<P> pts) {
    sort(pts.begin(), pts.end(), cmpP);
    vector<P> h;

    for (int t=0; t<2; t++) {
        int start = h.size();
        for (P p: pts) {
            while (h.size() >= start+2 &&
                   cross(h[h.size()-2], h.back(), p) <= 0) // removes collinear
                h.pop_back();
            h.push_back(p);
        }
        h.pop_back();
        reverse(pts.begin(), pts.end());
    }
    if (h.size()==1) return h;
    return h;
}


//Angle Between Two Vectors
ld angle(P a, P b) {
    return acosl(max((ld)-1, min((ld)1, dot(a,b)/(norm(a)*norm(b)))));
}


//Distance Between Two Lines
ld distLineLine(P a, P b, P c, P d) {
    if (sgn(cross(b-a, d-c)) != 0) return 0; // they intersect
    return distPointLine(a, b, c);
}


//Tangents from Point to Circle
vector<P> tangentsFromPoint(P p, Circle c) {
    P v = p - c.o;
    ld d = norm(v);
    if (d < c.r - EPS) return {}; // inside circle

    ld ang = acosl(c.r / d);
    P u = v / d;
    return {
        c.o + rotate(u, ang) * c.r,
        c.o + rotate(u, -ang) * c.r
    };
}





