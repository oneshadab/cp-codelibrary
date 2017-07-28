#include <bits/stdc++.h>

using namespace std;

#define FOR(i, N) FORR(i, 0, N)
#define FORR(i, a, b) FOTR(i, a, b, 1)
#define FOTR(i, a, b, c) for(int i=(a);i<(b);i+=(c))

#define MEM(a, x) memset(a,x,sizeof(a))
#define pb push_back
#define mk make_pair
#define pii pair<int, int>
#define MAX 100010   //Keep MAX as small as possible
#define MAXLG 17   //ceil(log2(MAX))

struct SA {
    pair<pii, int> L[MAX];
    int P[MAXLG + 1][MAX], n, stp, cnt, sa[MAX];
    string s;
    list<pair<pii, int>> buckets[MAX];

    int get_digit(pii &x, int d) { return d? x.second : x.first; }

    void radix(int d) {
        FOR(i, n + 1)buckets[i].clear();
        FOR(i, n)buckets[get_digit(L[i].first, d) + 1].pb(L[i]);
        int j = 0;
        FOR(i, n + 1) {
            for (auto it = buckets[i].begin(); it != buckets[i].end(); it++)
                L[j++] = *it;
        }
    }

    void build(string &st) {
        if (s.size() > 0)reset();
        s = st;
        n = s.size();
        int _rank[260] = {0};
        FOR(i, n) _rank[s[i]] = 1;
        FORR(i, 1, 260)_rank[i] += _rank[i - 1];
        FOR(i, n)P[0][i] = _rank[s[i]] - 1;
        sa[0] = 0;
        for (stp = 1, cnt = 1; cnt < n; stp++, cnt <<= 1) {
            FOR(i, n)L[i] = mk(mk(P[stp - 1][i], i + cnt < n ? P[stp - 1][i + cnt] : -1), i);
            radix(1);
            radix(0);
            FOR(i, n)
                P[stp][L[i].second] = i > 0 && L[i].first == L[i - 1].first?
                                      P[stp][L[i - 1].second] : i;
        }
        FOR(i, n)sa[i] = L[i].second;
    }

    int lcp(int x, int y) { //x,y is starting positions of prefix in the string
        int k, ret = 0;
        if (x == y)return n - x;
        for (k = stp - 1; k >= 0 && x < n && y < n; k--) {
            if (P[k][x] == P[k][y])
                x += 1 << k, y += 1 << k, ret += 1 << k;
        }
        return ret;
    }

    int numDistinctSubstring() {
        int ret = n - sa[0];
        FORR(i, 1, n) {
            ret += (n - sa[i]) - lcp(sa[i - 1], sa[i]);
        }
        return ret;
    }

    vector<string> distinctSubstirings() {
        int j = 0;
        vector<string> v;
        v.pb(s.substr(sa[0], n - sa[0]));
        FORR(i, 1, n) {
            int l = lcp(sa[i - 1], sa[i]);
            for (int k = 0; k < n - sa[i] - l; k++) {
                v.pb(s.substr(sa[i], l + k + 1));
            }
        }
        return v;
    }

    void reset() {
        FOR(i, n + 2)buckets[i].clear();
        MEM(P, 0);
        MEM(L, 0);
    }
} a;

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
/* SARRAY - Suffix Array (70)
 * DISUBSTR - Distinct Substrings */
// _SOLVED