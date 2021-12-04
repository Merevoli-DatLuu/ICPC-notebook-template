void misc() {
    cout << (n & (n - 1)) << "\n"; // set last one bit to 0
    cout << (n & -n) << "\n"; // set all to 0 except for last one bit
    cout << (n | (n - 1)) << "\n"; // invert all bit after last one bit
    cout << (n & (n - 1)) << "\n"; // if power of two equal 0
    cout << __builtin_clz(n) << "\n"; // the number of leading 0-bits in x
    cout << __builtin_ctz(n) << "\n"; // the number of trailing 0-bits in x
    cout << __builtin_popcount(n) << "\n"; // the number of 1-bits in x
    cout << __builtin_parity(n) << "\n"; // the number of 1-bits in x modulo 2.
}