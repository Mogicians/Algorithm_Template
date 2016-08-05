int s[N], sg[N];
bool hs[N];

void getSG(int* s, int len, int N) {
    memset(sg, 0, sizeof(sg));
    for (int i = 0; i < N; ++i) {
        memset(hs, 0, sizeof(hs));
        for (int j = 0; j < len; ++j) {
            if (i - s[j] < 0) continue;
            hs[sg[i - s[j]]] = 1;
        }
        for (int j = 0; j <= i; ++j) 
            if (!hs[j]) {
                sg[i] = j; 
                break;
            }
    }
}