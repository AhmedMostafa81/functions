#include <bits/stdc++.h>
using namespace std;
using u64 = unsigned long long;

// Compact, flexible XOR basis (linear basis) for competitive programming.
// - Stores a basis with one vector per bit position (0..63).
// - Insert is O(LOG). Queries are O(LOG).
// - Provided operations: insert, canRepresent, getMax (maximize x^span),
//   getMaxSubset (maximum xor of any subset), merge, getBasis, rank, countDistinct,
//   normalize (reduced echelon form).

struct XorBasis {
    static const int LOG = 64;            // change to 32 for 32-bit numbers
    array<u64, LOG> b;                   // b[i] has pivot at bit i (if non-zero)

    XorBasis() { clear(); }

    // Clear the basis.
    void clear() { b.fill(0); }

    // Insert x into the basis. Returns true if x increased the rank (was independent).
    // Explanation: reduction top-down. If x reduces to 0, it was dependent.
    bool insert(u64 x) {
        for (int i = LOG - 1; i >= 0 && x; --i) {
            if (!((x >> i) & 1ULL)) continue;
            if (!b[i]) { b[i] = x; return true; }
            x ^= b[i];
        }
        return false;
    }

    // Check whether x can be represented as xor of a subset of inserted numbers.
    // Explanation: reduce x by existing pivots; if it reaches 0 -> representable.
    bool canRepresent(u64 x) const {
        for (int i = LOG - 1; i >= 0 && x; --i) {
            if (!((x >> i) & 1ULL)) continue;
            if (!b[i]) return false;
            x ^= b[i];
        }
        return x == 0;
    }

    // Maximize (x XOR s) over all s in the span of the basis and return the value.
    // Explanation: greedy try to flip high bits using available pivots.
    u64 getMax(u64 x) const {
        u64 res = x;
        for (int i = LOG - 1; i >= 0; --i) if (b[i]) {
            u64 cand = res ^ b[i];
            if (cand > res) res = cand;
        }
        return res;
    }

    // Maximum xor obtainable by xor-ing any subset of inserted numbers.
    // Explanation: start from 0 and greedily maximize.
    u64 getMaxSubset() const {
        u64 res = 0;
        for (int i = LOG - 1; i >= 0; --i) if (b[i]) {
            u64 cand = res ^ b[i];
            if (cand > res) res = cand;
        }
        return res;
    }

    // Merge another basis into this (in-place). Returns added rank.
    // Explanation: insert every pivot from 'other'.
    int merge(const XorBasis &other) {
        int added = 0;
        for (int i = 0; i < LOG; ++i) if (other.b[i]) added += insert(other.b[i]);
        return added;
    }

    // Return non-zero basis vectors (unsorted). Useful for iterating or saving.
    vector<u64> getBasis() const {
        vector<u64> res;
        for (int i = 0; i < LOG; ++i) if (b[i]) res.push_back(b[i]);
        return res;
    }

    // Number of basis vectors (rank).
    int rank() const {
        int r = 0;
        for (int i = 0; i < LOG; ++i) if (b[i]) ++r;
        return r;
    }

    // Number of distinct subset-xors = 2^rank. (fits in u64 since LOG<=64)
    u64 countDistinct() const {
        int r = rank();
        if (r >= 64) return 0; // practically never: means full 64 bits -> overflow; handle as needed
        return 1ULL << r;
    }

    // Convert basis to reduced row-echelon form: make each pivot bit unique
    // and clear that bit from all other rows. After this, b[i]'s pivot bit i is
    // set and no other b[j] has bit i set. This is helpful for certain queries
    // and for producing a clean list of independent vectors.
    void normalize() {
        for (int i = LOG - 1; i >= 0; --i) if (b[i]) {
            for (int j = 0; j < LOG; ++j) if (j != i && (b[j] >> i) & 1ULL) b[j] ^= b[i];
        }
    }
};

// Minimal usage example (asserts for correctness). Remove in contest if not needed.
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    XorBasis xb;
    vector<u64> a = {17ULL, 97ULL, 41ULL, 37ULL, 11ULL};
    for (auto v : a) xb.insert(v);

    // basic checks
    assert(xb.canRepresent(0) == true);
    // any inserted value should be representable (xor of single element or others)
    for (auto v : a) assert(xb.canRepresent(v));

    // getMaxSubset should be >= any single element
    u64 mx = xb.getMaxSubset();
    for (auto v : a) assert(mx >= v);

    // merging test
    XorBasis yb;
    yb.insert(5);
    int add = xb.merge(yb);
    (void)add; // silence unused in non-debug builds

    // finished
    return 0;
}
