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

// Determina se os segmentos [A, B] e [C, D] se tocam
bool seg_intersect(point a, point b, point c, point d)
{
	int d1, d2, d3, d4;
	d1 = ccw(c, a, d);
	d2 = ccw(c, b, d);
	d3 = ccw(a, c, b);
	d4 = ccw(a, d, b);
	if (d1 * d2 == -1 && d3 * d4 == -1)
		return true;
	if (d1 == 0 && between(c, a, d))
		return true;
	if (d2 == 0 && between(c, b, d))
		return true;
	if (d3 == 0 && between(a, c, b))
		return true;
	if (d4 == 0 && between(a, d, b))
		return true;
	return false;
}

/* Retorna a area com sinal de um poligono T. Se area > 0, T esta
 * listado na ordem CCW */
double signedArea(polygon T)
{
	double area = 0;
	int n = T.size();
	if (n < 3)
		return 0;
	for (size_t i = 0; i < n; i++)
	{
		area += cross(T[i], T[(i + 1) % n]);
	}
	return (area / 2.0);
}

/* Retorna a area de um poligono T. (pode ser concavo ou convexo) em
 * O(N)*/
double poly_area(polygon &T) { return fabs(signedArea(T)); }

/* Retorna a centroide de um poligono T em O(N)*/
point centroide(polygon T)
{
	int n = T.size();
	double sgnArea = signedArea(T);

	point c = point(0, 0);
	for (int i = 0; i < n; i++)
	{
		int k = (i + 1) % n;
		c = c + (T[i] + T[k]) * cross(T[i], T[k]);
	}
	c = c / (sgnArea * 6.0);
	return c;
}

/*Encontra o convex hull de um conjunto de pontos em O(NlogN)
pivot: Ponto base para a criacao do convex hull;
radial_lt(): Ordena os pontos em sentido anti-horario (ccw).
Input: Conjunto de pontos 2D;
Output: Conjunto de pontos do convex hull, no sentido anti-horario;

(1)Se for preciso manter pontos colineares na borda do convex hull,
essa
parte evita que eles sejam removidos;
*/

point pivot;
bool radial_lt(point a, point b)
{
	int R = ccw(pivot, a, b);
	if (R == 0) // sao colineares
		return dot((pivot - a), (pivot - a)) < dot((pivot - b), (pivot - b));
	else
		return (R == 1); // 1 se A esta a direita de (pivot->B)
}

vector<point> convexhull(vector<point> T, vector<point> &inside)
{
	// Se for necessario remover pontos duplicadados
	sort(T.begin(), T.end()); // ordena por x e por y
	T.resize(unique(T.begin(), T.end()) - T.begin());

	int tam = 0, n = T.size();
	vector<point> U; // convex hull

	// nesse caso, pivot = ponto com menor y, depois menor x
	int idx = 0;
	for (int i = 1; i < T.size(); i++)
	{
		if ((T[i].y < T[idx].y) || (T[i].y == T[idx].y && T[i].x < T[idx].x))
		{
			idx = i;
		}
	}

	pivot = T[idx];
	swap(T[0], T[idx]);
	sort(++T.begin(), T.end(), radial_lt);

	/*(1)*/ int k;
	for (k = n - 2; k >= 0 && ccw(T[0], T[n - 1], T[k]) == 0; k--)
		;
	reverse((k + 1) + T.begin(), T.end()); /*(1)*/

	// troque <= por < para manter pontos colineares na borda
	for (int i = 0; i < T.size(); i++)
	{
		while (tam > 1 && ccw(U[tam - 2], U[tam - 1], T[i]) < 0)
		{
			inside.push_back(U.back());
			U.pop_back();
			tam--;
		}
		U.push_back(T[i]);
		tam++;
	}
	return U;
}

/**
 * @brief Generate n random points such that no two coincide and no three lie on the same line.
 * Adapted from jngen.h library
 */
vector<point> pointsInGeneralPosition(
	int n,
	long long X1, long long Y1,
	long long X2, long long Y2)
{
	struct Line
	{
		long long A, B, C; // Ax + By + C = 0
		Line() {}
		Line(const point &p1, const point &p2)
		{
			A = p1.y - p2.y;
			B = p2.x - p1.x;
			C = -(p1.x * A + p1.y * B);

			assert(A != 0 || B != 0);

			long long g = __gcd(A, __gcd(B, C));
			A /= g;
			B /= g;
			C /= g;
			if (A < 0 || (A == 0 && B < 0))
			{
				A = -A;
				B = -B;
				C = -C;
			}
		}

		bool operator<(const Line &other) const
		{
			return std::tie(A, B, C) < std::tie(other.A, other.B, other.C);
		}
	};

	std::set<Line> lines;
	std::set<point> points;

	vector<point> res;

	while (static_cast<int>(res.size()) != n)
	{

		int x = rnd.next(X1, X2);
		int y = rnd.next(Y1, Y2);
		point p(x, y);

		if (points.count(p))
		{
			continue;
		}

		if (std::none_of(
				res.begin(),
				res.end(),
				[&lines, &p](const point &q)
				{
					return lines.count(Line(p, q));
				}))
		{
			points.insert(p);
			for (const auto &q : res)
			{
				lines.emplace(p, q);
			}
			res.push_back(p);
		}
	}
	return res;
}

void printPoints(vector<point> p, bool print_in_ccw, string text = "")
{
	if (text.size())
		cout << text << endl;
	
	cout << p.size() << endl;

	if (print_in_ccw == false)
		reverse(p.begin(), p.end());

	for (size_t i = 0; i < p.size(); i++)
		cout << p[i].x << " " << p[i].y << endl;
	
	if (text.size())
		cout << "...\n";
}

/**
 * @brief Choose a point inside the polygon to be the position of the camera.
 */
void printPointInConvexPoly(vector<point> ch, vector<point> points_inside, string label = "")
{
	point camera;
	if (points_inside.size() > 0)
	{
		int idx = rnd.next(0, (int)points_inside.size() - 1);
		camera = points_inside[idx];
	}
	else
	{
		camera = centroide(ch);
	}

	cout << camera.x << " " << camera.y << label << endl;
}

int main(int argc, char *argv[])
{
	int n, x, y;
	vector<point> p;

	registerGen(argc, argv, 1);

	n = atoi(argv[2]);
	int max_xy = atoi(argv[3]);
	string testcase_type = string(argv[4]);
	bool print_in_ccw = (string(argv[5]) == "ccw");

	p = pointsInGeneralPosition(n, -max_xy, -max_xy, max_xy, max_xy);

	vector<point> insideCH; // pontos que estão dentro do Convex Hull
	vector<point> CH = convexhull(p, insideCH);
	assert(CH.size() >= 3);

	if (testcase_type == "convex")
	{
		//printPoints(CH, "Polygon");
		printPoints(CH, print_in_ccw, "");
		printPointInConvexPoly(CH, insideCH, "");
	}
	else if (testcase_type == "concave")
	{
		assert(insideCH.size() > 0);
		// Criar a aresta CH.back(), inside.back(), CH.front()
		CH.push_back(insideCH.back());
		insideCH.pop_back();

		//printPoints(CH, "Polygon");
		printPoints(CH, print_in_ccw, "");
		printPointInConvexPoly(CH, insideCH, "");
	}
}
