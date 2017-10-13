#include <bits/stdc++.h>

using namespace std;

#define FOR(i, N) FORR(i, 0, N)
#define FORR(i, a, b) FOTR(i, a, b, 1)
#define FOTR(i, a, b, c) for(int i=(a);i<(b);i+=(c))
#define cpp_io() {ios_base::sync_with_stdio(false);cin.tie(NULL);}
#define INF 1000000000

#define NXT(a, n) ((a)+1<(n)?(a)+1:(a)+1-(n))
#define LMD(a, n) ((a)<(n)?(a):(a)-(n))
#define double long double

struct point {
    double x, y;

    bool operator<(const point &p) const {
        return (x < p.x || (x == p.x && y < p.y));
    }

    point operator-(const point &a) const {
        return {x - a.x, y - a.y};
    }

    point operator/(const double val) const {
        return {x / val, y / val};
    }
};

vector<point> CH, P;

double cross(point p1, point p2, point p) {
    return (p2.x - p1.x) * (p.y - p1.y) - (p2.y - p1.y) * (p.x - p1.x);
}

double cross2(point A, point B) {
    return A.x * B.y - A.y * B.x;
}

double dot(point A, point B) {
    return A.x * B.x + A.y * B.y;
}

double dist(point A, point B) {
    return hypot(A.x - B.x, A.y - B.y);
}

void convexHull() {
    sort(P.begin(), P.end());
    int n = P.size(), k = 0;
    vector<point> H(2 * n);
    for (int i = 0; i < n; i++) {
        while (k >= 2 && cross(H[k - 2], H[k - 1], P[i]) <= 0) k--;
        H[k++] = P[i];
    }
    for (int i = n - 2, t = k + 1; i >= 0; i--) {
        while (k >= t && cross(H[k - 2], H[k - 1], P[i]) <= 0)k--;
        H[k++] = P[i];
    }
    H.resize(k);
    CH = H;
}

void smallRect() {
    int n = CH.size() - 1; // if CH[0] == CH[LAST]
    if (n < 3) {
        //cout << "0.00 0.00\n";
        //return;
    }
    int l = 1, r = 1, u = 1;
    double area = INF, per = INF;
    FOR(i, n) {
        point edge = (CH[NXT(i, n)] - CH[i]) / dist(CH[NXT(i, n)], CH[i]);

        while (dot(edge, CH[LMD(r, n)] - CH[i])
               < dot(edge, CH[NXT(r, n)] - CH[i])) r++;

        while (u < r || cross2(edge, CH[LMD(u, n)] - CH[i])
                        < cross2(edge, CH[NXT(u, n)] - CH[i])) u++;

        while (l < u || dot(edge, CH[LMD(l, n)] - CH[i])
                        > dot(edge, CH[NXT(l, n)] - CH[i])) l++;

        double w = dot(edge, CH[LMD(r, n)] - CH[i]) - dot(edge, CH[LMD(l, n)] - CH[i]);
        double h = fabs(cross2(CH[i] - CH[LMD(u, n)], CH[NXT(i, n)] - CH[LMD(u, n)]) /
                        dist(CH[i], CH[NXT(i, n)]));

        area = min(area, w * h);
        per = min(per, (w + h) * 2);
    }
    cout << fixed << setprecision(2) << area << " " << per << "\n";
}

int main() {
    cpp_io();
    int N, cs = 1;
    while (cin >> N) {
        if (N == 0)break;
        P.resize(N);
        FOR(i, N)cin >> P[i].x >> P[i].y;
        convexHull();
        smallRect();
    }
}





