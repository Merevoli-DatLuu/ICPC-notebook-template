const int maxc = 256;
struct trie {
    struct node {
        int a[maxc];
        int val;
        int & operator[](int i) {
            return a[i % maxc];
        }
        node() {
            memset(a, 0, sizeof(a));
            val = 0;
        }
    };
    vector < node > a;
    int & operator[](string s) {
        int pos = 0, c;
        for (int i = 0; c = s[i]; i++) {
            if (a[pos][c] == 0) {
                a.push_back(node());
                a[pos][c] = a.size() - 1;
            }
            pos = a[pos][c];
        }
        return a[pos].val;
    }
    void clear() {
        a.clear();
        a.push_back(node());
    }
    trie() {
        clear();
    }
}
tr;