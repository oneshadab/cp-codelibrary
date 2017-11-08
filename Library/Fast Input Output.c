#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/mman.h>

#define clr(ar) (memset(ar, 0, sizeof(ar)))
#define read() freopen("lol.txt", "r", stdin)
#define parse(x) (x = (x * 10) + (str[j] - 48))
#define parse(j, x) (x = (x * 10) + (str[j] - 48))
#define parse(j, x) (x = (x << 1) + (x << 3) + (str[j] - 48))

int ye;
char temp[25], out[1000010];

void convert(int x){
    int i, r, d = 1;

    for (; ;){
        r = (x / 10);
        temp[d++] = (x - (r * 10)) + 48;
        x = r;
        if (!x) break;
    }

    for (i = d - 1; i; i--) out[ye++] = temp[i];
}

void convert(long long x){
    int i, d = 1;
    long long r;

    for (; ;){
        r = (x / 10);
        temp[d++] = (x - (r * 10)) + 48;
        x = r;
        if (!x) break;
    }

    for (i = d - 1; i; i--) out[ye++] = temp[i];
}



void convert(int x){
    int i, r, d = 1;

    for (; ;){
        r = (x * 0.1);
        temp[d++] = (x - (r * 10)) + 48;
        x = r;
        if (!x) break;
    }

    for (i = d - 1; i; i--) out[ye++] = temp[i];
}


char* mmap_in(){
    char* str = mmap(0, 6500000, PROT_READ, MAP_SHARED, fileno(stdin), 0);
    return str;
}

int main(){
    ye = 0;
    convert(123);
    fwrite(out, 1, ye, stdout);
}


#define BUFFER_SIZE 11

const char digits[] = "00010203040506070809101112131415161718192021222324252627282930313233343536373839404142434445464748495051525354555657585960616263646566676869707172737475767778798081828384858687888990919293949596979899";

int ye = 0;
char buf[BUFFER_SIZE], out[100010];

void convert(int val){
    int c = 2, div = val / 100;
    char *it = (char*) &buf[BUFFER_SIZE - 2];

    while (div){
        memcpy(it, &digits[(val - (div * 100)) << 1], 2);
        it -= 2, c += 2;
        val = div;
        div = val / 100;
    }

    memcpy(it, &digits[val << 1], 2);
    if (val < 10) it++, c--;
    memcpy(&out[ye], it, c);
    ye += c;
}
