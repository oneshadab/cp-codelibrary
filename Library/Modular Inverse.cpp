#include <bits/stdtr1c++.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl

using namespace std;

int extended_gcd(int a, int b, int& x, int& y){
    /// Bezout's identity, ax + by = gcd(a,b)

    if (!b){
        y = 0, x = 1;
        return a;
    }

    int g = extended_gcd(b, a % b, y, x);
    y -= ((a / b) * x);
    return g;
}

int mod_inverse(int a, int m){
    /// inverse exists if and only if a and m are co-prime

    int x, y, inv;
    extended_gcd(a, m, x, y);
    inv = (x + m) % m;
    return inv;
}

int mod_inverse(int a, int mod){
    int x, y, u, v, q, r, m, n, b;

    u = y = 0, x = v = 1, b = mod;
    while (a){
        q = (b / a), r = (b % a);
        m = u - (q * x), n = v - (q * y);
        u = x, v = y;
        x = m, y = n;
        b = a, a = r;
    }

    if (u < 0) u += mod;
    return u;
}

/* Caution, crashes when m = 1, crashes sometimes when a = m
   Sometimes returns 0 if a and m are not co-primes
   Unstable but extremely elegant
*/

int mod_inverse(int a, int m){
    if ((a < 2)) return a;
    int res = (((1LL - (long long)m * mod_inverse(m % a, a)) / (a % m)) + m) % m;
    return res;
}

int main(){
}
