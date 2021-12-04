int pointer;
vector < long long > M, B;
bool bad(int l1, int l2, int l3) {
    return (B[l3] - B[l1]) * (M[l1] - M[l2]) < (B[l2] - B[l1]) * (M[l1] - M[l3]);
}
void add(long long m, long long b) {
    M.push_back(m);
    B.push_back(b);
    while (M.size() >= 3 && bad(M.size() - 3, M.size() - 2, M.size() - 1)) {
        M.erase(M.end() - 2);
        B.erase(B.end() - 2);
    }
}
long long query(long long x) {
    if (pointer >= M.size()) pointer = M.size() - 1;
    while (pointer < M.size() - 1 && M[pointer + 1] * x + B[pointer + 1] > M[pointer] * x + B[pointer])
        pointer++;
    return M[pointer] * x + B[pointer];
}