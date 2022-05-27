#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

typedef long long int LL;

const double EPS = 1e-9;

inline int cmp(LL x, LL y = 0, LL tol = 0)
{
	return ((x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1);
}

struct point
{
	LL x, y;
	point(LL x = 0, LL y = 0) : x(x), y(y) {}
	point operator+(point q) { return point(x + q.x, y + q.y); }
	point operator-(point q) { return point(x - q.x, y - q.y); }
	point operator*(LL t) { return point(x * t, y * t); }
	point operator/(LL t) { return point(x / t, y / t); }
	int cmp(point q) const
	{
		if (int t = ::cmp(x, q.x))
			return t;
		return ::cmp(y, q.y);
	}
	bool operator==(point q) const { return cmp(q) == 0; };
	bool operator!=(point q) const { return cmp(q) != 0; };
	bool operator<(point q) const { return cmp(q) < 0; };
};
ostream &operator<<(ostream &os, const point &p)
{
	os << "(" << p.x << "," << p.y << ")";
	return os;
}
#define vec(a, b) (b - a)
typedef vector<point> polygon;

LL cross(point a, point b) { return a.x * b.y - a.y * b.x; }
LL dot(point a, point b) { return a.x * b.x + a.y * b.y; }
LL collinear(point a, point b, point c)
{
	return cmp(cross(b - a, c - a)) == 0;
}
// retorna 1 se R esta a esquerda do vetor P->Q, -1 se estiver a
// direita. 0 se P, Q e R forem colineares
int ccw(point p, point q, point r) { return cmp(cross(q - p, r - p)); }

//////////////////////////////////////////////////////////////////////
/////////////////////////  Segmentos, Retas  /////////////////////////
//////////////////////////////////////////////////////////////////////

// Determina se P esta entre o segmento fechado [A,B], inclusive
bool between(point p, point a, point b)
{
	return collinear(p, a, b) && dot(a - p, b - p) <= 0;
}



void printPoints(vector<point> p, bool print_in_ccw)
{
	cout << p.size() << endl;

	if (print_in_ccw == false)
		reverse(p.begin(), p.end());

	for (size_t i = 0; i < p.size(); i++)
		cout << p[i].x << " " << p[i].y << endl;
}


void quadrado(int len, vector<point> &p)
{
	int iter, x, y;
	
	iter = len;
	x = -len;
	y = len;
	while (iter--)
	{
		p.push_back(point(x,y));
		x++;
		p.push_back(point(x,y));
		x++;
	}
	y--;

	iter = len;
	while (iter--)
	{
		p.push_back(point(x,y));
		y--;
		p.push_back(point(x,y));
		y--;
	}
	x--;

	iter = len;
	while (iter--)
	{
		p.push_back(point(x,y));
		x--;
		p.push_back(point(x,y));
		x--;
	}
	y++;

	iter = len;
	while (iter--)
	{
		p.push_back(point(x,y));
		y++;
		p.push_back(point(x,y));
		y++;
	}
}

int main(int argc, char *argv[])
{
	registerGen(argc, argv, 1);

	int camera_x = atoi(argv[2]);
	int camera_y = atoi(argv[3]);
	bool print_ccw = (string(argv[4]) == "ccw");

	vector<point> p;
	quadrado(12500, p);

	printPoints(p, print_ccw);
	cout << camera_x << " " << camera_y << endl;
}
