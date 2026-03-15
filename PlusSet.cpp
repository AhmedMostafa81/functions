template <size_t N>
struct PlusSet {
    static_assert(N>0, "N must be > 0");
    using u64 = uint64_t;
    static constexpr size_t B = 64, W = (N + B - 1) / B;
    u64 a[W];
    static inline constexpr u64 tail_mask() { return (N % B) ? ((1ULL << (N % B)) - 1) : ~0ULL; }

    PlusSet(){ reset(); }
    void reset(){ fill(a, a+W, 0); }
    void set_all(){ fill(a, a+W, ~0ULL); a[W-1] &= tail_mask(); }

    void set(size_t p, bool v = true){ size_t w = p>>6, b = p & 63; if(v) a[w] |= (1ULL<<b); else a[w] &= ~(1ULL<<b); }
    void flip(size_t p){ a[p>>6] ^= (1ULL << (p & 63)); a[W-1] &= tail_mask(); }
    void flip_all(){ for(size_t i=0;i<W;++i) a[i] = ~a[i]; a[W-1] &= tail_mask(); }

    bool test(size_t p) const { return (a[p>>6] >> (p & 63)) & 1; }
    bool any() const { for(size_t i=0;i<W;++i) if(a[i]) return true; return false; }
    bool none() const { return !any(); }
    size_t count() const { size_t s=0; for(size_t i=0;i<W;++i) s += __builtin_popcountll(a[i]); return s; }

    PlusSet& operator&=(const PlusSet& o){ for(size_t i=0;i<W;++i) a[i] &= o.a[i]; return *this; }
    PlusSet& operator|=(const PlusSet& o){ for(size_t i=0;i<W;++i) a[i] |= o.a[i]; return *this; }
    PlusSet& operator^=(const PlusSet& o){ for(size_t i=0;i<W;++i) a[i] ^= o.a[i]; return *this; }
    PlusSet operator~() const { PlusSet r = *this; for(size_t i=0;i<W;++i) r.a[i] = ~r.a[i]; r.a[W-1] &= tail_mask(); return r; }
    friend PlusSet operator&(PlusSet x,const PlusSet& y){ x &= y; return x; }
    friend PlusSet operator|(PlusSet x,const PlusSet& y){ x |= y; return x; }
    friend PlusSet operator^(PlusSet x,const PlusSet& y){ x ^= y; return x; }

    PlusSet& operator<<=(size_t s){
        if(s >= N){ reset(); return *this; }
        size_t big = s >> 6; unsigned rem = s & 63;
        if(rem == 0){
            for(size_t i = W; i-- > 0;) a[i] = (i >= big ? a[i-big] : 0);
        } else {
            for(size_t i = W; i-- > 0;){
                u64 v = 0;
                if(i >= big){
                    v = a[i-big] << rem;
                    if(i - big > 0) v |= (a[i-big-1] >> (64 - rem));
                }
                a[i] = v;
            }
        }
        a[W-1] &= tail_mask();
        return *this;
    }

    PlusSet& operator>>=(size_t s){
        if(s >= N){ reset(); return *this; }
        size_t big = s >> 6; unsigned rem = s & 63;
        if(rem == 0){
            for(size_t i=0;i<W;++i) a[i] = (i + big < W ? a[i + big] : 0);
        } else {
            for(size_t i=0;i<W;++i){
                u64 v = 0;
                if(i + big < W){
                    v = a[i + big] >> rem;
                    if(i + big + 1 < W) v |= (a[i + big + 1] << (64 - rem));
                }
                a[i] = v;
            }
        }
        return *this;
    }

    PlusSet operator<<(size_t k) const { PlusSet r = *this; r <<= k; return r; }
    PlusSet operator>>(size_t k) const { PlusSet r = *this; r >>= k; return r; }

    int find_first() const {
        for(size_t i=0;i<W;++i){
            u64 w = a[i];
            if(w){ int t = __builtin_ctzll(w); int pos = int(i*64 + t); return pos >= int(N) ? -1 : pos; }
        }
        return -1;
    }
    int find_next(int pos) const {
        if(pos + 1 >= int(N)) return -1;
        size_t i = (pos + 1) >> 6; unsigned b = (pos + 1) & 63;
        u64 w = a[i] & (~0ULL << b);
        if(w) return int(i*64 + __builtin_ctzll(w));
        for(size_t j = i+1; j < W; ++j) if(a[j]) return int(j*64 + __builtin_ctzll(a[j]));
        return -1;
    }
};
