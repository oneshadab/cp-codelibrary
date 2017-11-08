#include <bits/stdtr1c++.h>

#define MAX 10000010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl

using namespace std;

namespace dv{
    long long P[100];
    bitset <MAX> isprime;
    int p = 0, C[100], primes[666666];

    void Sieve(){
        int i, j, k;
        for (i = 3; (i * i) < MAX; i += 2){
            if (!isprime[i]){
                for (j = (i * i), k = i << 1; j < MAX; j += k){
                    isprime[j] = true;
                }
            }
        }

        primes[p++] = 2;
        for (i = 3; i < MAX; i += 2){
            if (!isprime[i]) primes[p++] = i;
        }
    }

    void backtrack(int i, long long d, vector <long long>& v){
        if (i < 0){
            v.push_back(d);
            return;
        }
        for (int j = 0; j <= C[i]; j++, d *= P[i]) backtrack(i - 1, d, v);
    }

    vector <long long> divisors(long long n){
        if (!p) Sieve();

        int i, k, x, len = 0;
        for (i = 0; i < p; i++){
            k = 0, x = primes[i];
            if (((long long)x * x) > n) break;

            while (!(n % x)){
                k++;
                n /= x;
            }
            if (k) P[len] = x, C[len++] = k;
        }
        if (n > 1) P[len] = n, C[len++] = 1;

        vector <long long> v;
        backtrack(len - 1, 1, v);
        sort(v.begin(), v.end());
        return v;
    }
}

int main(){

}
