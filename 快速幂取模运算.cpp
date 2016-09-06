/*******************************
 * (a ^ b) mod c
 *******************************/

ll PowerMod(ll a, ll b, ll c) {
	a %= c;
	ll r = 1;
	for (; b; a = a * a % c, b >>= 1)
		if (b & 1) r = r * a % c;
	return r % c;
}

// 当乘法取模可能会爆int64时，手写乘法取模以避免溢出
ll PowerMod(ll a, ll b, ll c) {
	a %= c;
	ll r = 1;
	for (; b; a = ProductMod(a, a, c), b >>= 1)
		if (b & 1) r = ProductMod(r, a, c);
	return r % c;
}