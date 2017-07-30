#include<bits/stdc++.h>

#define cpp_io() {ios_base::sync_with_stdio(false);cin.tie(NULL);}
#define FOR(i, N) FORR(i, 0, N)
#define FORR(i, a, b) FOTR(i, a, b, 1)
#define FOTR(i, a, b, c) for(int i=(a);i<(b);i+=(c))

using namespace std;

string preprocess(string s) {
    int len = s.length();
    string t = "^";
    FOR(i, len) { t += "#", t += s[i]; }
    return t + "#$";
}

vector<int> LPS_Array(string str) {
    string T = preprocess(str);
    int n = T.length(), C = 0, R = 0, LN;
    vector<int> lps(n);
    FORR(i, 1, n) {
        LN = (R > i) ? min(R - i, lps[2 * C - i]) : 0;
        while (T[i + 1 + LN] == T[i - 1 - LN])LN++;
        if (i + LN > R) { C = i, R = i + LN; }
        lps[i] = LN;
    }
    return lps;
    /*  Print Palindromic Substrings:
    *   FOR(i, lps.size())
    *       if(lps[i]>0)
    *           cout<<s.substr((i-lps[i]-1)>>1, lps[i])<<"\n";
    */
}

int main() {
    cpp_io();
    int n;
    string s;
    cin >> n;
    while (n--) {
        cin >> s;
        vector<int> lps = LPS_Array(s);

        int mx = 0, c = 0;
        for (auto v: lps) if (v > mx)mx = v;
        for (auto v: lps) if (v == mx)c++;

        cout << mx << " " << c << "\n";
    }
}

// SOLVED
/* SPOJ MSUBSTR */
// _SOLVED