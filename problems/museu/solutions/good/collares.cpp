#include <iostream>

using namespace std;

int px, py;
int x[100000], y[100000];

long long area(int x1, int y1, int x2, int y2) {
    return (long long)(x1-px)*(y2-py) - (long long)(y1-py)*(x2-px);
}

int main() {
    int n;
    cin >> n;
    
    for (int i = 0; i < n; i++)
        cin >> x[i] >> y[i];
    cin >> px >> py;
    
    long long a1 = 0, a2 = 0, a;
    bool ok = true;
        
    for (int i = 0; i < n; i++) {
        a = area(x[i], y[i], x[(i+1)%n], y[(i+1)%n]);
        if (a == 0)
            ok = false;
        a1 += a;
        a2 += a > 0 ? a : -a;
    }
             
    if (a1 < 0)
        a1 = -a1;
    cout << (ok && a1 == a2 ? "S" : "N") << endl;
}
