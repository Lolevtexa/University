#include "search.h"

const int prime = 101;

bool rabinKarpSearch(const std::string& text, const std::string& pattern) {
    int m = pattern.size();
    int n = text.size();
    if (m > n) return false;

    long long patternHash = 0, textHash = 0, h = 1;
    
    for (int i = 0; i < m - 1; i++)
        h = (h * prime);

    for (int i = 0; i < m; i++) {
        patternHash = (prime * patternHash + pattern[i]);
        textHash = (prime * textHash + text[i]);
    }

    for (int i = 0; i <= n - m; i++) {
        if (patternHash == textHash) {
            int j;
            for (j = 0; j < m; j++) {
                if (text[i + j] != pattern[j])
                    break;
            }
            if (j == m)
                return true;
        }

        if (i < n - m) {
            textHash = (prime * (textHash - text[i] * h) + text[i + m]);
        }
    }
    
    return false;
}
