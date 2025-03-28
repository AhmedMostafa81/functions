struct Trie {
    const int BIT = 30;
    struct Node {
        static const int MX = 2;
        int children[MX] = {};
        int f = 0;
    };

    vector<Node> trie;

    Trie() {
        trie.emplace_back();
        insert(0);
    }

    void insert(int x) {
        int idx = 0;
        for(int bit = BIT; bit >= 0; bit--) {
            int nxt = ((x&(1<<bit)) != 0);

            if(trie[idx].children[nxt] == 0) {
                trie[idx].children[nxt] = trie.size();
                trie.emplace_back();
            }
            idx = trie[idx].children[nxt];
            trie[idx].f++;
        }
    }

    void erase(int x) {
        int idx = 0;
        for(int bit = BIT; bit >= 0; bit--) {
            int nxt = ((x&(1<<bit)) != 0);

            idx = trie[idx].children[nxt];
            trie[idx].f--;
        }
    }

    int query(int x) {
        int idx = 0;
        int ret = 0;
        for(int bit = BIT; bit >= 0; bit--) {
            int nxt = ((x&(1<<bit)) == 0);

            if(trie[trie[idx].children[nxt]].f == 0)
                nxt ^= 1;
            else
                ret |= (1<<bit);
            idx = trie[idx].children[nxt];
        }
        return ret;
    }

    void clear() {
        trie.clear();
        trie.emplace_back();
        insert(0);
    }
};

struct Trie {
    struct Node {
        static const int MX = 29;
        int children[MX] = {};
        int f = 0;
    };

    vector<Node> trie;

    Trie() {
        trie.emplace_back();
    }

    void insert(string& s) {
        int idx = 0;
        for(auto i : s) {
            int nxt = i-'a';

            if(trie[idx].children[nxt] == 0) {
                trie[idx].children[nxt] = trie.size();
                trie.emplace_back();
            }
            idx = trie[idx].children[nxt];
            trie[idx].f++;
        }
    }

    void erase(string& s) {
        int idx = 0;
        for(auto i : s) {
            int nxt = i-'a';

            idx = trie[idx].children[nxt];
            trie[idx].f--;
        }
    }

    int query(string& s) {
        int idx = 0;
        for(auto i : s) {
            int nxt = i-'a';
            if(trie[trie[idx].children[nxt]].f == 0)
                return 0;
            idx = trie[idx].children[nxt];
        }
        return trie[idx].f;
    }
};
