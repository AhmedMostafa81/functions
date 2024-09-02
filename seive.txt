vector<bool> isPrime(1e6 + 1, true);
void sieve() {
    isPrime[1] = 0;
    for (int p = 2; p * p <= 1e6; ++p) {
        if (isPrime[p]) {
            for (int i = p * p; i <= 1e6; i += p) {
                isPrime[i] = false;
            }
        }
    }
}    

