#include <bits/stdtr1c++.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl

using namespace std;

namespace fastio{
    int ptr, ye;
    char temp[25], str[31333667], out[31333667];

    void init(){
        ptr = 0, ye = 0;
        fread(str, 1, 31333667, stdin);
    }

    inline long long number(){
        int i, j, neg = 0;
        long long val = 0;

        while (str[ptr] < 45 || str[ptr] > 57) ptr++;
        if (str[ptr] == 45) neg++, ptr++;
        while (str[ptr] > 47 && str[ptr] < 58) val = (val * 10) + (str[ptr++] - 48);
        if (neg) val = -val;
        return val;
    }

    inline void convert(long long x){
        int i, d = 0;
        if (x < 0) x = -x, out[ye++] = 45;

        for (; ;){
            temp[++d] = (x % 10) + 48;
            x /= 10;
            if (!x) break;
        }

        for (i = d; i; i--) out[ye++] = temp[i];
    }

    inline void print(){
        fwrite(out, 1, ye, stdout);
    }

    inline void append(char ch){
        out[ye++] = ch;
    }
}

int main(){

}
