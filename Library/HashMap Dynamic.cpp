#include <stdio.h>
#include <bits/stdtr1c++.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

const int nil = INT_MIN;

inline void init_random(){
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    srand(seed);
}

struct hashmap{
    int k, len, mod;
    vector <int> mp, val;

    inline bool isprime(int x){
        if (x <= 2) return (x == 2);
        if (x & 1){
            for (int i = 3; (i * i) <= x; i += 2){
                if (x % i == 0) return false;
            }
        }
        return (x & 1);
    }

    inline unsigned int smhash(unsigned int h){
        h ^= h >> 16;
        h *= 0x85ebca6b;
        h ^= h >> 13;
        h *= 0xc2b2ae35;
        h ^= h >> 16;
        return h;
    }

    hashmap(int load_factor = 2){
        len = 0, mod = 7, k = load_factor;
        mp.resize(mod, nil), val.resize(mod, 0);
    }

    inline void redistribute(){
        vector <pair<int, int>> ar;

        ar.reserve(len);
        for (int i = 0; i < mod; i++){
            if (mp[i] != nil) ar.push_back(make_pair(mp[i], val[i]));
        }

        len = 0, mod = (mod * k) + (rand() & 7);
        while (!isprime(mod)) mod++;
        mp = vector<int>(mod, nil), val = vector<int>(mod, 0);
        for (int i = 0; i < ar.size(); i++) add(ar[i].first, ar[i].second);
    }

    inline void add(int x, int v){
        int i = smhash(x) % mod;
        while (mp[i] != nil && mp[i] != x){
            i++;
            if (i == mod) i = 0;
        }

        len += (mp[i] == nil);
        mp[i] = x, val[i] += v;
        if ((len * k * 0.75) > mod) redistribute();
    }

    inline int get(int x){
        int i = smhash(x) % mod;
        while (mp[i] != nil && mp[i] != x){
            i++;
            if (i == mod) i = 0;
        }
        return (mp[i] == x) ? val[i] : 0;
    }
};

int main(){
    clock_t start = clock();
    init_random();
    hashmap h = hashmap(2);

    int q = 1e7;
    while (q--){
        int i = ran(1, 1000000000), v = ran(1, 1000);
        h.add(i, v);
    }

    fprintf(stderr, "%0.6f\n", (clock() - start) / (1.0 * CLOCKS_PER_SEC));
    return 0;
}
