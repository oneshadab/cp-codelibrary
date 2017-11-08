#include <bits/stdtr1c++.h>

#define MAX 100010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

struct Point{
    long long x, y;

    Point(){
    }

    Point(long long xi, long long yi){
        x = xi, y = yi;
    }
};

struct Segment{
    struct Point P1, P2;

    Segment(){
    }

    Segment(struct Point P1i, struct Point P2i){
        P1 = P1i, P2 = P2i;
    }
};

/// Returns 0 if ABC is collinear, positive if ABC is a left turn, negative if ABC is a right turn
long long ccw(struct Point A, struct Point B, struct Point C){
    return ((B.x - A.x) * (C.y - A.y)) - ((C.x - A.x) * (B.y - A.y));
}

/// Returns the shortest distance from Segment S to Point P
double dis(struct Segment S, struct Point P){
    double p, xx, yy;
    long long x = P.x, y = P.y, x1 = S.P1.x, y1 = S.P1.y, x2 = S.P2.x, y2 = S.P2.y;
    long long a = x - x1, b = y - y1, c = x2 - x1, d = y2 - y1, dot = (a * c) + (b * d), len = (c * c) + (d * d);

    if ((dot < 0) || (x1 == x2 && y1 == y2)) xx = x1, yy = y1;
    else if (dot > len) xx = x2, yy = y2;
    else p = (1.0 * dot) / len, xx = x1 + (p * c), yy = y1 + (p * d);
    xx = -xx + x, yy = -yy + y;
    return sqrt((xx * xx) + (yy * yy));
}

/// Returns true if Point P lies on the Segment (both end-points inclusive)
bool PointOnSeg(struct Segment S, struct Point P){
    long long x = P.x, y = P.y, x1 = S.P1.x, y1 = S.P1.y, x2 = S.P2.x, y2 = S.P2.y;
    long long a = x - x1, b = y - y1, c = x2 - x1, d = y2 - y1, dot = (a * c) + (b * d), len = (c * c) + (d * d);

    if (x1 == x2 && y1 == y2) return (x1 == x && y1 == y);
    if (dot < 0 || dot > len) return false;
    return ((((x1 * len) + (dot * c)) == (x * len)) && (((y1 * len) + (dot * d)) == (y * len)));
}

int main(){
    return 0;
}
