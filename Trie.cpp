const int BIT = 30  ;
struct Node {
    int ch[2] = {};
    int f = 0;
}neutral;
 
vector<Node> trie;
struct Trie {
 
    Trie() {
        trie.pb(neutral);
        insert(0);
    }
 
    void insert (int x) {
        int cur = 0;
        for (int b = BIT;b>=0;b--) {
            int nxt = ((x&(1ll<<b)) != 0);
            if (!trie[cur].ch[nxt]) {
                trie[cur].ch[nxt] = trie.size();
                trie.pb(neutral);
            }
            cur = trie[cur].ch[nxt];
            trie[cur].f++;
        }
    }
 
    void erase(int x) {
        int idx = 0;
        for(int bit = BIT; bit >= 0; bit--) {
            int nxt = ((x&(1<<bit)) != 0);
 
            idx = trie[idx].ch[nxt];
            trie[idx].f--;
        }
    }
 
    int ans(int x) {
        int idx = 0;
        int ret = 0;
        for(int bit = BIT; bit >= 0; bit--) {
            int nxt = ((x&(1<<bit)) == 0);
 
            if(trie[trie[idx].ch[nxt]].f == 0)
                nxt ^= 1;
            else
                ret |= (1<<bit);
            idx = trie[idx].ch[nxt];
        }
        return ret;
    }
 
 
};
