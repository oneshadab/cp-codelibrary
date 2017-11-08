#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

const long double PI = 2.0 * acos(0.0);

/// latitude and longitude of 2 points in degrees and radius of earth
long double haversine(long double lat1, long double lon1, long double lat2, long double lon2, long double radius){
    lat1 = (lat1 * PI) / 180.0;
    lat2 = (lat2 * PI) / 180.0;
    lon1 = (lon1 * PI) / 180.0;
    lon2 = (lon2 * PI) / 180.0;

    return radius * acos(sin(lat1) * sin(lat2) + cos(lon2 - lon1) * cos(lat1) * cos(lat2));
}

int main(){

}
