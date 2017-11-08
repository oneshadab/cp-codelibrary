#include <bits/stdc++.h>

using namespace std;

#define MAX 1010101
#define STT 300000
#define CLR(a, x) (memset(a, x, sizeof(a)))
char mStr[MAX + 7];
char tempStr[MAX + 7];
int jump[STT][30];
int fail[STT];
int visited[STT];
int term[STT];
vector<int> rev[STT];

struct AhoCorasick{
    static const int MAXN = 300000;
    int jump[MAXN][300], fail[MAXN], visited[MAXN];
    vector<int> rev[STT], term;
    int lst;

    void add(string str){ //Returns the final state of a string
        int j = 0;
        for(int i = 0; str[i]; i++) {
            char ch = str[i];
            if(jump[j][ch] == -1) jump[j][ch] = ++lst;
            j = jump[j][ch];
        }
        term.push_back(j);
    }

    void build(){
        queue<int> que;
        fail[0] = -1;
        que.push(0);
        while(!que.empty()) {
            int v = que.front();
            que.pop();
            for(int i = 0; i <= 26; i++) {
                if(jump[v][i] != -1) {
                    int u = jump[v][i];
                    int j = fail[v];
                    while(j != -1 && jump[j][i] == -1) j = fail[j];
                    if(j != -1) {
                        fail[u] = jump[j][i];
                        rev[jump[j][i]].push_back(u);
                    }
                    que.push(u);
                }
            }
        }
    }

    void process(string s){
        memset(visited, 0, sizeof(visited));
        int j = 0;
        for(auto ch: s){
            while(j != -1 && jump[j][ch] == -1) {
                j = fail[j];
            }
            if(j != -1 && jump[j][ch] != -1)
                j = jump[j][ch];
            if(j == -1) j = 0;
            visited[j] += 1;;
        }
    }

    int countMatched(int i){ // Number of times the i'th string was matched
        return dfs(term[i]);
    }

    int dfs(int u){
        if(u == 0) return 0;
        int cnt = visited[u];
        for(auto v: rev[u]) cnt+=dfs(v);
        return cnt;
    }

    void clear(){
        lst=0;
        memset(jump, -1, sizeof(jump));
        memset(fail,  0, sizeof(fail));
        for(int i=0;i<MAXN; i++) rev[i].clear();
    }

}aho;


int main()
{
    //freopen("input.txt", "r", stdin);
    int t;
    cin >> t;
    for(int cs = 1; cs <= t; cs++) {
        CLR(term, -1);
        aho.clear();
        int n;
        scanf("%d", &n);
        scanf("%s", mStr);
        for(int i = 0; i < n; i++) {
            scanf("%s", tempStr);
            aho.add(tempStr);
        }
        aho.build();
        aho.process(mStr);
        printf("Case %d:\n", cs);
        for(int i = 0; i < n; i++) {
            int cnt = aho.countMatched(i);
            printf("%d\n", cnt);
        }

    }
}
