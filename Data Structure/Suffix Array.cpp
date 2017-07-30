#include <bits/stdc++.h>

using namespace std;

#define FOR(i,N) FORR(i, 0, N)
#define FORR(i,a,b) FOTR(i, a, b, 1)
#define FOTR(i,a,b,c) for(int i=(a);i<(b);i+=(c))

#define MEM(a,x) memset(a,x,sizeof(a))
#define pb push_back
#define pii pair<int, int>
#define MAX 100010   //Keep MAX as small as possible
#define MAXLG 17   //ceil(log2(MAX))

struct SA {
    pair<pii, int> L[MAX];
    int P[MAXLG + 1][MAX], n, stp, cnt, sa[MAX];
    string s;
    void build(const string &st){
        if(s.size()>0)MEM(L,0);
        s = st;
        n = s.size();
        FOR(i, n)P[0][i] = s[i] - 1;
        sa[0] = 0;
        for (stp = 1, cnt = 1; cnt<n; stp++, cnt <<= 1) {
            FOR(i, n)L[i] = {{P[stp-1][i], i+cnt<n? P[stp-1][i+cnt] : -1}, i};
            sort(L, L+n);
            FOR(i, n)
                P[stp][L[i].second] = i>0 &&
                    L[i].first==L[i-1].first? P[stp][L[i - 1].second] : i;
        }
        FOR(i, n)sa[i] = L[i].second;
    }

    int lcp(int x, int y) { //x,y is starting positions of prefix in the string
        int k, ret = 0;
        if (x == y)return n - x;
        for (k = stp-1; k >= 0 && x<n && y<n; k--) {
            if (P[k][x] == P[k][y])
                x+= 1<<k, y+= 1<<k, ret+= 1<<k;
        }
        return ret;
    }

    int numDistinctSubstring(){
        int ret = n-sa[0];
        FORR(i, 1, n){
            ret += (n-sa[i])-lcp(sa[i-1], sa[i]);
        }
        return ret;
    }

    vector<string> distinctSubstirings(){
        int j = 0;
        vector<string> v;
        v.pb(s.substr(sa[0], n-sa[0]));
        FORR(i, 1, n){
            int l = lcp(sa[i-1], sa[i]);
            for(int k=0; k<n-sa[i]-l; k++){
                v.pb(s.substr(sa[i], l+k+1));
            }
        }
        return v;
    }
}a;

int main() {
    string s = "abcabc";
    a.build(s);

    FOR(i, 6)cout << a.sa[i] << " ";      //3 0 4 1 5 2
    cout << "\n\n";

    cout << a.lcp(a.sa[0], a.sa[2]) << "\n";  // 0
    cout << a.lcp(a.sa[0], a.sa[1]) << "\n";  // 3
    cout << a.lcp(a.sa[0], a.sa[0]) << "\n\n";  // 3

    s = "banana";
    a.build(s);
    cout << a.numDistinctSubstring() << "\n";  //15
}

// SOLVED
/* SPOJ SARRAY - Suffix Array (80)
 * SPOJ DISUBSTR - Distinct Substrings */
// _SOLVED