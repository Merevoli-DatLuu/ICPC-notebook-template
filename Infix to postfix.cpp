int GetPriority(char c) {
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    if (c == '(') return 0;
}
string infix_postfix(string s) {
    string res = "";
    stack < char > st;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == ' ') {
            continue;
        }
        if (s[i] == '(') {
            st.push(s[i]);
            continue;
        }
        if (s[i] == ')') {
            while (!st.empty() && st.top() != '(') {
                res = res + st.top() + " ";
                st.pop();
            }
            st.pop();
            continue;
        }
        if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
            while (!st.empty() && GetPriority(st.top()) >= GetPriority(s[i])) {
                res = res + st.top() + " ";
                st.pop();
            }
            st.push(s[i]);
            continue;
        }
        if ('0' <= s[i] && s[i] <= '9') {
            while ('0' <= s[i] && s[i] <= '9') {
                res += s[i];
                i++;
            }
            i--;
            res += " ";
            continue;
        }
    }
    while (!st.empty()) {
        res = res + st.top() + " ";
        st.pop();
    }
    return res;
}
int calc_postfix(string s) {
    stack < int > st;
    for (int i = 0; i < s.size(); i++) {
        int x = 0;
        if (s[i] == ' ') continue;
        if ('0' <= s[i] && s[i] <= '9') {
            while ('0' <= s[i] && s[i] <= '9') {
                x = x * 10 + (s[i] - '0');
                i++;
            }
            i--;
        } else if (s[i] == '+') {
            x = st.top();
            st.pop();
            x += st.top();
            st.pop();
        } else if (s[i] == '-') {
            x = st.top();
            st.pop();
            x -= st.top();
            st.pop();
        } else if (s[i] == '*') {
            x = st.top();
            st.pop();
            x *= st.top();
            st.pop();
        } else if (s[i] == '/') {
            x = st.top();
            st.pop();
            x /= st.top();
            st.pop();
        }
        st.push(x);
    }
    return st.top();
}