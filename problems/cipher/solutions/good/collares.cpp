#include <iostream>
#include <vector>

using namespace std;

int main() {
    string s;
    int n;
    cin >> s >> n;

    vector<int> pi(s.size());
    for (int i = 0, cur = 0; i < n; i++) {
        int p = max(1, 2*n-2);
        for (int v = i, d = 2*i; v < s.size(); d = p-d ? p-d : d, v += d)
            pi[v] = cur++;
    }

    for (int i = 0; i < s.size(); i++)
        cout << s[pi[i]];
    cout << endl;
}
