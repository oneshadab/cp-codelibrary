#include <bits/stdtr1c++.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl

using namespace std;

/// SPOJ MAKESUM
/// Returns lexicographically smallest positive solution in vector res for pairsum vector ar, false if none exists

bool Pairsum(vector <int> ar, vector <int>& res){
    res.clear();
    sort(ar.begin(), ar.end());
    int i, j, k, l, a, b, x, n = ar.size();

    if (n == 0){
        res.push_back(1); /// Since only positive solution is required
        return true;
    }
    if (n == 1){
        if (ar[0] < 2) return false; /// Since only positive solution is required
        res.push_back(1), res.push_back(ar[0] - 1); /// Since only positive solution is required
        return true;
    }

    res.resize(n, 0);
    a = ar[0], b = ar[1];
    vector <int> lex_smallest;

    for (i = 2, k = 2; i * (i - 1) < 2 * n && k < n; i++, k++){
        if ((a + b - ar[k]) & 1 ^ 1){
            j = 1, res[0] = (a + b - ar[k]) >> 1;
            multiset <int> S(ar.begin(), ar.end());

            while (S.size() && res[0] > 0){ /// Since only positive solution is required
                res[j] = *S.begin() - res[0];
                for (l = 0; l < j && !S.empty(); l++){
                    auto pos = S.find(res[l] + res[j]);
                    if (pos == S.end()) goto skip;
                    S.erase(pos);
                }
                j++;
            }

            skip:
            if (j * (j - 1) == 2 * n){
                res.resize(j);
                sort(res.begin(), res.end());
                if (!lex_smallest.size() || res < lex_smallest) lex_smallest = res;
            }
        }
    }
    res = lex_smallest;
    return (lex_smallest.size() > 0);
}

/// UVA Pairsumonious Numbers
/// Returns any valid solution in vector res for pairsum vector ar, false if none exists

bool Pairsum(vector <int> ar, vector <int>& res){
    res.clear();
    sort(ar.begin(), ar.end());
    int i, j, k, l, a, b, x, n = ar.size();

    if (n == 0){
        res.push_back(1);
        return true;
    }
    if (n == 1){
        if (ar[0] < 2) return false;
        res.push_back(1), res.push_back(ar[0] - 1);
        return true;
    }

    res.resize(n, 0);
    a = ar[0], b = ar[1];
    for (i = 2, k = 2; i * (i - 1) < 2 * n && k < n; i++, k++){
        if ((a + b - ar[k]) & 1 ^ 1){
            j = 1, res[0] = (a + b - ar[k]) >> 1;
            multiset <int> S(ar.begin(), ar.end());

            while (S.size()){
                res[j] = *S.begin() - res[0];
                for (l = 0; l < j && !S.empty(); l++){
                    auto pos = S.find(res[l] + res[j]);
                    if (pos == S.end()) goto skip;
                    S.erase(pos);
                }
                j++;
            }

            skip:
            if (j * (j - 1) == 2 * n){
                res.resize(j);
                sort(res.begin(), res.end());
                return true;
            }
        }
    }
    return false;
}

int main(){
    vector <int> res;
    vector <int> ar = {216, 210, 204, 212, 220, 214, 222, 208, 216, 210};

    if (Pairsum(ar, res)){
        for (i = 0; i < res.size(); i++) printf("%d ", res[i]); /// output = 101 103 107 109 113
        puts("");
    }
    return 0;
}
