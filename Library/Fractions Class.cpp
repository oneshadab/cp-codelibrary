#include <bits/stdtr1c++.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl

using namespace std;

struct Fraction{
    long long numerator, denominator;

    long long gcd(long long a, long long b){
        while (b) b ^= a ^= b ^= a %= b;
        return a;
    }

    Fraction(){}

    Fraction(long long x, long long y){
        long long g = gcd(abs(x), abs(y));
        numerator = x / g;
        denominator = y / g;
    }

    Fraction operator+ (Fraction);
    Fraction operator- (Fraction);
    Fraction operator* (Fraction);
    Fraction operator/ (Fraction);
};

Fraction Fraction::operator+ (Fraction param){
    long long x = (numerator * param.denominator) + (denominator * param.numerator);
    long long y = (denominator * param.denominator);
    return Fraction(x, y);
}

Fraction Fraction::operator- (Fraction param){
    long long x = (numerator * param.denominator) - (denominator * param.numerator);
    long long y = (denominator * param.denominator);
    return Fraction(x, y);
}

Fraction Fraction::operator* (Fraction param){
    long long x = (numerator * param.numerator);
    long long y = (denominator * param.denominator);
    return Fraction(x, y);
}

Fraction Fraction::operator/ (Fraction param){
    long long x = (numerator * param.denominator);
    long long y = (denominator * param.numerator);
    return Fraction(x, y);
}

int main(){

}
