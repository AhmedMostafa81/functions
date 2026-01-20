
// intersection between two circles and get the points 

struct Point {
    double x, y;
};

// returns number of intersection points (0, 1, 2)
// stores the points in p1 and p2
int circle_intersection(
    Point c1, double r1,
    Point c2, double r2,
    Point &p1, Point &p2
) {
    const double EPS = 1e-9;

    double dx = c2.x - c1.x;
    double dy = c2.y - c1.y;
    double d = hypot(dx, dy);

    // No intersection
    if (d > r1 + r2 + EPS) return 0;
    if (d < fabs(r1 - r2) - EPS) return 0;

    // Same circle (infinite intersections)
    if (d < EPS && fabs(r1 - r2) < EPS) return -1;

    // Distance from c1 to midpoint
    double a = (r1*r1 - r2*r2 + d*d) / (2*d);
    double h2 = r1*r1 - a*a;
    if (h2 < 0) h2 = 0;  // avoid precision issues
    double h = sqrt(h2);

    // Midpoint between intersection points
    double xm = c1.x + a * dx / d;
    double ym = c1.y + a * dy / d;

    // Offset vector
    double rx = -dy * (h / d);
    double ry =  dx * (h / d);

    p1 = {xm + rx, ym + ry};
    p2 = {xm - rx, ym - ry};

    if (h < EPS) return 1; // tangent
    return 2;
}
