
const int MAX_N = 10010;  
  
struct BigInteger {  
    int len, s[MAX_N];  
    BigInteger () {  
        memset(s, 0, sizeof(s));  
        len = 1;  
    }  
    BigInteger (int num) { *this = num; }  
    BigInteger (const char* num) { *this = num; }  
    BigInteger operator = (const int num) {  
        char s[MAX_N];  
        sprintf(s, "%d", num);  
        *this = s;  
        return *this;  
    }  
    BigInteger operator = (const char* num) {  
    	if (strlen(num) > 1)
        	for(int i = 0; num[i] == '0'; num++); 
        len = strlen(num);
        for(int i = 0; i < len; i++) s[i] = num[len-i-1] - '0';  
        return *this;  
    }  
    BigInteger operator + (const BigInteger &b) const {  
        BigInteger c;  c.len = 0;  
        for(int i = 0, g = 0; g || i < max(len, b.len); i++) {
            int x = g;  
            if(i < len) x += s[i];  
            if(i < b.len) x += b.s[i];  
            c.s[c.len++] = x % 10;  
            g = x / 10;  
        }  
        return c;  
    }  
    BigInteger operator += (const BigInteger &b) {  
        *this = *this + b;  
        return *this;  
    }  
    void clean() {  
        while(len > 1 && !s[len-1]) len--;
    }  
    BigInteger operator * (const BigInteger &b) {  
        BigInteger c;  c.len = len + b.len;  
        for(int i = 0; i < len; i++)   
            for(int j = 0; j < b.len; j++)   
                c.s[i+j] += s[i] * b.s[j];  
        for(int i = 0; i < c.len; i++) {  
            c.s[i+1] += c.s[i]/10;  
            c.s[i] %= 10;  
        }  
        c.clean();  
        return c;  
    }  
    BigInteger operator *= (const BigInteger &b) {  
        *this = *this * b;  
        return *this;  
    }  
    BigInteger operator - (const BigInteger &b) {  
        BigInteger c;  
        c.len = 0;  
        for(int i = 0, g = 0; i < len; i++) {  
            int x = s[i] - g;  
            if(i < b.len) x -= b.s[i];  
            if(x >= 0) g = 0;  
            else {  
                g = 1;  
                x += 10;  
            }  
            c.s[c.len++] = x;  
        }  
        c.clean();  
        return c;  
    }  
    BigInteger operator -= (const BigInteger &b) {  
        *this = *this - b;  
        return *this;  
    }  
    BigInteger operator / (const BigInteger &b) {  
        BigInteger c, f = 0;  
        for(int i = len-1; i >= 0; i--) {  
            f = f*10;  
            f.s[0] = s[i];  
            while(f >= b) {  
                f -= b;  
                c.s[i]++;  
            }  
        }  
        c.len = len;  
        c.clean();  
        return c;  
    }  
    BigInteger operator /= (const BigInteger &b) {  
        *this  = *this / b;  
        return *this;  
    }  
    BigInteger operator % (const BigInteger &b) {  
        BigInteger r = *this / b;  
        r = *this - r*b;  
        return r;  
    }  
    BigInteger operator %= (const BigInteger &b) {  
        *this = *this % b;  
        return *this;  
    }  
    bool operator < (const BigInteger &b) {  
        if(len != b.len) return len < b.len;  
        for(int i = len-1; i >= 0; i--)  
            if(s[i] != b.s[i]) return s[i] < b.s[i];  
        return false;  
    }  
    bool operator > (const BigInteger &b) {  
        if(len != b.len) return len > b.len;  
        for(int i = len-1; i >= 0; i--)  
            if(s[i] != b.s[i]) return s[i] > b.s[i];
        return false;  
    }  
    bool operator == (const BigInteger &b) {  
        return !(*this > b) && !(*this < b);  
    }  
    bool operator != (const BigInteger &b) {  
        return !(*this == b);  
    }  
    bool operator <= (const BigInteger &b) {  
        return *this < b || *this == b;  
    }  
    bool operator >= (const BigInteger &b) {  
        return *this > b || *this == b;  
    }  
    string str() const {  
        string res = "";  
        for(int i = 0; i < len; i++) res = char(s[i] + '0') + res;  
        return res;  
    }  
};  
  
istream& operator >> (istream &in, BigInteger &x) {  
    string s;  
    in >> s;  
    x = s.c_str();  
    return in;  
}  
  
ostream& operator << (ostream &out, const BigInteger &x) {  
    out << x.str();  
    return out;  
}  

