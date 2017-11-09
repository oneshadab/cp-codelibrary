#include <bits/stdc++.h>

using namespace std;

#define sqr(x) ((x)*(x))
#define mp make_pair
#define pb push_back

const double eps = 1e-10;
const double pi = acos(-1.0);
const double inf = 1e20;
const int maxp = 10;

int dblcmp(double d) {
    if (fabs(d) < eps) return 0;
    return d > eps ? 1 : -1;
}

struct point {
    double x, y;
    point() {}
    point(double _x, double _y) :
            x(_x), y(_y) {
    };
    bool operator==(point a)const {
        return dblcmp(a.x - x) == 0 && dblcmp(a.y - y) == 0;
    }
    bool operator<(point a)const {
        return dblcmp(a.x - x) == 0 ? dblcmp(y - a.y) < 0 : x < a.x;
    }
    double len() {
        return hypot(x, y);
    }
    double len2() {
        return x*x + y*y;
    }
    double distance(point p) {
        return hypot(x - p.x, y - p.y);
    }
    point add(point p) {
        return point(x + p.x, y + p.y);
    }
    point sub(point p) {
        return point(x - p.x, y - p.y);
    }
    point mul(double b) {
        return point(x*b, y*b);
    }
    point div(double b) {
        return point(x / b, y / b);
    }
    double dot(point p) {
        return x*p.x + y*p.y;
    }
    double det(point p) {
        return x*p.y - y*p.x;
    }
    double rad(point a, point b) {
        point p = *this;
        return fabs(atan2(fabs(a.sub(p).det(b.sub(p))), a.sub(p).dot(b.sub(p))));
    }
    point trunc(double r) {
        double l = len();
        if (!dblcmp(l))return *this;
        r /= l;
        return point(x*r, y*r);
    }
    point rotleft() {
        return point(-y, x);
    }
    point rotright() {
        return point(y, -x);
    }
    point rotate(point p, double angle) { // P counterclockwise rotation angle around the point angle
        point v = this->sub(p);
        double c = cos(angle), s = sin(angle);
        return point(p.x + v.x*c - v.y*s, p.y + v.x*s + v.y*c);
    }
};

struct line {
    point a, b;
    line() {}
    line(point _a, point _b) {
        a = _a;
        b = _b;
    }
    double length() {
        return a.distance(b);
    }

    /*
    Points and line segments between
    1 Counter clockwise
    2 in a clockwise
    3 parallel
    */
    int relation(point p) {
        int c = dblcmp(p.sub(a).det(b.sub(a)));
        if (c < 0)return 1;
        if (c > 0)return 2;
        return 3;
    }
    bool parallel(line v) {
        return dblcmp(b.sub(a).det(v.b.sub(v.a))) == 0;
    }

    /* 0 Parallel
    1 coincides
    2 intersect */
    int linecrossline(line v) {
        if ((*this).parallel(v)) {
            return v.relation(a) == 3;
        }
        return 2;
    }
    point crosspoint(line v) {
        double a1 = v.b.sub(v.a).det(a.sub(v.a));
        double a2 = v.b.sub(v.a).det(b.sub(v.a));
        return point((a.x*a2 - b.x*a1) / (a2 - a1), (a.y*a2 - b.y*a1) / (a2 - a1));
    }
    double dispointtoline(point p) {
        return fabs(p.sub(a).det(b.sub(a))) / length();
    }
    point lineprog(point p) {
        return a.add(b.sub(a).mul(b.sub(a).dot(p.sub(a)) / b.sub(a).len2()));
    }
};

struct circle {
    point p;
    double r;
    circle() {}
    circle(point _p, double _r) :
            p(_p), r(_r) {
    };
    circle(double x, double y, double _r) :
            p(point(x, y)), r(_r) {
    };
    circle(point a, point b, point c){ //Circumcircle of triangle
        p = line(a.add(b).div(2),a.add(b).div(2).add(b.sub(a).rotleft())).crosspoint(line(c.add(b).div(2), c.add(b).div(2).add(b.sub(c).rotleft())));
        r = p.distance(a);
    }
    double area() {
        return pi*sqr(r);
    }
    bool operator==(circle v) {
        return ((p == v.p) && dblcmp(r - v.r) == 0);
    }
    bool operator<(circle v)const {
        return ((p < v.p) || (p == v.p) && dblcmp(r - v.r) < 0);
    }
    int relation(point b) {
        double dst = b.distance(p);
        if (dblcmp(dst - r) < 0)return 2;
        if (dblcmp(dst - r) == 0)return 1;
        return 0;
    }
    int relationcircle(circle v) {
        double d = p.distance(v.p);
        if (dblcmp(d - r - v.r) > 0)return 5;
        if (dblcmp(d - r - v.r) == 0)return 4;
        double l = fabs(r - v.r);
        if (dblcmp(d - r - v.r) < 0 && dblcmp(d - l) > 0)return 3;
        if (dblcmp(d - l) == 0)return 2;
        if (dblcmp(d - l) < 0)return 1;
    }
    int relationline(line v) {
        double dst = v.dispointtoline(p);
        if (dblcmp(dst - r) < 0)return 2;
        if (dblcmp(dst - r) == 0)return 1;
        return 0;
    }
    int pointcrossline(line v, point &p1, point &p2){
        if (!(*this).relationline(v))return 0;
        point a = v.lineprog(p);
        double d = v.dispointtoline(p);
        d = sqrt(r*r - d*d);
        if (dblcmp(d) == 0) {
            p1 = a;
            p2 = a;
            return 1;
        }
        p1 = a.sub(v.b.sub(v.a).trunc(d));
        p2 = a.add(v.b.sub(v.a).trunc(d));
        return 2;
    }
    double areacircle(circle v) {
        int rel = relationcircle(v);
        if (rel >= 4)return 0.0;
        if (rel <= 2)return min(area(), v.area());
        double d = p.distance(v.p);
        double hf = (r + v.r + d) / 2.0;
        double ss = 2 * sqrt(hf*(hf - r)*(hf - v.r)*(hf - d));
        double a1 = acos((r*r + d*d - v.r*v.r) / (2.0*r*d));
        a1 = a1*r*r;
        double a2 = acos((v.r*v.r + d*d - r*r) / (2.0*v.r*d));
        a2 = a2*v.r*v.r;
        return a1 + a2 - ss;
    }
    double areatriangle(point a, point b) {
        if (dblcmp(p.sub(a).det(p.sub(b)) == 0))return 0.0;
        point q[5];
        int len = 0;
        q[len++] = a;
        line l(a, b);
        point p1, p2;
        if (pointcrossline(l, q[1], q[2]) == 2) {
            if (dblcmp(a.sub(q[1]).dot(b.sub(q[1]))) < 0)q[len++] = q[1];
            if (dblcmp(a.sub(q[2]).dot(b.sub(q[2]))) < 0)q[len++] = q[2];
        }
        q[len++] = b;
        if (len == 4 && (dblcmp(q[0].sub(q[1]).dot(q[2].sub(q[1]))) > 0))swap(q[1], q[2]);
        double res = 0;
        int i;
        for (i = 0; i < len - 1; i++) {
            if (relation(q[i]) == 0 || relation(q[i + 1]) == 0) {
                double arg = p.rad(q[i], q[i + 1]);
                res += r*r*arg / 2.0;
            }
            else {
                res += fabs(q[i].sub(p).det(q[i + 1].sub(p)) / 2.0);
            }
        }
        return res;
    }
};

struct polygon {
    int n;
    point p[maxp];
    bool isconvex() {
        bool s[3];
        memset(s, 0, sizeof(s));
        int i, j, k;
        for (i = 0; i < n; i++) {
            j = (i + 1) % n;
            k = (j + 1) % n;
            s[dblcmp(p[j].sub(p[i]).det(p[k].sub(p[i]))) + 1] = 1;
            if (s[0] && s[2])return 0;
        }
        return 1;
    }
    double getcircumference() {
        double sum = 0;
        int i;
        for (i = 0; i < n; i++) {
            sum += p[i].distance(p[(i + 1) % n]);
        }
        return sum;
    }
    double getarea() {
        double sum = 0;
        int i;
        for (i = 0; i < n; i++) {
            sum += p[i].det(p[(i + 1) % n]);
        }
        return fabs(sum) / 2;
    }

    double areacircle(circle c) { // area of intersection of polygon and circle
        int i, j, k, l, m;
        double ans = 0;
        for (i = 0; i < n; i++) {
            int j = (i + 1) % n;
            if (dblcmp(p[j].sub(c.p).det(p[i].sub(c.p))) >= 0) {
                ans += c.areatriangle(p[i], p[j]);
            }
            else {
                ans -= c.areatriangle(p[i], p[j]);
            }
        }
        return fabs(ans);
    }
    void find(int st, point tri[], circle &c) {
        if (!st) {
            c = circle(point(0, 0), -2);
        }
        if (st == 1) {
            c = circle(tri[0], 0);
        }
        if (st == 2) {
            c = circle(tri[0].add(tri[1]).div(2), tri[0].distance(tri[1]) / 2.0);
        }
        if (st == 3) {
            c = circle(tri[0], tri[1], tri[2]);
        }
    }
    void solve(int cur, int st, point tri[], circle &c) {
        find(st, tri, c);
        if (st == 3)return;
        int i;
        for (i = 0; i < cur; i++) {
            if (dblcmp(p[i].distance(c.p) - c.r) > 0) {
                tri[st] = p[i];
                solve(i, st + 1, tri, c);
            }
        }
    }
    circle mincircle() { //Smallest circle covering point set
        random_shuffle(p, p + n);
        point tri[4];
        circle c;
        solve(n, 0, tri, c);
        return c;
    }
};

int main(){
    return 0;
}
