#include <bits/stdtr1c++.h>

#define MAX 262148 /// 2 * Smallest power of 2 greater than MAXN, 2^18 when MAXN = 10^5
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

/// Replace long double with double if not required

namespace fft{
    struct complx{
        long double real, img;

        inline complx(){
            real = img = 0.0;
        }

        inline complx(long double x){
            real = x, img = 0.0;
        }

        inline complx(long double x, long double y){
            real = x, img = y;
        }

        inline void operator += (complx &other){
            real += other.real, img += other.img;
        }

        inline void operator -= (complx &other){
            real -= other.real, img -= other.img;
        }

        inline complx operator + (complx &other){
            return complx(real + other.real, img + other.img);
        }

        inline complx operator - (complx &other){
            return complx(real - other.real, img - other.img);
        }

        inline complx operator * (complx& other){
            return complx((real * other.real) - (img * other.img), (real * other.img) + (img * other.real));
        }
    } P[MAX >> 1], P1[MAX], P2[MAX];

    int rev[MAX];
    long long ar[6][MAX];

    inline long long round_half_even(long double x){
        long long res = abs(x) + 0.5;
        if (x < 0) res = -res;
        return res;
    }

    void transform(complx *ar, int n, int inv){ /// hash = 131109
        int i, j, k, l, len, len2;
        const long double p = 4.0 * inv * acos(0.0);

        for (i = 0, l = __builtin_ctz(n) - 1; i < n; i++){
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << l);
            if(i < rev[i]) swap(ar[i], ar[rev[i]]);
        }

        for (len = 2; len <= n; len <<= 1){
            len2 = len >> 1;
            long double theta = p / len;
            complx mul(cos(theta), sin(theta));
            for (i = 1, P[0] = complx(1, 0); i < len2; i++) P[i] = (P[i - 1] * mul);

            for (i = 0; i < n; i += len){
                complx t, *x = ar + i, *y = ar + i + len2, *l = ar + i + len2, *z = P;
                for (; x != l; x++, y++, z++){
                    t = (*y) * (*z), *y = *x - t;
                    *x += t;
                }
            }
        }

        if (inv == -1){
            long double tmp = 1.0 / n;
            for (i = 0; i < n; i++) ar[i].real *= tmp;
        }
    }

    void fft_convolution(int n, complx* A, complx* B){ /// hash = 121635
        int i, m, d = 0;
        if (__builtin_popcount(n) != 1){
            for (i = 0; i < n; i++) B[i + n] = B[i], A[i + n] = complx(0);
            d = n, n *= 2;
        }

        m = 1 << (32 - __builtin_clz(n) - (__builtin_popcount(n) == 1));
        for (i = n; i < m; i++) A[i] = B[i] = complx(0);

        transform(A, m, 1), transform(B, m, 1);
        for (i = 0; i < m; i++) A[i] = A[i] * B[i];
        transform(A, m, -1);
        for (i = 0; i < d && d; i++) A[i] = A[i + d];
    }

    int fft_multiply(int a, complx* A, int b, complx* B){
        int n = a + b - 1;
        int m = 1 << (32 - __builtin_clz(n) - (__builtin_popcount(n) == 1));
        for (int i = a; i < m; i++) A[i] = complx(0);
        for (int i = b; i < m; i++) B[i] = complx(0);
        transform(A, m, 1), transform(B, m, 1);
        for (int i = 0; i < m; i++) A[i] = A[i] * B[i];
        transform(A, m, -1);
        return m;
    }

    /// Multiplies two polynomials A and B and return the coefficients of their product in A
    /// Function returns degree of the polynomial A * B

    template <typename dataType>
    int multiply(int a, dataType* A, int b, dataType* B){
        for (int i = 0; i < a; i++) P1[i] = complx(A[i], 0.0);
        for (int i = 0; i < b; i++) P2[i] = complx(B[i], 0.0);
        int len = fft_multiply(a, P1, b, P2);
        for (int i = 0; i < len; i++) A[i] = round_half_even(P1[i].real);
        return len;
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
    template <typename dataType>
    void convolution(int n, dataType* A, dataType* B){
        for (int i = 0; i < n; i++) P1[i] = complx(A[i], 0.0), P2[i] = complx(B[i], 0.0);
        fft_convolution(n, P1, P2);
        for (int i = 0; i < n; i++) A[i] = round_half_even(P1[i].real);
    }

    /// Extended functions

    /// Returns the convolution of A and B modulo mod in A
    void convolution(int n, int* A, int* B, int mod){ /// hash = 174371
        int i, s = sqrt(0.9 + mod);

        for (i = 0; i < n; i++){
            ar[0][i] = ar[5][i] = A[i] % s;
            ar[1][i] = ar[4][i] = A[i] / s;
        }
        for (i = 0; i < n; i++) ar[2][i] = B[i] % s, ar[3][i] = B[i] / s;

        convolution(n, ar[5], ar[2]), convolution(n, ar[0], ar[3]);
        convolution(n, ar[4], ar[2]), convolution(n, ar[1], ar[3]);

        for (i = 0; i < n; i++){
            A[i] = ( ((ar[0][i] + ar[4][i]) * s) + ar[5][i] + (ar[1][i] * s % mod * s)) % mod;
        }
    }

    /// Multiplies two polynomials A and B and return the coefficients of their product in A modulo m
    /// Function returns degree of the polynomial A * B

    int multiply(int a, int* A, int b, int* B, int mod){ /// hash = 848260
        int i, s = sqrt(0.9 + mod);

        for (i = 0; i < a; i++){
            ar[0][i] = ar[5][i] = A[i] % s;
            ar[1][i] = ar[4][i] = A[i] / s;
        }
        for (i = 0; i < b; i++) ar[2][i] = B[i] % s, ar[3][i] = B[i] / s;

        multiply(a, ar[5], b, ar[2]), multiply(a, ar[0], b, ar[3]);
        multiply(a, ar[4], b, ar[2]), multiply(a, ar[1], b, ar[3]);

        for (i = 0; i < (a + b - 1); i++){
            A[i] = ( ((ar[0][i] + ar[4][i]) * s) + ar[5][i] + (ar[1][i] * s % mod * s)) % mod;
        }
        return (a + b - 1);
    }

    /// Multiplies two polynomials A and B and return the coefficients of their product in A modulo m
    /// Function returns degree of the polynomial A * B

    int fastmul(int a, int* A, int b, int* B, int mod){
        complx ar[4][MAX]; /// make global if RTE
        int i, m, n = a + b - 1, s = sqrt(0.9 + mod);

        m = 1 << (32 - __builtin_clz(n) - (__builtin_popcount(n) == 1));
        for (i = 0; i < a; i++) ar[0][i] = complx(A[i] % s, 0), ar[1][i] = complx(A[i] / s, 0);
        for (i = 0; i < b; i++) ar[2][i] = complx(B[i] % s, 0), ar[3][i] = complx(B[i] / s, 0);
        for (i = a; i < m; i++) ar[0][i] = ar[1][i] = complx(0);
        for (i = b; i < m; i++) ar[2][i] = ar[3][i] = complx(0);

        for (i = 0; i < 4; i++) transform(ar[i], m, 1);
        for (i = 0; i < m; i++){
            P1[i] = ar[0][i] * ar[2][i], P2[i] = ar[1][i] * ar[2][i];
            ar[0][i] = ar[0][i] * ar[3][i], ar[1][i] = ar[1][i] * ar[3][i];
        }
        transform(ar[0], m, -1), transform(ar[1], m, -1), transform(P2, m, -1), transform(P1, m, -1);

        for (i = 0; i < (a + b - 1); i++){
            long long x = floor(ar[0][i].real + 0.5), y = floor(P2[i].real + 0.5);
            long long z = floor(P1[i].real + 0.5), w = floor(ar[1][i].real + 0.5);
            A[i] = ( ((x + y) * s) + z + (w * s % mod * s)) % mod;
        }
        return (a + b - 1);
    }
}

int main(){

}
