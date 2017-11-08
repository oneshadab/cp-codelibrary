#include <bits/stdtr1c++.h>

#define MAXN 666            /// Size of matrix
#define MOD 1000000007      /// MOD must be prime and greater than 2
#define MOD_THRESHOLD 18    /// MOD * MOD * MOD_THRESHOLD < 2^64

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

namespace bbl{ /// IMPORTANT: MOD must be prime and greater than 2
    struct Matrix{ /// hash = 839399 (for Matrix class)
        int n, ar[MAXN][MAXN];

        Matrix(){}
        Matrix(int dimension, int diagonal = 0){
            clr(ar);
            n = dimension;
            for (int i = 0; i < n; i++) ar[i][i] = diagonal;
        }

        Matrix operator* (const Matrix& other) const{
            Matrix res(n);
            int i, j, k, l, d;

            for(i = 0; i < n; i++){
                for(j = 0; j < other.n; j++){
                    unsigned long long x = 0;
                    for(k = 0; k < n; k += MOD_THRESHOLD){
                        for (l = 0; l < MOD_THRESHOLD && (k + l) < n; l++){
                            x += ((unsigned long long)ar[i][k + l] * other.ar[k + l][j]);
                        }
                        x %= MOD;
                    }
                    res.ar[i][j] = x;
                }
            }
            return res;
        }

        Matrix operator^ (long long n) const{
            Matrix x = *this, res = Matrix(this->n, 1);
            while (n){
                if (n & 1) res = res * x;
                n = n >> 1;
                x = x * x;
            }
            return res;
        }
    };

    int mod_inverse(int x){
        int u = 1, v = 0, t = 0, a = x, b = MOD;
        while (b){
            t = a / b;
            a -= (t * b), u -= (t * v);
            swap(a, b), swap(u, v);
        }
        return (u + MOD) % MOD;
    }

    int convolution(const int* A, const int* B, int n){
        int i = 0, j = 0;
        unsigned long long res = 0;
        for (i = 0; (i + MOD_THRESHOLD) <= n; res %= MOD){
            for (j = 0; j < MOD_THRESHOLD; j++, i++) res += (unsigned long long)A[i] * B[i];
        }

        for (j = 0; i < n; i++) res += (unsigned long long)A[i] * B[i];
        return res % MOD;
    }

    /// Berlekamp Massey algorithm in O(n ^ 2)
    /// Finds the shortest linear recurrence that will generate the sequence S and returns it in C
    /// S[i] * C[l - 1] + S[i + 1] * C[l - 2] + ... + S[j] * C[0] = 0

    int berlekamp_massey(vector <int> S, vector <int>& C){ /// hash = 347704
        assert(S.size() && (S.size() % 2) == 0);

        int n = S.size();
        C.assign(n + 1, 0);
        vector <int> T, B(n + 1, 0);
        reverse(S.begin(), S.end());

        C[0] = 1, B[0] = 1;
        int i, j, k, d, x, l = 0, m = 1, b = 1, deg = 0;

        for (i = 0; i < n; i++){
            d = S[n - i - 1];
            if (l > 0) d = (d + convolution(&C[1], &S[n - i], l)) % MOD;
            if (d == 0) m++;
            else{
                if (l * 2 <= i) T.assign(C.begin(), C.begin() + l + 1);
                x = (((long long)mod_inverse(b) * (MOD - d)) % MOD + MOD) % MOD;

                for (j = 0; j <= deg; j++){
                    C[m + j] = (C[m + j] + (unsigned long long)x * B[j]) % MOD;
                }
                if (l * 2 <= i){
                    B.swap(T);
                    deg = B.size() - 1;
                    b = d, m = 1, l = i - l + 1;
                }
                else m++;
            }
        }

        C.resize(l + 1);
        return l;
    }

    /// find's the n'th term of the recurrence from a continuous sequence of recurrence values
    /// recurrence and n both follow 0 based indexing
    long long interpolate(vector <int>& recurrence, long long n){ /// hash = 377697
        int len = recurrence.size();
        if (n < len) return recurrence[n];

        vector <int> polynomial;
        int l = berlekamp_massey(recurrence, polynomial);
        while (l && polynomial[l] == 0){
            l--;
            polynomial.pop_back();
        }
        reverse(polynomial.begin(), polynomial.begin() + l + 1);

        struct Matrix mat = Matrix(l);
        for (int i = 1; i < mat.n; i++) mat.ar[i][i - 1] = 1;
        for (int i = 0; i < mat.n; i++) mat.ar[0][i] = MOD - polynomial[l - i - 1];

        long long res = 0;
        mat = mat ^ (n - len + 1);
        for (int i = 0; i < mat.n; i++) res = (res + (long long)mat.ar[0][i] * recurrence[len - i - 1]) % MOD;
        return res;
    }
}

int main(){
    vector <int> recurrence = {0, 0, 1, 1, 2, 3}; /// fibonacci sequence
    printf("%lld\n", bbl::interpolate(recurrence, 1234567)); /// output = 481148194
    return 0;
}
