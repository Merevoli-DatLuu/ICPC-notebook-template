#include <bits/stdc++.h>

using namespace std;

/*
    Segment Tree (Update one, Query range)
    Usage:
    + update(index, value)
    + query_range(index_from, index_to)

    *Note: set value for n before using update and query
*/

const int MAX_N = 1e5 + 1;
int n;
long long st[MAX_N];

void _set(long long &node, long long value){
    node += value;
}

long long _get(long long left_node, long long right_node){
    return left_node + right_node;
}

void update(int x, long long value, int id = 1, int l = 1, int r = n){
	if (x < l || r < x){
        return;
    }
	if (l == r){
		_set(st[id], value);
		return;
	}

	int mid = (l + r) >> 1;
	update(x, value, id << 1, l, mid);
	update(x, value, id << 1 | 1, mid + 1, r);
	st[id] = _get(st[id << 1], st[id << 1 | 1]);
}

long long query_range(int start_pos, int end_pos, int id = 1, int l = 1, int r = n){
	if (r < start_pos || l > end_pos){
        return 0;
	}
	if (l >= start_pos && r <= end_pos){
        return st[id];
	}

	int mid = (l + r) >> 1;
	return _get(
        query_range(start_pos, end_pos, id << 1, l, mid),
        query_range(start_pos, end_pos, id << 1 | 1, mid + 1, r)
    );
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
