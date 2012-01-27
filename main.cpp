/*
 * File:   main.cpp
 * Author: rturnau
 *
 * Created on January 26, 2012, 9:04 AM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

class point {
public:
    point() : x(0), y(0) {};
    point(int x, int y) : x(x), y(y) {};
   
    int x;
    int y;
};

int min(int n1, int n2) {
    int min = n2;
    if (n1 <= n2) {
        min = n1;
    }
    return min;
}

int max(int n1, int n2) {
    int max = n2;
    if (n1 >= n2) {
        max = n1;
    }
    return max;
}


int cross_product(point p1, point p2) {
    return (p1.x * p2.y) - (p2.x * p1.y);
}

// Using p0 as the origin, determine if the vector p0-p1
// is to the right or the left or straight ahead of p0-02
// from CLRS 33.1
int find_direction (point p0, point p1, point p2) {
    return ((p1.x - p0.x) * (p2.y - p0.y)) - ((p2.x - p0.x) * (p1.y - p0.y));
}


// Determine if point p2 is on the line segment described by 
// points p0 and p2
bool on_segment(point p0, point p1, point p2) {
    bool ret = false;
    if ((min(p0.x, p1.x) <= p2.x) && (p2.x <= max(p0.x, p1.x))
            && ((min(p0.y, p1.y) <= p2.y) && (p2.y <= max(p0.y, p1.y)))) {
        ret = true;
    }
    return ret;
}

// determines if a line p1-p2 intersects line p3-p4
// In the real world, I'd encapsulate the line segment into its own
// class...
bool segments_intersect(point p1, point p2, point p3, point p4 ) {
    int d1 = find_direction(p3, p4, p1);
    int d2 = find_direction(p3, p4, p2);
    int d3 = find_direction(p1, p2, p3);
    int d4 = find_direction(p1, p2, p4);
    
    if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0))
                && ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))) {
        return true;
    } else if ((d1 == 0) && on_segment(p3, p4, p1)) {
        return true;
    } else if ((d2 == 0) && on_segment(p3, p4, p2)) {
        return true;
    } else if ((d3 == 0) && on_segment(p1, p2, p3)) {
        return true;
    } else if ((d4 == 0) && on_segment(p1, p2, p4)) {
        return true;
    }
    return false;
}



/*
 *
 */
int main(int argc, char** argv) {
    //ofstream fout("points.out");
    ifstream fin("points.in");
    int n = 0;
    fin >> n;

    point points[n];
    int x, y;
    for (int i = 0; i < n; i++) {
        fin >> x >> y;
        points[i] = point(x, y);
    }
   
   
   
    cout << "cross product of (" << points[0].x << "," << points[0].y << ") and (" << points[1].x << "," << points[1].y << "): " << cross_product(points[0], points[1]) << "\n";
   
    cout << "direction of line (" <<  points[0].x << "," << points[0].y << ") and (" << points[2].x << "," << points[2].y
            << ") from line (" << points[0].x << "," << points[0].y
            << ") and (" << points[1].x << "," << points[1].y << ")\n";
    cout << find_direction (points[0], points[1], points[2]);

    return 0;
}


