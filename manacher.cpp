void Transform (char* str) {
    int k = 0;
    s[k++] = '$'; s[k++] = '#';
    for (int i = 0; str[i]; ++i) {
        s[k++] = str[i]; s[k++] = '#';
    }
    s[k] = 0;
}

int Manacher (char* str) {
    Transform();
    int mx = 0, id = 0, ans = 0;
    clr (p, 0);
    for (int i = 1; s[i]; ++i) {
        p[i] = mx > i ? min(p[2*id-i], mx-i) : 1;
        while (s[i+p[i]] == s[i-p[i]]) p[i]++; //以i为中心，p[i]为半径，查找是否还有可能构成回文的情况
        if (i + p[i] > mx) { // 更新最远的右边界
            mx = i+p[i];
            id = i;
        }
        ans = max(ans, p[i]-1);
    }
    return ans;
}

