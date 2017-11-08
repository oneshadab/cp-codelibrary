#include <bits/stdtr1c++.h>

#define LOG 18
#define MAX 50010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

namespace sa{
    char str[MAX];
    int n, m, freq[MAX], ar[MAX], lcp[MAX], temp[MAX], dp[LOG][MAX];

    int getlcp(int a, int b) {
        int i, l, res = 0;
        for (i = LOG - 1; i >= 0; i--) {
            l = 1 << i;
            if (l <= n && dp[i][a] == dp[i][b]) res += l, a += l, b += l;
        }
        return res;
    }

    long long distinct_substrings(){
        long long res = ((long long)n * (n + 1)) >> 1;
        for (int i = 0; (i + 1) < n; i++) res -= lcp[i];
        return res;
    }

    void build(char* hello, int gen_lcp){
        int i, j, k, l, h;
        strcpy(str, hello);
        n = strlen(str) + 1;

        clr(freq);
        for (i = 0; i < n; i++) freq[str[i]]++;
        for (i = 1; i < 256; i++) freq[i] += freq[i - 1];

        for (i = 0; i < n; i++){
            ar[freq[str[i]] - 1] = i;
            freq[str[i]]--;
        }

        dp[0][ar[0]] = 1;
        for (i = 1, m = 1; i < n; i++) {
            if (str[ar[i]] != str[ar[i - 1]]) m++;
            dp[0][ar[i]] = m;
        }

        for (i = 1; ;i++) {
            h = 1 << (i - 1);
            for (j = 0; j < n; j++) {
                temp[j] = ar[j] - h;
                if (temp[j] < 0) temp[j] += n;
            }

            for (j = 1; j <= m; j++) freq[j] = 0;
            for (j = 0; j < n; j++)  freq[dp[i - 1][temp[j]]]++;
            for (j = 2; j <= m; j++) freq[j] += freq[j - 1];

            for (j = n - 1; j >= 0; j--) {
                ar[freq[dp[i - 1][temp[j]]] - 1] = temp[j];
                freq[dp[i - 1][temp[j]]]--;
            }

            dp[i][ar[0]] = 1;
            for (j = 1, m = 1; j < n; j++) {
                k = ar[j] + h, l = ar[j - 1] + h;
                if (k >= n) k -= n;
                if (l >= n) l -= n;
                if ((dp[i - 1][ar[j]] != dp[i - 1][ar[j - 1]]) || (dp[i - 1][k] != dp[i - 1][l])) m++;
                dp[i][ar[j]] = m;
            }

            if ((1 << i) >= n) break;
        }

        for (i = 0; i < n; i++) ar[i] = ar[i + 1];
        n--;

        if (gen_lcp){
            for (i = 0; i < n; i++) temp[ar[i]] = i;
            for (k = 0, i = 0; i < n; i++, k ? k-- : 0){
                if (temp[i] == (n - 1)) k = 0;
                else{
                    j = ar[temp[i] + 1];
                    while(((i + k) < n) && ((j + k) < n) && (str[i + k] == str[j + k])) k++;
                }
                lcp[temp[i]] = k;
            }
        }
    }
}

int main(){
}


namespace suffix_array{ /// N log^N
    int n, g;
    vector <int> sa, pos, temp;

    inline bool compare(int i, int j){
        if (pos[i] != pos[j]) return (pos[i] < pos[j]);
        i += g, j += g;
        return (i < n && j < n) ? (pos[i] < pos[j]) : (i > j);
    }

    vector<int> construct(char* str){
        n = strlen(str);
        sa.resize(n, 0), pos.resize(n, 0), temp.resize(n, 0);

        for (int i = 0; i < n; i++) sa[i] = i, pos[i] = str[i];
        for (g = 1; ; g<<= 1){
            sort(sa.begin(), sa.end(), compare);
            for (int i = 0; (i + 1) < n; i++) temp[i + 1] = temp[i] + compare(sa[i], sa[i + 1]);
            for (int i = 0; i < n; i++) pos[sa[i]] = temp[i];
            if (temp[n - 1] == n - 1) break;
        }
        return sa;
    }
};
