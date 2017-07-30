#include <bits/stdc++.h>

using namespace std;

struct FastIO {
    static const int MaxSize = 8192;
    char in[MaxSize + 10], out[MaxSize], buffer[MaxSize];
    int len, pos, cnt;

    char nextChar() {
        if (pos == len) len = fread(in, sizeof(char), MaxSize, stdin), pos = 0;
        if (pos == len) return EOF;
        return in[pos++];
    }

    void printChar(char ch) {
        if (cnt == MaxSize) flush();
        out[cnt++] = ch;
    }

    void flush() {
        if (cnt) fwrite(out, sizeof(char), cnt, stdout);
        cnt = 0;
    }

    ~FastIO() {
        flush();
    }

    /* For Numbers */
    template<typename T,
            typename = typename enable_if<is_integral<T>::value, T>::type>
    FastIO &operator>>(T &num) {
        num = 0;
        char ch = nextChar(), neg = false;
        while (!isdigit(ch) && ch != '-' && ch != '+') ch = nextChar();
        if (ch == '-' || ch == '+') neg = (ch == '-'), ch = nextChar();
        while (isdigit(ch)) num = num * 10 + ch - '0', ch = nextChar();
        if (neg) num = -num;
        return *this;
    }

    template<typename T,
            typename = typename enable_if<is_integral<T>::value, T>::type>
    FastIO &operator<<(T num) {
        int n = 0, neg = false;
        if (num < 0) neg = true, num = -num;
        while (num || !n) buffer[n++] = num % 10 + '0', num = num / 10;
        if (neg) printChar('-');
        while (n) printChar(buffer[--n]);
        return *this;
    }

    /* For Characters */
    FastIO &operator>>(char &ch) {
        ch = nextChar();
        return *this;
    }

    FastIO &operator<<(char ch) {
        printChar(ch);
        return *this;
    }

    /*For Strings */
    FastIO &operator>>(string &s) {
        s.clear();
        char ch = nextChar();
        while (ch == ' ' || ch == '\n') ch = nextChar();
        while (ch != ' ' && ch != '\n') s.push_back(ch), ch = nextChar();
        return *this;
    }

    FastIO &operator<<(string s) {
        for (auto ch: s) printChar(ch);
        return *this;
    }
    /*For Doubles */

} fio;

int main() {
    //SPOJ INTEST
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long n, k, ans = 0;
    fio >> n >> k;
    for (int i = 0; i < n; i++) {
        int x;
        fio >> x;
        if (x % k == 0) ans++;
    }
    fio << ans;
}
