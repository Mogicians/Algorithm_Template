/*************************************************************************
 * Miller-Rabin 素性测试
 *************************************************************************/
ll myrand() { return rand() * (ll)rand(); }

bool MillerRabin(ll n, int times = 20) { // times = 20
	ll k = 0, m, a, i, j;
	if (n < 2) return false;
	if (n == 2) return true;
	if (!(n & 1)) return false;
	for (m = n - 1; !(m & 1); m >>= 1, ++k);
	for (i = 0; i < times; ++i) {
		a = PowerMod(myrand() % (n - 2) + 2, m, n);
		if (a == 1) continue;
		for (j = 0; j < k && a != n - 1; ++j)
			a = ProductMod(a, a, n);
		if (j >= k) return false;
	}
	return true;
}
