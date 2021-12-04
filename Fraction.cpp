Fraction(double f) {
    double integral = floor(f);
    double frac = f - integral;
    const T precision = 1000000000;
    T gcd_ = __gcd((T) round(frac * precision), precision);
    T denominator = precision / gcd_;
    T numerator = round(frac * precision) / gcd_;
    a = integral * denominator + numerator;
    b = denominator;
    norm();
}