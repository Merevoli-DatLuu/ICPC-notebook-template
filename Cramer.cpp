LL det(int a1, int b1, int c1, int a2, int b2, int c2, int a3, int b3, int c3) {
    return +a1 * (b2 * c3 - b3 * c2) - b1 * (a2 * c3 - a3 * c2) + c1 * (a2 * b3 - a3 * b2);
}
void cramer(int a1, int b1, int c1, int d1, int a2, int b2, int c2, int d2,
    int a3, int b3, int c3, int d3) {
    LL D = det(a1, b1, c1, a2, b2, c2, a3, b3, c3);
    double DX = det(d1, b1, c1, d2, b2, c2, d3, b3, c3);
    double DY = det(a1, d1, c1, a2, d2, c2, a3, d3, c3);
    double DZ = det(a1, b1, d1, a2, b2, d2, a3, b3, d3);
    if (D == 0) cout << "Math error\n";
    else cout << DX / D << " " << DY / D << " " << DZ / D << "\n";
}