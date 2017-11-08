#include <bits/stdtr1c++.h>

#define MAX 262148 /// 2 * Smallest power of 2 greater than MAXN, 2^18 when MAXN = 10^5
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

typedef complex <double> complx; /// Replace double with long double if more precision is required

complx dp[MAX >> 1], P1[MAX], P2[MAX];

inline long long round_half_even(double x){
    long long res = abs(x) + 0.5;
    if (x < 0) res = -res;
    return res;
}

void FFT(complx *ar, int n, int inv){
    int i, j, l, len, len2;
    const double p = 4.0 * inv * acos(0.0);

    for (i = 1, j = 0; i < n; i++){
        for (l = n >> 1; j >= l; l >>= 1) j -= l;
        j += l;
        if (i < j) swap(ar[i], ar[j]);
    }

    for (len = 2; len <= n; len <<= 1){
        len2 = len >> 1;
        double theta = p / len;
        complx mul(cos(theta), sin(theta));

        dp[0] = complx(1, 0);
        for (i = 1; i < len2; i++) dp[i] = (dp[i - 1] * mul);

        for (i = 0; i < n; i += len){
            complx t, *pu = ar + i, *pv = ar + i + len2, *pend = ar + i + len2, *pw = dp;
            for (; pu != pend; pu++, pv++, pw++){
                t = (*pv) * (*pw);
                *pv = *pu - t;
                *pu += t;
            }
        }
    }

    if (inv == -1){
        for (i = 0; i < n; i++) ar[i] /= n;
    }
}

void convolution(int n, complx* A, complx* B){
    int i, m, d = 0;
    if (__builtin_popcount(n) != 1){
        for (i = 0; i < n; i++) B[i + n] = B[i], A[i + n] = complx(0);
        d = n, n *= 2;
    }

    m = 1 << (32 - __builtin_clz(n) - (__builtin_popcount(n) == 1));
    for (i = n; i < m; i++) A[i] = B[i] = complx(0);

    FFT(A, m, 1), FFT(B, m, 1);
    for (i = 0; i < m; i++) A[i] = A[i] * B[i];
    FFT(A, m, -1);
    for (i = 0; i < d && d; i++) A[i] = A[i + d];
}

int multiply(int a, complx* A, int b, complx* B){
    int i, n, m;
    n = a + b - 1;
    m = 1 << (32 - __builtin_clz(n) - (__builtin_popcount(n) == 1));

    for (i = a; i < m; i++) A[i] = 0;
    for (i = b; i < m; i++) B[i] = 0;
    FFT(A, m, 1), FFT(B, m, 1);
    for (i = 0; i < m; i++) A[i] = A[i] * B[i];
    FFT(A, m, -1);
    return m;
}

/***
    Computes the circular convolution of A and B, denoted A * B, in C
    A and B must be of equal size, if not normalize before calling function
    Example to demonstrate convolution for n = 5:

    c0 = a0b0 + a1b4 + a2b3 + a3b2 + a4b1
    c1 = a0b1 + a1b0 + a2b4 + a3b3 + a4b2
    ...
    c4 = a0b4 + a1b3 + a2b2 + a3b1 + a4b0


    Note: If linear convolution is required, pad with zeros appropriately, as in multiplication

***/

/// Returns the convolution of A and B in A

void convolution(int n, int* A, int* B){
    for (int i = 0; i < n; i++) P1[i] = complx(A[i], 0);
    for (int i = 0; i < n; i++) P2[i] = complx(B[i], 0);
    convolution(n, P1, P2);
    for (int i = 0; i < n; i++) A[i] = round_half_even(P1[i].real());
}

/// Multiplies two polynomials A and B and return the coefficients of their product in A
/// Function returns degree of the polynomial A * B

int multiply(int a, int* A, int b, int* B){
    for (int i = 0; i < a; i++) P1[i] = complx(A[i], 0);
    for (int i = 0; i < b; i++) P2[i] = complx(B[i], 0);
    int degree = multiply(a, P1, b, P2);
    for (int i = 0; i < degree; i++) A[i] = round_half_even(P1[i].real());
    return degree;
}

int main(){
}
