#include <bits/stdc++.h>

using namespace std;

/*
    Fenwick Tree (Update range, Query range)
    Usage:
    + update(index, value)
    + update_range(index_from, index_to, value)
    + query(index)
    + query_range(index_from, index_to)

    *Note: set value for n before using update and query
*/

const int MAX_N = 1e5 + 1;
int n, q;
long long ft_1[MAX_N], ft_2[MAX_N];

void _set(long long &node, long long value){
    node += value;
}

void _get(long long &res, long long value){
    res += value;
}

void _update(long long *ft, int x, long long v) {
    for (; x <= n; x += (x & -x)){
        _set(ft[x], v);
    }
}

void update_range(int l, int r, long long v) {
    _update(ft_1, l, v);
    _update(ft_1, r + 1, -v);
    _update(ft_2, l, v * (l - 1));
    _update(ft_2, r + 1, -v * r);
}

void update(int x, long long v){
    update_range(x, x, v);
}

long long get_value(long long *ft, int x) {
    long long res = 0;

    for (; x; x -= (x & -x)){
        _get(res, ft[x]);
    }
    return res;
}

long long _query(int x) {
    return get_value(ft_1, x) * x - get_value(ft_2, x);
}

long long query_range(int l, int r) {
    return _query(r) - _query(l - 1);
}

long long query(int x){
    return query_range(x, x);
}

/********************************************************************/

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    n = 5;

    update(1, 1);
    cout << query_range(1, 5) << '\n';
    cout << query_range(1, 3) << '\n';
    cout << query_range(3, 5) << '\n';
    cout << '\n';
    update(2, 1);
    cout << query_range(1, 5) << '\n';
    cout << query_range(1, 3) << '\n';
    cout << query_range(3, 5) << '\n';
    cout << '\n';
    update(3, 1);
    cout << query_range(1, 5) << '\n';
    cout << query_range(1, 3) << '\n';
    cout << query_range(3, 5) << '\n';
    cout << '\n';
    update(4, 1);
    cout << query_range(1, 5) << '\n';
    cout << query_range(1, 3) << '\n';
    cout << query_range(3, 5) << '\n';
    cout << '\n';
    update(5, 1);
    cout << query_range(1, 5) << '\n';
    cout << query_range(1, 3) << '\n';
    cout << query_range(3, 5) << '\n';
    cout << '\n';
    update(2, 2);
    cout << query_range(1, 5) << '\n';
    cout << query_range(1, 3) << '\n';
    cout << query_range(3, 5) << '\n';
    cout << '\n';
    update(3, 3);
    cout << query_range(1, 5) << '\n';
    cout << query_range(1, 3) << '\n';
    cout << query_range(3, 5) << '\n';
    cout << '\n';

    cout << query(1) << '\n';
    cout << query(2) << '\n';
    cout << query(3) << '\n';
    cout << query(4) << '\n';
    cout << query(5) << '\n';
    cout << '\n';

    update_range(1, 5, 1);
    cout << query_range(1, 5) << '\n';
    cout << query_range(1, 3) << '\n';
    cout << query_range(3, 5) << '\n';
    cout << '\n';
    cout << query(1) << '\n';
    cout << query(2) << '\n';
    cout << query(3) << '\n';
    cout << query(4) << '\n';
    cout << query(5) << '\n';
    cout << '\n';

    update_range(2, 3, 3);
    cout << query_range(1, 5) << '\n';
    cout << query_range(1, 3) << '\n';
    cout << query_range(3, 5) << '\n';
    cout << '\n';
    cout << query(1) << '\n';
    cout << query(2) << '\n';
    cout << query(3) << '\n';
    cout << query(4) << '\n';
    cout << query(5) << '\n';
    cout << '\n';

}
