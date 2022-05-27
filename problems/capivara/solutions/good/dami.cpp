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

int L, C, K;
vector<int> mid;
int cor[3];

int solve2d(){
	if(K != (L*C-1)) return -1;
	return L*C - max(cor[0], max(cor[1], cor[2]));
}

int solve1d(int c, vector<int> v){
	int need = L*C - cor[c];
	bool pivoEhIgual = true;
	for(int i=v.size()-K-1; i<=K; i++)
		if(v[i] != c)
			pivoEhIgual = false;
	if(pivoEhIgual) need += 2;
	return need;
}

int main() {

	cin >> L >> C >> K;

	vector<vector<int> > m(L, vector<int>(C, 0));
	cor[0] = cor[1] = cor[2] = 0;

	for(int i=0; i<L; i++)
    for(int j=0; j<C; j++){
    	cin >> m[i][j];
    	cor[--m[i][j]]++;
	}

	if(L > 1 && C > 1){
		cout << solve2d() << "\n";
	}
	else{
		int len = max(L, C);
		int minimo = len/2;
		if(K < minimo || K >= len) cout << -1 << "\n";
		else{
			vector<int> v;
			if(C >= L) v = m[0];
			else for(int i=0; i<L; i++) v.push_back(m[i][0]);
			int ans = min(solve1d(0, v), min(solve1d(1, v), solve1d(2, v)));
			cout << ans << "\n";
		}
	}

	return 0;
}
