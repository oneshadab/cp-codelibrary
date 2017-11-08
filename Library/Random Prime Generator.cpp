#include <bits/stdtr1c++.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl

using namespace std;

bool isPrime(uint64_t p){
    for (uint64_t i = 2; (i * i) <= p; i++){
        if ((p % i) == 0) return false;
    }
    return true;
}

uint64_t RandomPrime(uint64_t a, uint64_t b){
    mt19937_64 generator(time(0));
    uniform_int_distribution<unsigned long long> random(a, b);

    uint64_t p = random(generator);
    while (!isPrime(p)) p++;
    return p;
}

int main(){
    uint64_t res = RandomPrime(1e9 + 9e8 , 2e9);
    dbg(res);
    return 0;
}
