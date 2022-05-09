#include <bits/stdc++.h>
#include "jngen.h"

using namespace std;

const double EPS = 1e-9;

inline int cmp(double x, double y = 0, double tol = EPS){
  return ((x <= y+tol) ? (x+tol < y) ? -1 : 0 : 1);
}

long long int cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }
long long int dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }
bool collinear(Point a, Point b, Point c)
{
	return cross(b - a, c - a) == 0;
}

// retorna 1 se R esta a esquerda do vetor P->Q, -1 se estiver a
// direita. 0 se P, Q e R forem colineares
int ccw(Point p, Point q, Point r)
{
	long long int ret = cross(q - p, r - p);
	if (ret < 0)
		ret = -1;
	if (ret > 0)
		ret = 1;
	return ret;
}

//////////////////////////////////////////////////////////////////////
/////////////////////////  Segmentos, Retas  /////////////////////////
//////////////////////////////////////////////////////////////////////

// Determina se P esta entre o segmento fechado [A,B], inclusive
bool between(Point p, Point a, Point b)
{
	return collinear(p, a, b) && dot(a - p, b - p) <= 0;
}

double arg(Point b, Point a, Point c)
{
	Point u = b - a, v = c - a;
	return atan2(cross(u, v), dot(u, v));
}

//	Determina se P pertence a T, funciona para convexo ou concavo
// -1 borda, 0 fora, 1 dentro. O(N)
int in_poly(Point p, vector<Point> &T)
{
	double a = 0;
	int N = T.size();
	for (size_t i = 0; i < N; i++)
	{
		if (between(p, T[i], T[(i + 1) % N]))
			return -1;
		a += arg(T[i], p, T[(i + 1) % N]);
	}
	return cmp(a) != 0;
}

void printPoints(vector<Point> &p, string text = "")
{
	if (text.size())
		cout << text << endl;

	cout << p.size() << endl;
	for (size_t i = 0; i < p.size(); i++)
		cout << p[i].x << " " << p[i].y << endl;
	if (text.size())
		cout << "...\n";
}

int main(int argc, char *argv[])
{
	parseArgs(argc, argv);

	int n = atoi(argv[2]);
	int max_xy = atoi(argv[3]);
	string testcase_type = string(argv[4]);

	vector<Point> poly = jngen::GeometryRandom::convexPolygon(n, -max_xy, max_xy);
	Point camera;

	if (testcase_type == "convex")
	{
		// generates the point of the camera
		do
		{
			camera = jngen::GeometryRandom::point(-max_xy, -max_xy, max_xy, max_xy);
		} while (in_poly(camera, poly) != 1);

		//printPoints(poly, "Polygon");
		printPoints(poly, "");
		cout << camera.x << " " << camera.y << endl;
	}
	else if (testcase_type == "concave")
	{
		// generates a random point
		Point p;
		do
		{
			p = jngen::GeometryRandom::point(-max_xy, -max_xy, max_xy, max_xy);
		} while (in_poly(p, poly) != 1);

		poly.push_back(p);

		// generates the point to be the camera
		do
		{
			camera = jngen::GeometryRandom::point(-max_xy, -max_xy, max_xy, max_xy);
		} while (in_poly(camera, poly) != 1);

		//printPoints(poly, "Polygon");
		printPoints(poly, "");
		cout << camera.x << " " << camera.y << endl;
	}

	Drawer d;
	for (auto p : poly)
		d.point( p );
	for (int i = 0; i < poly.size(); i++) {
		d.segment(poly[i], poly[(i+1)%poly.size()]);
	}
	
	d.setColor("red");
	d.point(camera);

	string filename = string(argv[1]) + ".svg";
    d.dumpSvg(filename);
}
