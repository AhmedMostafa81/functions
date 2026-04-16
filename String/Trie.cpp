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
