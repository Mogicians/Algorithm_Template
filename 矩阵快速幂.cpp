struct Matrix {
	ll mat[2][2];
};

Matrix unit = {
	1, 0,
	0, 1
};

Matrix K = {
	1, 1,
	1, 0
};

Matrix mul(Matrix a, Matrix b) {
	Matrix res;
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			res.mat[i][j] = 0;
			for (int k = 0; k < 2; ++k) {
				res.mat[i][j] += a.mat[i][k] * b.mat[k][j];
				res.mat[i][j] %= mod;
			}
		}
	}
	return res;
}

Matrix quickpow(Matrix a, int n) {
	Matrix res = unit;
	while(n) {
		if(n & 1) res = mul(res, a);
		a = mul(a, a);
		n >>= 1;
	}
	return res;
}