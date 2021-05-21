#include <bits/stdc++.h>

using namespace std;

/*
    Enables reading 128-bit integers
*/
#ifdef __SIZEOF_INT128__
  template<> struct std::is_integral<__int128_t>: true_type {};
#endif

struct FastIO {
    static const int MaxSize = 8192;
    bool isEOF;
    
    char in[MaxSize+10], out[MaxSize+10], buffer[MaxSize+10];
    int inPos, inSize, outSize;
    
    char nextChar() {
        if (inPos == inSize) inSize = fread(in, sizeof(char), MaxSize, stdin), inPos = 0;
        if (inPos == inSize) return isEOF = true, EOF;
        return in[inPos++];
    }

    void printChar(char ch) {
        if (outSize == MaxSize) flush();
        out[outSize++] = ch;
    }

    void flush() {
        if (outSize) fwrite(out, sizeof(char), outSize, stdout);
        outSize = 0;
    }

    ~FastIO() {
        flush();
    }
    
    /* For EOF */
    explicit operator bool() const {
        return !isEOF;
    }

    /* For Numbers */
    template<
        typename T,
        typename = typename enable_if<is_integral<T>::value, T>::type>
    FastIO& operator>>(T &num) {
        num = 0;
        char ch = nextChar(), neg = false;
        while (ch != EOF && !isdigit(ch) && ch != '-' && ch != '+') ch = nextChar();
        if (ch != EOF && ch == '-' || ch == '+') neg = (ch == '-'), ch = nextChar();
        while (ch != EOF && isdigit(ch)) num = num * 10 + ch - '0', ch = nextChar();
        if (neg) num = -num;
        return *this;
    }

    template<
        typename T,
        typename = typename enable_if<is_integral<T>::value, T>::type>
    FastIO& operator<<(T num) {
        int n = 0, neg = false;
        if (num < 0) neg = true, num = -num;
        while (num || !n) buffer[n++] = num % 10 + '0', num = num / 10;
        if (neg) printChar('-');
        while (n) printChar(buffer[--n]);
        return *this;
    }

    /* For Characters */
    FastIO& operator>>(char &ch) {
        ch = nextChar();
        return *this;
    }

    FastIO& operator<<(char ch) {
        printChar(ch);
        return *this;
    }

    /*For Strings */
    FastIO& operator>>(string &s) {
        s.clear();
        char ch = nextChar();
        while (ch != EOF && ch == ' ' || ch == '\n') ch = nextChar();
        while (ch != EOF && ch != ' ' && ch != '\n') s.push_back(ch), ch = nextChar();
        return *this;
    }

    FastIO& operator<<(string s) {
        for (auto ch: s) printChar(ch);
        return *this;
    }
    
    /*For Doubles */

} fio;

int main() {
    //SPOJ INOUTTEST
    int n;
    fio >> n;
    for (int i = 0; i < n; i++) {
        int a, b;
        fio >> a >> b;
        fio << (a * b) << "\n";
    }
}
 