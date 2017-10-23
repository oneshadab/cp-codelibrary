/* Kattis /problems/dogs
Two dogs are moving along two sequence of line segments
Have to find the minimum distance between the dogs
Smaller problem - Given 2 line segments of same length,
AB and CD. A dog is moving from A to B, another from C to D.
what will be their minimum distance?
*/

#include <bits/stdc++.h>

using namespace std;

#define EPS 1e-9
#define FOR(i,N) FORR(i, 0, N)
#define FORR(i,a,b) FOTR(i, a, b, 1)
#define FOTR(i,a,b,c) for(int i=(a);i<(b);i+=(c))
#define cpp_io() {ios_base::sync_with_stdio(false);cin.tie(NULL);}

double ans;

struct point{
    double x, y;
};

double dist(const point &a, const point &b){
    return hypot(a.x-b.x, a.y-b.y);
}

point nextPoint(point a, point b, double T){
    return { (a.x+T*b.x)/(1+T), (a.y+T*b.y)/(1+T) };
}

void calc(point a, point b, point c, point d, double rt){

    double lf = 0, m1, m2, t1, t2, ds, d1, d2;
    point p1, p2, p3, p4;
    FOR(i, 100){
        ds = rt - lf;
        m1 = lf+ds/3, m2 = rt-ds/3;

        t1 = ds - m1;
        if(t1<EPS)break;
        p1 = nextPoint(a, b, m1/t1), p2 = nextPoint(c, d, m1/t1);

        t2 = ds - m2;
        if(t2<EPS)break;
        p3 = nextPoint(a, b, m2/t2), p4 = nextPoint(c, d, m2/t2);

        d1 = dist(p1, p2), d2 = dist(p3, p4);

        if(d1 < d2){
            b = p3, d = p4;
        }
        else {
            a = p1, c = p2;
        }
    }
    ans = min(ans, min(d1,d2));
}

int main(){
    cpp_io();
    int n, m, it1, it2;
    while(cin>>n){
        vector<point> d1, d2;
        d1.resize(n);
        FOR(i, n)cin>>d1[i].x>>d1[i].y;
        cin>>m;
        d2.resize(m);
        FOR(i, m)cin>>d2[i].x>>d2[i].y;

        it1=it2=1;
        point c1=d1[0], c2=d2[0], pr1, pr2;
        double dst1, dst2;
        ans = 1e15;
        while(it1<n && it2<m){
            pr1 = c1, pr2 = c2;
            dst1 = dist(c1, d1[it1]);
            dst2 = dist(c2, d2[it2]);
            if(fabs(dst1-dst2)<EPS){
                c1 = d1[it1++];
                c2 = d2[it2++];
            }
            else if(dst1<dst2){
                c1 = d1[it1++];
                c2 = nextPoint(c2, d2[it2], dst1/(dst2-dst1));
            }
            else {
                c1 = nextPoint(c1, d1[it1], dst2/(dst1-dst2));
                c2 = d2[it2++];
            }
            calc(pr1, c1, pr2, c2, min(dst1, dst2));
        }
        cout<<fixed<<setprecision(10)<<ans<<"\n";
    }
}