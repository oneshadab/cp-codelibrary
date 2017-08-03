#include <bits/stdc++.h>

using namespace std;

/*
    Chinese Remainder Theorem Finds X % M
    Where,
        M = mod[0] * mod[1] * mod[2] ...
    And,
        r[0] = X % mod[0]
        r[1] = X % mod[1]
        r[2] = X % mod[2]
        ....
    Where mod[0], mod[1], mod[2] ... are co-prime

    NOTE:
    if there is a possibility of k being very big, then
    prime factorize m[i], find modular inverse of 'tmp'
    of each of the factors 'k' equals to the multiplication
    (modular mods[i]) of modular inverses
*/


typedef long long ll;
ll CRT (vector<ll> &r, vector<ll> &mods) {
	ll M = 1, ret = 0, n = mods.size();
	for (int i = 0; i < n; i++) M *= mods[i];
	for (int i = 0; i < n; i++) {
		ll m = M / mods[i], tmp = m % mods[i], k = 0;
        while((k * tmp) % mods[i] != 1) k++;
		ret += ((m * k) % M *r[i]) % M;
		ret %= M;
    }
	return ret;
}
