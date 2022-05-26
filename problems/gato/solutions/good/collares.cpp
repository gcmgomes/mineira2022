#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    string n;
    int K;
    cin >> n >> K;

    vector<int> p(K);
    for (int i = 0; i < K; i++)
        cin >> p[i];

    int m[K];
    vector<int> nxt(n.size()+1, -1);
    nxt[n.size()] = n.size();

    for (int i = n.size()-1; i >= 0; i--) {
        memset(m, 0, sizeof m);

        for (int j = i; j < n.size(); j++) {
            bool good = false;
            for (int k = 0; k < K; k++) {
                m[k] = (10*m[k] + (n[j] - '0')) % p[k];
                if (m[k] == 0)
                    good = true;
            }

            if (good && nxt[j+1] != -1) {
                nxt[i] = j+1;
                break;
            }
        }
    }

    if (nxt[0] == -1) {
        cout << "-1" << endl;
        return 0;
    }

    int cur = 0, sz = 0;
    while (cur != n.size())
        sz++, cur = nxt[cur];
    cout << sz << endl;

    cur = 0;
    while (cur != n.size()) {
        if (cur)
            cout << " ";
        cout << n.substr(cur, nxt[cur] - cur);
        cur = nxt[cur];
    }
    cout << endl;
}
