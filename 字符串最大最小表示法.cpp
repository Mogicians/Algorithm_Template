int MinMaxRep (char* s, int l, bool type) { // type = 1 : 最小表示
    int i = 0, j = 1, k = 0;
    while (i < l && j < l) {
        k = 0;
        while (s[(i + k) % l] == s[(j + k) % l] && k < l) k++;
        if (k == l) break;
        if (type ? s[(i + k) % l] > s[(j + k) % l] : s[(i + k) % l] < s[(j + k) % l]) i = max(i + k, j) + 1;
        else j = max(j + k, i) + 1;
    }
    return min(i, j) + 1;
}