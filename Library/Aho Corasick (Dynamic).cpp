#include <bits/stdtr1c++.h>

#define LOG 19
#define LET 26
#define MAX 300010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl

using namespace std;

struct aho_corasick{
    long long counter[MAX];
    vector <int> dp[LET];
    vector <string> dictionary;
    vector <vector<int> > trie;
    int id, len, Q[MAX], fail[MAX], edge[256];

    inline int node(){
		trie.push_back(vector<int>(LET, 0));
		fail[id] = 0, counter[id] = 0;
		return id++;
    }

    inline int size(){
        return dictionary.size();
    }

    void clear(){
        trie.clear();
        dictionary.clear();
        id = 0, len = 0, node();
        for (int i = 0; i < LET; i++) dp[i].clear();
        for (int i = 'a'; i <= 'z'; i++) edge[i] = i - 'a'; /// change here if different character set
    }

    aho_corasick(){
        clear();
    }

    inline void insert(const char* str){
        int j, x, cur = 0;
        for (j = 0; str[j] != 0; j++){
            x = edge[str[j]];
            if (!trie[cur][x]) trie[cur][x] = node();
            cur = trie[cur][x];
        }

        counter[cur] = 1;
        dictionary.push_back(str);
    }

    inline void build(){ /// remember to call build
        for (int i = 0; i < LET; i++) dp[i].resize(id, 0);
        for (int i = 0; i < id; i++){
            for (int j = 0; j < LET; j++){
                dp[j][i] = i;
            }
        }

        int i, j, x, f = 0, l = 0;
        for (i = 0; i < LET; i++){
            if (trie[0][i]) Q[l++] = trie[0][i];
        }

        while (f < l){
            i = Q[f++];
            for (j = 0; j < LET; j++){
                int &v = trie[i][j];
                if (v == 0) v = trie[fail[i]][j];
                else{
                    Q[l++] = v;
                    fail[v] = trie[fail[i]][j], counter[v] += counter[fail[v]];
                }
                if (i && !trie[i][j]) dp[j][i] = dp[j][fail[i]];
            }
        }
    }

    inline int next(int cur, char ch){
        int x = edge[ch];
        cur = dp[x][cur];
        if (trie[cur][x]) cur = trie[cur][x];
        return cur;
    }

    long long count(const char* str){ /// total number of occurrences of all words from dictionary in str
        int cur = 0;
        long long res = 0;

        for (int j = 0; str[j] && id > 1; j++){
            cur = next(cur, str[j]);
            res += counter[cur];
        }
        return res;
    }
};

struct dynamic_aho{ /// dynamic aho corasick in N log N
    aho_corasick ar[LOG];

    dynamic_aho(){
        for (int i = 0; i < LOG; i++) ar[i].clear();
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

    long long count(const char* str){
        long long res = 0;
        for (int i = 0; i < LOG; i++) res += ar[i].count(str);
        return res;
    }
};

char str[MAX];

int main(){
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
