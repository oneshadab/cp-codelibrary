#include <bits/stdtr1c++.h>

#define MAX 131072 /// Must be a power of 2
#define MOD 1000000007

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

int ptr = 0, buffer[MAX * 6];
unsigned long long temp[128];
const unsigned long long INF = 16111345678373523861LL;

void karatsuba(int n, int *a, int *b, int *res){ /// n is a power of 2
    int i, j, h;
    /// MOD * MOD * n must fit in unsigned long long!

    if (n == 16){ /// Loop unrolling, to reduce recursive calls
        for (i = 0; i < (n + n); i++) temp[i] = 0;
        for (i = 0; i < n; i++){
            temp[i + 0] += ((long long)a[i] * b[0]), temp[i + 1] += ((long long)a[i] * b[1]), temp[i + 2] += ((long long)a[i] * b[2]), temp[i + 3] += ((long long)a[i] * b[3]);
            temp[i + 4] += ((long long)a[i] * b[4]), temp[i + 5] += ((long long)a[i] * b[5]), temp[i + 6] += ((long long)a[i] * b[6]), temp[i + 7] += ((long long)a[i] * b[7]);
            temp[i + 8] += ((long long)a[i] * b[8]), temp[i + 9] += ((long long)a[i] * b[9]), temp[i + 10] += ((long long)a[i] * b[10]), temp[i + 11] += ((long long)a[i] * b[11]);
            temp[i + 12] += ((long long)a[i] * b[12]), temp[i + 13] += ((long long)a[i] * b[13]), temp[i + 14] += ((long long)a[i] * b[14]), temp[i + 15] += ((long long)a[i] * b[15]);
        }
		for (i = 0; i < (n + n); i++) res[i] = temp[i] % MOD;
		return;
	}

	if (n < 17){ /// Reduce recursive calls by setting a threshold
        for (i = 0; i < (n + n); i++) temp[i] = 0;
        for (i = 0; i < n; i++){
            for (j = 0; j < n; j++){
                temp[i + j] += ((long long)a[i] * b[j]);
            }
        }
		for (i = 0; i < (n + n); i++) res[i] = temp[i] % MOD;
		return;
	}

	h = n >> 1;
	karatsuba(h, a, b, res);
	karatsuba(h, a + h, b + h, res + n);
	int *x = buffer + ptr, *y = buffer + ptr + h, *z = buffer + ptr + h + h;

	ptr += (h + h + n);
	for (i = 0; i < h; i++){ /// Loop unrolling
        x[i] = a[i] + a[i + h], y[i] = b[i] + b[i + h];
        if (x[i] >= MOD) x[i] -= MOD;
        if (y[i] >= MOD) y[i] -= MOD;

        i++;
        x[i] = a[i] + a[i + h], y[i] = b[i] + b[i + h];
        if (x[i] >= MOD) x[i] -= MOD;
        if (y[i] >= MOD) y[i] -= MOD;
	}

	karatsuba(h, x, y, z);
	for (i = 0; i < n; i += 2){ /// Loop unrolling
        z[i] -= (res[i] + res[i + n]);
        z[i + 1] -= (res[i + 1] + res[i + n + 1]);
	}

	for (i = 0; i < n; i++){ /// Loop unrolling
        res[i + h] = (res[i + h] + z[i]) % MOD;
        if (res[i + h] < 0) res[i + h] += MOD;
        i++;
        res[i + h] = (res[i + h] + z[i]) % MOD;
        if (res[i + h] < 0) res[i + h] += MOD;
	}
	ptr -= (h + h + n);
}

/// multiplies two polynomial a(degree n) and b(degree m) and returns the result modulo MOD in a
/// returns the degree of the multiplied polynomial
/// note that a and b are changed in the process
int mul(int n, int *a, int m, int *b){
    int i, r, c = (n < m ? n : m), d = (n > m ? n : m), *res = buffer + ptr;
    r = 1 << (32 - __builtin_clz(d) - (__builtin_popcount(d) == 1));
    for (i = d; i < r; i++) a[i] = b[i] = 0;
    for (i = c; i < d && n < m; i++) a[i] = 0;
    for (i = c; i < d && m < n; i++) b[i] = 0;

    ptr += (r << 1), karatsuba(r, a, b, res), ptr -= (r << 1);
    for (i = 0; i < (r << 1); i++) a[i] = res[i];
    return (n + m - 1);
}

int a[MAX], b[MAX];

int main(){
    int i, j, k, n = MAX - 10;
    for (i = 0; i < n; i++) a[i] = ran(1, 1000000000);
    for (i = 0; i < n; i++) b[i] = ran(1, 991929183);
    clock_t start = clock();
    mul(n, a, n, b);
    dbg(a[n / 2]);
    for (i = 0; i < (n << 1); i++){
        if (a[i] < 0) puts("YO");
    }
    printf("%0.5f\n", (clock() - start) / (1.0 * CLOCKS_PER_SEC));
    return 0;
}
