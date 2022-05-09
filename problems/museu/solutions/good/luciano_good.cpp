#include <bits/stdc++.h>

using namespace std;

const double EPS = 1e-9;

inline int cmp(int x, int y = 0)
{
    return ((x <= y) ? (x < y) ? -1 : 0 : 1);
}

struct point
{
    long long int x, y;
    point(int x = 0, int y = 0) : x(x), y(y) {}
    point operator+(point q) { return point(x + q.x, y + q.y); }
    point operator-(point q) { return point(x - q.x, y - q.y); }
    int cmp(point q) const
    {
        if (int t = (x == q.x))
            return t;
        return (y == q.y);
    }
    bool operator==(point q) const { return cmp(q) == 0; };
    bool operator!=(point q) const { return cmp(q) != 0; };
    bool operator<(point q) const { return cmp(q) < 0; };
};

ostream &operator<<(ostream &os, const point &p)
{
    os << "(" << p.x << ", " << p.y << ")";
}

long long int cross(point a, point b) { return a.x * b.y - a.y * b.x; }
long long int dot(point a, point b) { return a.x * b.x + a.y * b.y; }
long long int collinear(point a, point b, point c) { return (cross(b - a, c - a)) == 0; }

// retorna 1 se R esta a esquerda do vetor P->Q, -1 se estiver a
// direita. 0 se P, Q e R forem colineares
int ccw(point p, point q, point r) { return cmp(cross(q - p, r - p)); }


/******************
 * SOLUTION
 *****************/

int N;
vector<point> P;
point C;

void solve(){
    for (size_t i = 0; i < P.size(); i++)
    {
        int ret = ccw(C, P[i], P[(i + 1)%P.size()]);
        if (ret <= 0)
        {
            cout << "N\n";
            return;
        }
    }

    cout << "S\n";
    return;
}

int main()
{
    cin >> N;
    P.resize(N);

    // polygon
    for(int i = 0; i < N; i++) {
        cin >> P[i].x >> P[i].y;
    }

    // camera
    cin >> C.x >> C.y;

    solve();

    return 0;
}