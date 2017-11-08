#include <bits/stdtr1c++.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("avx,tune=native")

#define gen() freopen("lol.txt", "w", stdout)
#define write() freopen("output.txt", "w", stdout)
#define test1() freopen("test1.txt", "w", stdout)
#define test2() freopen("test2.txt", "w", stdout)

#define setbit(x, i) ((x) | (1 << (i)))
#define pow2(x) ((x) && !((x) & ((x) - 1)))
#define resetbit(x, i) ((x) & (~(1 << (i))))
#define getbit(x, i) (((x) & (1 << (i))) ? (1):(0))

#define printbits(x, n) cout << #x << " = " << x << " = " << bitset<n>(x) << endl /// Least significant n bits of x, n must be constant
#define tobinary(x) string(bitset<64>(x).to_string<char, string::traits_type, string::allocator_type>()).substr(min(63, __builtin_clzll(x)), 64)
#define lastbits(x, n) cout << string(bitset<64>(x).to_string<char, string::traits_type, string::allocator_type>()).substr(64 - n, 64) << endl
#define firstbits(x, n) cout << string(bitset<64>(x).to_string<char, string::traits_type, string::allocator_type>()).substr(min(63, __builtin_clzll(x)), 64).substr(0, n) << endl;

using namespace std;

inline void init_random(){
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    srand(seed);
}

int main(){
    cout <<  fixed << setprecision(25) << res << endl;
}
