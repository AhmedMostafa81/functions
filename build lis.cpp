// Longest Increasing Subsequence (strictly increasing)
// Returns indices of one LIS
// Time: O(n log n)

vector<int> LIS(const vector<int>& a) {
    int n = a.size();
    vector<int> parent(n, -1);
    vector<int> tail;        // tail values
    vector<int> tail_idx;    // index of tail values

    for (int i = 0; i < n; i++) {
        int pos = lower_bound(tail.begin(), tail.end(), a[i]) - tail.begin();

        if (pos == (int)tail.size()) {
            tail.push_back(a[i]);
            tail_idx.push_back(i);
        } else {
            tail[pos] = a[i];
            tail_idx[pos] = i;
        }

        if (pos > 0)
            parent[i] = tail_idx[pos - 1];
    }

    // reconstruct LIS
    vector<int> lis;
    int cur = tail_idx.back();
    while (cur != -1) {
        lis.push_back(cur);      // push index
        cur = parent[cur];
    }
    reverse(lis.begin(), lis.end());
    return lis;   // indices of LIS
}
