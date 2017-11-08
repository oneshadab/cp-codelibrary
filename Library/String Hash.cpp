#include <bits/stdtr1c++.h>

#define MAXLEN 100010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl

using namespace std;

class StringHash{
    public:

    int n;
    char str[MAXLEN];
    unsigned long long base = 1925728309;
    unsigned long long P[MAXLEN], ar[MAXLEN], rev[MAXLEN];

    StringHash(){
    }

    StringHash(char* temp){
        strcpy(str, temp);
        n = strlen(str);
        Generate();
    }

    void Generate(){
        int i;
        unsigned long long x;

        P[0] = 1;
        for (i = 1; i <= n; i++) P[i] = (P[i - 1] * base);

        x = 0;
        for (i = 0; i < n; i++){
            x = (x * base) + str[i];
            ar[i] = x;
        }

        x = 0;
        for (i = n - 1; i >= 0; i--){
            x = (x * base) + str[i];
            rev[i] = x;
        }
    }

    unsigned long long forward_hash(int i, int j){
        unsigned long long x = ar[j];
        if (i){
            unsigned long long y = P[j - i + 1] * ar[i - 1];
            x -= y;
        }
        return x;
    }

    unsigned long long reverse_hash(int i, int j){
        unsigned long long x = rev[i];
        if ((j + 1) != n){
            unsigned long long y = P[j - i + 1] * rev[j + 1];
            x -= y;
        }
        return x;
    }
};

int main(){
    char* str = "Hello World";
    StringHash S = StringHash(str);
}
