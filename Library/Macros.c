#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("avx,tune=native")

#define gen() freopen("lol.txt", "w", stdout)
#define write() freopen("output.txt", "w", stdout)
#define test1() freopen("test1.txt", "w", stdout)
#define test2() freopen("test2.txt", "w", stdout)
#define optimize(str) __attribute__((optimize(str)))
#define rand(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

#define min(a,b) ((a)<(b) ? (a):(b))
#define max(a,b) ((a)>(b) ? (a):(b))
#define swap(a,b) ((a) = (a) + (b) - (b = a))

#define setbit(x, i) ((x) | (1 << (i)))
#define pow2(x) ((x) && !((x) & ((x) - 1)))
#define resetbit(x, i) ((x) & (~(1 << (i))))
#define getbit(x, i) (((x) & (1 << (i))) ? (1):(0))

const int dx[] = {0, 0, -1, 1};
const int dy[] = {-1, 1, 0, 0};
const int dx[] = {0, 0, -1, 1, -1, -1, 1, 1};
const int dy[] = {-1, 1, 0, 0, -1, 1, -1, 1};
const int knightx[] = {-1, -1, 1, 1, -2, -2, 2, 2};
const int knighty[] = {-2, 2, -2, 2, -1, 1, -1, 1};
#define valid(i, j) ((i) >= 0 && (i) < n && (j) >= 0 && (j) < n)
#define valid(i, j) ((i) >= 0 && (i) < n && (j) >= 0 && (j) < m)

/***************************************
swap works perfectly for any signed integer, most probably works great for doubles too
pow2 works perfectly for any signed integer, except for -(2^31) = -2147483648
***************************************/

int main(){ optimize("O3");

}
