
class Solution {
public:
    string longestPalindrome(string s) {
        string res = "";

        for (int i = 0; i < s.size(); i++) {
            for (int j = 0; j < 2; j++) {
                int l = i, r = i + j;

                while (l >= 0 && r < s.size() && s[l] == s[r]) {
                    if (r - l + 1 > res.size())
                        res = s.substr(l, r - l + 1);
                    l--;
                    r++;
                }
            }
        }
        return res;
    }
};
