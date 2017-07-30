#include <bits/stdc++.h>

using namespace std;

vector<int> kmp(string &str) {
    vector<int> fail;
    fail.push_back(0);
    int pos = 0;
    for (int i = 1; i < str.length(); i++) {
        fail.push_back(pos);
        while (pos > 0 && str[i] != str[pos])
            pos = fail[pos];
        if (str[i] == str[pos])
            pos += 1;
    }
    fail.push_back(pos);
    return fail;
}

int main() {
    for (;;) {
        string str;
        cin >> str;
        if (str == ".") break;
        int len = str.length();
        vector<int> fail = kmp(str);
        int cnt = fail.back();
        int left = len - cnt;
        int ans = 1;
        if (len % left == 0) ans = len / left;
        cout << ans << "\n";
    }
}
