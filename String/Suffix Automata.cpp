#include <bits/stdc++.h>

using namespace std;

struct SuffixAutomata {
    struct state {
        int len, link;
        map <char, int> next;
    };

    const int MAXLEN = 100000;
    vector <state> st;
    int sz;
    int last;

    ///For finding number of occurrences
    set < pair <int, int> > base;
    vector <int> cnt;
    bool isPreProcessed;
    ///For finding number of occurrences

    SuffixAutomata() {
        st = vector <state> (MAXLEN * 2);
        last = 0;
        st[0].len = 0;
        st[0].link = -1;
        sz = 1;

        ///For finding number of occurrences
        cnt = vector <int> (MAXLEN * 2);
        isPreProcessed = false;
        ///For finding number of occurrences
    }

    void BuildAutomata(string& s) {
        for (auto &x: s) Insert(x);
    }

    void Insert(char c) {
        int cur = sz++;
        st[cur].len = st[last].len + 1;

        ///For finding number of occurrences
        cnt[cur] = 1;
        base.insert(make_pair(st[cur].len, cur));
        ///For finding number of occurrences

        int p;
        for (p = last; p != -1 && !st[p].next.count(c); p = st[p].link)
            st[p].next[c] = cur;
        if (p == -1)
            st[cur].link = 0;
        else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len)
                st[cur].link = q;
            else {
                int clone = sz++;
                st[clone].len = st[p].len + 1;
                st[clone].next = st[q].next;
                st[clone].link = st[q].link;
                for (; p !=- 1 && st[p].next[c] == q; p = st[p].link)
                    st[p].next[c] = clone;
                st[q].link = st[cur].link = clone;

                ///For finding number of occurrences
                cnt[clone] = 0;
                base.insert({st[clone].len, clone});
                ///For finding number of occurrences
            }
        }
        last = cur;
    }

    /**
        Finds the lexicographically earliest longest common substring between the String s
        and string on which automata is built
        Tested Problem: SSTORY(CodeChef)
    **/
    string LongestCommonSubstring(string &s) {
        int v = 0, l = 0, best = 0, bestpos = 0;
        for (int i = 0; i < s.size(); i++) {
            while (v && !st[v].next.count(s[i])) {
                v = st[v].link;
                l = st[v].len;
            }
            if (st[v].next.count(s[i])) {
                v = st[v].next[s[i]];
                l++;
            }
            if (l > best)
                best = l, bestpos = i;
        }
        return s.substr(bestpos - best + 1, best);
    }

    /**
        Finds the number of time(s) String s occurs in the String on which
        automata is built
        Tested Problem: 432D(CF)
    **/

    int OccurrencesPreprocess() {
        for (auto it = base.rbegin(); it != base.rend(); it++)
            cnt[st[it->second].link] += cnt[it->second];
    }

    int Occurrences(string& s) {
        if (isPreProcessed == false) OccurrencesPreprocess();
        isPreProcessed = true;

        int v = 0;
        for (auto &x: s) v = st[v].next[x];

        return cnt[v];
    }
};


int main() {
    /**
        builds automata on String s1 and finds out the Longest common substring between s1 and s2
        string s1, s2;
        cin >> s1 >> s2;
        SuffixAutomata SA;
        SA.BuildAutomata(s1);
        cout << SA.LongestCommonSubstring(s2) << ;
    **/

    return 0;
}