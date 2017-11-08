#include <stdio.h>

/***

1. Sum of all numbers less than or equal to n and also co-prime to n = (phi(n) * n) / 2

2. Lagrange's Polnomial:
   A polynomial of degree n can be uniquely represented and evaluated from it's value in n + 1 distinct points (x_i, y_i)

   For the function f(x) = x ^2, given three points

    x_0 = 1, f(x_0) = 1
    x_1 = 2, f(x_1) = 4
    x_2 = 3, f(x_2) = 9

    The interpolating polynomial is:

             1*(x-2)(x-3) + 4*(x-1)(x-3) + 9*(x-1)(x-2)
    L(x) =    ----------     ----------     ----------    =  x^2
              (1-2)(1-3)     (2-1)(2-3)     (3-1)(3-2)

3. Eulerian Numbers, E(n, k): Number of permutations from 1 to n such that
   P_i < P_(i+1) (or P_i > P_(i + 1) since symmetric) in exactly k positions.
   Recurrence: E(n, k) = (k+1)E(n - 1, k) + (n - k)(n - 1, k - 1)
***/

int main(){
}
