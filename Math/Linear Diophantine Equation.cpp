#include <bits/stdc++.h>

using namespace std;

#define ll long long

ll egcd(ll a, ll b, ll &x, ll &y) {
    if (a == 0) {
        x = 0; y = 1;
        return b;
    }
    ll x1, y1;
    ll d = egcd (b%a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

//Ax + By = C; Doesn't handle A = B = 0
//More solutions: x' = x + (k*b) / g, y' = y - (k*a) / g
bool LDE_One(ll a, ll b, ll c, ll &x0, ll &y0, ll &g) {
    g = egcd (abs(a), abs(b), x0, y0);
    if (c % g != 0)
        return false;
    x0 *= c / g;
    y0 *= c / g;
    if (a < 0)   x0 *= -1;
    if (b < 0)   y0 *= -1;
    return true;
}

//Ax + By + C = 0
ll LDE_All(int a, int b, int c, ll x1, ll x2, ll y1, ll y2) {
    ll x, y, g;
    g = egcd(a, b, x, y);
    if (!a && !b) {
        if (c) return 0;
        return (x2 - x1 + 1) * (ll)(y2 - y1 + 1);
    }
    else if (!a) {
        if (c % b) return 0;
        c = -c / b;
        if (y1 <= c && c <= y2) return (x2 - x1 + 1);
        return 0;
    }
    else if (!b) {
        if (c % a) return 0;
        c = -c / a;
        if (x1 <= c && c <= x2) return (y2 - y1 + 1);
        return 0;
    }
    if (c % g == 0) {
        x *= (-c / g); y *= (-c / g);
        b /= g; a /= g;
        swap(a, b);
        double p = (x1 - x) / (double)a, q = (x2 - x) / (double)a;
        if (p > q) swap(p, q);
        x1 = (ll)ceil(p);
        x2 = (ll)floor(q);

        p = (y - y1) / (double)b; q = (y - y2) / (double)b;
        if (p > q) swap(p, q);
        y1 = (ll)ceil(p);
        y2 = (ll)floor(q);

        x1 = max(x1, y1); x2 = min(x2, y2);
        return max(0LL, x2 - x1 + 1);
    }
    return 0;
}

int main(){
    ll T, a,b,c,x1,y1,x2,y2;
    cin>>T;
    for(int cs = 1; cs<=T; cs++){
        cin>>a>>b>>c>>x1>>x2>>y1>>y2;
        cout<<"Case "<<cs<<": ";
        cout<<LDE_All(a,b,c,x1,x2,y1,y2)<<"\n";
    }
}