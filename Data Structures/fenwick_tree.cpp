template<typename T>
struct fenwick_tree {
    int n{};
    vector<T> bit;
    const T DEFAULT = 0;

    fenwick_tree() = default;

    void init(int n_) {
        this->n = n_;
        bit.assign(n_ + 1, DEFAULT);
    }

    explicit fenwick_tree(int n) {
        init(n);
    }
    //   lazm tdyha vector 1-based
    explicit fenwick_tree(vector<T> &v) : fenwick_tree(int(v.size())) {
        int idx = 1;
        while (idx < n) {
            add(idx , v[idx]);
            idx++;
        }
    }

    void add(int idx, T value) {
        while (idx <= n) {
            bit[idx] += value;
            idx += idx & -idx;
        }
    }

    T prefix(int idx) {
        T ret = 0;
        while (idx) {
            ret += bit[idx];
            idx ^= idx & -idx;
        }
        return ret;
    }

    T rangeSum(int l, int r) {
        if (l > r)
            return 0;
        return prefix(r) - prefix(l - 1);
    }

};
