#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

int L, C, T;
char m[1001][1001];
bool vis[1001][1001];
int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};

bool dentro(int x, int y){
	return x >= 0 && y >= 0 && x < L && y < C;
}

int bfs(int a, int b){
	queue<pair<pair<int, int>, int> > q;
	int ans = 0;
	q.push({{a, b}, 0});
	while(!q.empty()){
		pair<pair<int, int>, int> f = q.front();
		q.pop();
		int x = f.first.first, y = f.first.second;
		int t = f.second;
		if(vis[x][y]) continue;
		vis[x][y] = true;
		ans++;
		for(int k=0; k<4; k++){
			int xx = x+dx[k];
			int yy = y+dy[k];
			if(dentro(xx, yy) && m[xx][yy] == '.' && t+1 <= T){
				q.push({{xx, yy}, t+1});
			}
		}
	}
	return ans;
}

int gcd(int a, int b) { if (a == 0) return b; else return gcd (b % a, a); }

int main(){

	int a, b, possible = 0;
	cin >> L >> C >> T >> a >> b;
	--a; --b;

	for(int i=0; i<L; i++)
	for(int j=0; j<C; j++){
		cin >> m[i][j];
		vis[i][j] = 0;
		if(m[i][j] == '.') possible++;
	}

	int reach = bfs(a, b);
	int g = gcd(reach, possible);

	cout << reach/g << " " << possible/g << endl;

	return 0;
}
