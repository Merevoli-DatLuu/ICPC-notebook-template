template < class type >
    struct matrix {
        vector < vector < type > > f;
        int m, n;
        matrix(int m = 0, int n = 0): m(m), n(n) {
            f.resize(m);
            for (int i = 0; i < m; i++) {
                f[i].resize(n);
                for (int j = 0; j < n; j++) {
                    f[i][j] = 0;
                }
            }
        }
        void operator = (const matrix & a);
        void print() {
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    cout << f[i][j] << " ";
                }
                cout << "\n";
            }
            cout << "\n";
        }
    };
template < class type >
    matrix < type > identity(int n) {
        matrix < type > i(n, n);
        for (int j = 0; j < n; j++) i.f[j][j] = 1;
        return i;
    }
template < class type >
    matrix < type > operator * (const matrix < type > & a,
        const matrix < type > & b) {
        matrix < type > c(a.m, b.n);
        for (int i = 0; i < c.m; i++)
            for (int j = 0; j < c.n; j++)
                for (int k = 0; k < a.n; k++)
                    c.f[i][j] = (c.f[i][j] + a.f[i][k] * b.f[k][j]) % mod;
        return c;
    }
template < class type >
    matrix < type > operator ^ (const matrix < type > & a, int k) {
        if (k == 0) return identity < type > (a.n);
        if (k == 1) return a;
        matrix < type > t = a ^ (k / 2);
        t = t * t;
        if (k & 1) t = t * a;
        return t;
    }
template < class type >
    void matrix < type > ::operator = (const matrix < type > & a) {
        m = a.m;
        n = a.n;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++) f[i][j] = a.f[i][j];
    }
//Matrix_math
void getCofactor(int mat[N][N], int temp[N][N], int p, int q, int n) {
    int i = 0, j = 0;
    for (int row = 0; row < n; row++)
        for (int col = 0; col < n; col++) {
            if (row != p && col != q) {
                temp[i][j++] = mat[row][col];
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
}
int determinantOfMatrix(int mat[N][N], int n) {
    int D = 0;
    if (n == 1) return mat[0][0];
    int temp[N][N];
    int sign = 1;
    for (int f = 0; f < n; f++) {
        getCofactor(mat, temp, 0, f, n);
        D += sign * mat[0][f] * determinantOfMatrix(temp, n - 1);
        sign = -sign;
    }
    return D;
}
void adjoint(int A[N][N], int adj[N][N]) {
    if (N == 1) {
        adj[0][0] = 1;
        return;
    }
    int sign = 1, temp[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            getCofactor(A, temp, i, j, N);
            sign = ((i + j) % 2 == 0) ? 1 : -1;
            adj[j][i] = (sign) * (determinant(temp, N - 1));
        }
}
bool inverse(int A[N][N], double inverse[N][N]) {
    int det = determinant(A, N);
    if (det == 0) return false;
    int adj[N][N];
    adjoint(A, adj);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) inverse[i][j] = adj[i][j] / double(det);
    return true;
}