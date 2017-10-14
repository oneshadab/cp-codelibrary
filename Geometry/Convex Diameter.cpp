#include <bits/stdc++.h>

using namespace std;

#define FOR(i,N) FORR(i, 0, N)
#define FORR(i,a,b) FOTR(i, a, b, 1)
#define FOTR(i,a,b,c) for(int i=(a);i<(b);i+=(c))
#define cpp_io() {ios_base::sync_with_stdio(false);cin.tie(NULL);}
#define ll long long
#define NXT(a, n) ((a)+1<(n)?(a)+1:(a)+1-(n))

struct point {
    ll x, y;
    bool operator <(const point &p) const {
        return (x < p.x || (x == p.x && y < p.y));
    }
    point operator-(const point &p) const {
        return {x - p.x, y - p.y};
    }
};

vector <point> CH, P;

ll cross(point p1, point p2, point p) {
    return (p2.x - p1.x) * (p.y - p1.y) - (p2.y - p1.y) * (p.x - p1.x);
}

double dist(const point &a, const point &b){
    return hypot(a.x - b.x, a.y - b.y);
}
double det(const point&a, const point &b){
    return a.x * b.y - a.y * b.x;
}
void convexHull() {
    sort(P.begin(), P.end());
    int n = P.size(), k = 0;
    vector <point> H(2 * n);
    for (int i = 0; i<n; i++) {
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

double convexDiameter(const vector<point>&ps) {
    int n = ps.size()-1; //ps[0] == ps[last]
    int is = 0, js = 0;
    for (int i = 1; i < n; ++i) {
        if (ps[i].x > ps[is].x)
            is = i;
        if (ps[i].x < ps[js].x)
            js = i;
    }
    double maxd = dist(ps[is],ps[js]);
    int i = is, j = js;
    do {
        if (det(ps[NXT(i,n)] - ps[i], ps[NXT(j,n)] - ps[j]) >= 0){
            ++j;
            if(j>=n) j-=n;
        }
        else{
            ++i;
            if(i>=n) i-=n;
        }
        maxd = max(maxd, dist(ps[i],ps[j]));
    } while (i != is || j != js);
    return maxd;
}

int main() {
    cpp_io();
    int n;
    cin>>n;
    P.resize(n);
    FOR(i, n)cin>>P[i].x >> P[i].y;
    convexHull();
    cout<<fixed<<setprecision(10)<<convexDiameter(CH)<<"\n";
}