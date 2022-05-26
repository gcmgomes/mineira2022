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
vector<vector<int> > m(L, vector<int>(C, 0));
vector<int> mid;
int cor[3];

int solve2d(){
	if(K != (L*C-1)) return -1;
	return L*C - max(cor[0], max(cor[1], cor[2]));
}

int solve1d(int c){
	int need = L*C - cor[c];
	bool meioEhIgual = true;
	for(int i=0; i<mid.size(); i++){
		if(mid[i] != c) meioEhIgual = false;
	}
	if(meioEhIgual) need += 2;
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
			// 2 possiveis mids
			if(L >= C) {
				mid.push_back(m[(len-1)/2][0]);
				if(len%2 == 0) mid.push_back(m[len/2][0]);
			}
			else{
				mid.push_back(m[0][(len-1)/2]);
				if(len%2 == 0) mid.push_back(m[0][len/2]);
			}
			int ans = min(solve1d(0), min(solve1d(1), solve1d(2)));
			cout << ans << "\n";
		}
	}

	return 0;
}
