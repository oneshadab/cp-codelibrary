#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

/* Machine Dependent + Not so fast when compared to math.h sqrt() */

float F(float y){
    long i;
    float x;
    const float threehalfs = 1.5F;

    x = y * 0.5F;
    i = *(long *) &y;
    i  = 0x5f3759df -(i >> 1);
    y  = *(float *) &i;

    y  = y * (threehalfs - (x * y * y )); /* Repeat this to increase precision */
    y  = y * (threehalfs - (x * y * y ));
    y  = y * (threehalfs - (x * y * y ));
    y  = y * (threehalfs - (x * y * y ));
	return (1.0 / y);
}

double root(double y){
    double x;
    long long i;
    const double threehalfs = 1.5;

    x = y * 0.5;
    i = *(long long*) (&y);
    i = 0x5fe6ec85e7de30daLL - (i >> 1);
    y = *(double*) (&i);

    y = y * (1.5 - x * y * y); /* Repeat this to increase precision */
    y = y * (1.5 - x * y * y);
    y = y * (1.5 - x * y * y);
    y = y * (1.5 - x * y * y);
    return (1.0 / y);
}

int main(){
    printf("%0.9lf %0.9lf\n", F(25.0), root(25.0));
}
