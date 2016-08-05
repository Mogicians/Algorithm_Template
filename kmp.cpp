void getNext (char* s, int len) {
    int i = 0, j;
    j = Next[0] = -1;
    while (i < len) {
        while (j != -1 && s[i] != s[j]) j = Next[j];
        Next[++i] = ++j;
    }
}
int kmp (char* s, char* t) {
    int i = 0, j = 0, ans = 0;
    int n = strlen(s), m = strlen(t);
    getNext (t, m);
    while (i < n) {
        while (j != -1 && s[i] != t[j]) j = Next[j];
        ++i; ++j;
        if (j >= m) {
            ans++;
            j = Next[j];
        }
    }
    return ans;
}
