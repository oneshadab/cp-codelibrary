#include <stdio.h>
#include <bits/stdtr1c++.h>

#define LOG 19
#define LET 26
#define MAX 300300 /// At least MAX + 300
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl

using namespace std;

set <int> pool;
long long counter[MAX];
int Q[MAX], edge[256], leaf[MAX], fail[MAX], dp[MAX][LET], trie[MAX][LET];

struct aho_corasick{
    int root;
    vector <int> nodes;
    vector <string> dictionary;

    inline int node(){
        int id = *(pool.begin());
        pool.erase(pool.begin());

		for (int i = 0; i < LET; i++) trie[id][i] = root;
		nodes.push_back(id);
		fail[id] = root, leaf[id] = 0, counter[id] = 0;
		return id;
    }

    inline int size(){
        return dictionary.size();
    }

    void clear(){
        for (auto i: nodes) pool.insert(i);

        nodes.clear();
        dictionary.clear();
        root = *(pool.begin());
        node();
        for (int i = 0; i < LET; i++) dp[root][i] = root;
        for (int i = 'a'; i <= 'z'; i++) edge[i] = i - 'a'; /// change here if different character set
    }

    aho_corasick(){
        clear();
    }

    inline int next(int cur, char ch){
        int x = edge[ch];
        cur = dp[cur][x];
        if (trie[cur][x] != root) cur = trie[cur][x];
        return cur;
    }

    inline void insert(const char* str){
        int j, x, cur = root;
        for (j = 0; str[j] != 0; j++){
            x = edge[str[j]];
            if (trie[cur][x] == root) trie[cur][x] = node();
            cur = trie[cur][x];
        }

        leaf[cur]++;
        dictionary.push_back(str);
    }


    inline void build(){ /// remember to call build
        vector <pair<int, pair<int, char> > > Q;
        Q.push_back({root, {root, 0}});

        for(int i = 0; i < Q.size(); i++){
            int u = Q[i].first;
            int p = Q[i].second.first;
            char c = Q[i].second.second;
            for (int j = 0; j < LET; j++){
                if (trie[u][j] != root) Q.push_back({trie[u][j], {u, j}});
            }

            if (u != root){
                int f = fail[p];
                while (f != root && trie[f][c] == root) f = fail[f];
                if(trie[f][c] != root && trie[f][c] != u) fail[u] = trie[f][c];
                counter[u] = leaf[u] + counter[fail[u]];

                for (int j = 0; j < LET; j++){
                    dp[u][j] = u;
                    if (u && trie[u][j] == root) dp[u][j] = dp[fail[u]][j];
                }
            }
        }
    }

    inline long long count(const char* str){ /// total number of occurrences of all words from dictionary in str
        int cur = root;
        long long res = 0;

        for (int j = 0; str[j]; j++){
            cur = next(cur, str[j]);
            res += counter[cur];
        }
        return res;
    }
};

struct dynamic_aho{ /// dynamic aho corasick in N log N
    aho_corasick ar[LOG];

    dynamic_aho(){
        for (int i = 0; i < LOG; i++) ar[i] = aho_corasick();
    }

    inline void insert(const char* str){
        int i, k = 0;
        for (k = 0; k < LOG && ar[k].size(); k++){}

        ar[k].insert(str);
        for (i = 0; i < k; i++){
            for (auto s: ar[i].dictionary){
                ar[k].insert(s.c_str());
            }
            ar[i].clear();
        }
        ar[k].build();
    }

    inline long long count(const char* str){
        long long res = 0;
        for (int i = 0; i < LOG; i++) res += ar[i].count(str);
        return res;
    }

    inline void clear(){
        for (int i = 0; i < LOG; i++) ar[i].clear();
    }
};

char str[MAX];

int main(){
    for (int i = 1; i < MAX; i++) pool.insert(pool.end(), i); /// must do this before anything

    dynamic_aho ar[2];
    int t, i, j, k, l, flag;

    scanf("%d", &t);
    while (t--){
        scanf("%d %s", &flag, str);
        if (flag == 3){
            printf("%lld\n", ar[0].count(str) - ar[1].count(str));
            fflush(stdout);
        }
        else ar[flag - 1].insert(str);
    }
    return 0;
}

