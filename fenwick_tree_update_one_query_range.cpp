#include <bits/stdc++.h>

using namespace std;

/*
    Fenwick Tree (Update one, Query range)
    Usage:
    + update(index, value)
    + query_range(index_from, index_to)

    *Note: set value for n before using update and query
*/

const int MAX_N = 2e5 + 1;
int n;
long long ft[MAX_N];

void _set(long long &node, long long value){
    node += value;
}

void _get(long long &res, long long value){
    res += value;
}

void update(int x, long long v) {
    for (; x <= n; x += x & -x){
        _set(ft[x], v);
    }
}

long long get_value(int x) {
    long long res = 0;

    for (; x; x -= x & -x){
        _get(res, ft[x]);
    }
    return res;
}

long long query_range(int l, int r) {
    return get_value(r) - get_value(l - 1);
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
}
