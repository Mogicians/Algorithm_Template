struct PAM {

    int next[N][26]; // next指针
    int fail[N]; // fail失配后缀链接
    int cnt[N];  // 该节点表示的回文串出现的次数
    int num[N];  // 该节点表示的回文串的最右端点为回文串结尾的回文串个数
    int len[N];  // 该节点回文串长度
    int s[N];    // 存放添加的字符
    int last;    // 指向新添加一个字母后所形成的最长回文串表示的节点
    int n;       // 已添加字符个数
    int p;       // 节点个数

    int newnode(int w) {
        memset(next[p], 0, sizeof(next[p]));
        cnt[p] = 0;
        num[p] = 0;
        len[p] = w;
        return p++;
    }

    void init() {
        p = 0;
        newnode(0); newnode(-1);
        n = last = 0;
        s[n] = -1;
        fail[0] = 1;
    }

    int getfail(int x) {
        while(s[n-len[x]-1] != s[n]) x = fail[x];
        return x;
    }

    void insert(int c) {
        c -= 'a'; s[++n] = c;
        int cur = getfail(last);
        if(!next[cur][c]) {
            int now = newnode(len[cur] + 2);
            fail[now] = next[getfail(fail[cur])][c];
            next[cur][c] = now;
            num[now] = num[fail[now]] + 1;
        }
        last = next[cur][c];
        cnt[last]++;
    }

    void count() {
        for(int i = p-1; i >= 2; --i)
            cnt[fail[i]] += cnt[i];
    }

} pam;
