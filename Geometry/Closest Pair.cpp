#include <bits/stdc++.h>

using namespace std;

#define FOR(i, N) FORR(i, 0, N)
#define FORR(i, a, b) FOTR(i, a, b, 1)
#define FOTR(i, a, b, c) for(int i=(a);i<(b);i+=(c))
#define cpp_io() {ios_base::sync_with_stdio(false);cin.tie(NULL);}
#define MAX 10010
#define EPS 1e-9

struct point {
    double x, y;

    const bool operator<(const point &B) const {
        if (fabs(x - B.x) < EPS) return y < B.y;
        return x < B.x;
    }

} P[MAX];

double dist(const point &A, const point &B) {
    return hypot(A.x - B.x, A.y - B.y);
}

double closest(int l, int r) {
    if (l >= r) return 1e10;
    if (l + 1 == r)
        return dist(P[l], P[r]);

    int mid = (l + r) >> 1;
    double mn = min(closest(l, mid), closest(mid + 1, r));

    vector<point> LB, RB;

    for (int i = mid; i >= l && (P[mid].x - P[i].x) < mn; --i)
        LB.push_back(P[i]);
    for (int i = mid + 1; i <= r && (P[i].x - P[mid].x) < mn; ++i)
        RB.push_back(P[i]);

    FORR(i, 0, LB.size()) FORR(j, 0, RB.size()) mn = min(mn, dist(LB[i], RB[j]));

    return mn;
}

int main() {
    cpp_io();
    int N;
    while (cin >> N) {
        if (N == 0)break;
        FOR(i, N)cin >> P[i].x >> P[i].y;
        sort(P, P + N);
        double ans = closest(0, N - 1);
        if (ans < 10000.0) {
            cout << fixed << setprecision(4) << ans << "\n";
        } else cout << "INFINITY\n";
    }
}




