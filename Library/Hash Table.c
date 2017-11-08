#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define PAD  66667
#define HMOD 1000033
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

int id = 1, entry[HMOD + PAD];
unsigned int hashtable[HMOD + PAD];

void insert(unsigned int x){
    int i = x % HMOD;
    while (entry[i] == id && hashtable[i] != x) i++;
    hashtable[i] = x, entry[i] = id;
}

bool find(unsigned int x){
    int i = x % HMOD;
    while (entry[i] == id && hashtable[i] != x) i++;
    return (entry[i] == id);
}

int main(){

}
