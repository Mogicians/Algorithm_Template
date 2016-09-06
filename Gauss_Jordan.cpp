/*************************************************************************
 * 列主元.高斯约旦消元法 解方程组
 *************************************************************************/
// A为增广矩阵, {A[i][n]/A[i][i]}为解集
// 返回是否有唯一解
bool Gauss_Jordan(double A[][MAX_N], int n) {
	bool uniq = true;
	 for (int i = 0; i < n; ++i) {
	 	int r = i;
	 	for (int j = i + 1; j < n; ++j)
	 		if (fabs(A[j][i]) > fabs(A[r][i])) r = j;
	 	if (fabs(A[r][i]) < EPS) { uniq = false; continue; }
	 	if (r != i) for (int j = 0; j <= n; ++j) swap(A[r][j], A[i][j]);
	 	for (int k = 0; k < n; ++k) if (k != i)
	 		for (int j = n; j >= i; --j) A[k][j] -= A[k][i] / A[i][i] * A[i][j];
	 }
	return uniq;
}