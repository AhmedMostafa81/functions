// ===================== 2D Fenwick Tree (Binary Indexed Tree) =====================
// ➤ Efficient structure for 2D prefix sums and point updates.
// ➤ Time Complexity:
//     - Point update: O(log N * log M)
//     - Prefix sum query: O(log N * log M)
// ➤ Use Cases:
//     - Dynamic 2D range sum queries
//     - Matrix/grid problems (e.g., subrectangle sums)
// ➤ Note:
//     - Indexing is 0-based
//     - Only supports point updates and prefix sum queries
// =================================================================================

struct FenwickTree2D {
    vector<vector<int>> bit; // 2D BIT array
    int n, m;

    // Constructor to initialize a 2D BIT of size n x m
    void init(int _n, int _m) {
        n = _n;
        m = _m;
        bit.assign(n, vector<int>(m, 0));
    }

    // Add `delta` to element at position (x, y)
    void add(int x, int y, int delta) {
        for (int i = x; i < n; i = i | (i + 1))
            for (int j = y; j < m; j = j | (j + 1))
                bit[i][j] += delta;
    }

    // Query prefix sum in rectangle from (0, 0) to (x, y), inclusive
    int sum(int x, int y) {
        int ret = 0;
        for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
            for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
                ret += bit[i][j];
        return ret;
    }

    // Query sum in subrectangle [(x1,y1), (x2,y2)], inclusive
    int rangeSum(int x1, int y1, int x2, int y2) {
        return sum(x2, y2)
             - sum(x1 - 1, y2)
             - sum(x2, y1 - 1)
             + sum(x1 - 1, y1 - 1);
    }
};
