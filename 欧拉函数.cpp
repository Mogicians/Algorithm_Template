ll euler_phi (ll n) {
	ll ans = n;
	for (ll i = 2; i*i <= n; ++i){
		if (n % i == 0) {
			ans = ans / i * (i - 1);
			while (n % i == 0) n /= i;
		}
	}
	if (n > 1) ans = ans / n * (n - 1);
	return ans;
}
