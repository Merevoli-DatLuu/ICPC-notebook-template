// a * x + b * y = c , c % gcd(a, b) == 0
int diophantine(int a, int b, int c, int & x, int & y) {
    int g = extgcd(a, b, x, y);
    x = c / g * x;
    y = c / g * y;
    return g;
}