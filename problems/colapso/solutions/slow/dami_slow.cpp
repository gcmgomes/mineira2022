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

int N, M, K, Q;
int m[401][401];
const int INF = 1e9+10;

int getSquareSum(int i, int j, int t){
    int ret = 0;
    int jj = j-K+1, ii = i-K+1;
    for(int a = ii; a <= i; a++)
    for(int b = jj; b <= j; b++)
       ret += (m[a][b] <= t);
    return ret;
}

bool solve(int t){
    for(int i=K-1; i<N; i++)
    for(int j=K-1; j<M; j++){
        int sum = getSquareSum(i, j, t);
        if(sum == K*K) return true;
    }
    return false;
}

int main(){

    cin >> N >> M >> K >> Q;

    for(int i=0; i<N; i++)
    for(int j=0; j<M; j++)
    m[i][j] = INF;

    for(int i=0; i<Q; i++){
        int A, B, D;
        cin >> A >> B >> D;
        --A; --B;
        m[A][B] = D;
    }

    int ini = 1, fim = 1e9;
    int ret = INF;

    while(ini <= fim){
        int mid = (ini+fim)/2;
        bool colapsed = solve(mid);
        if(colapsed) ret = mid, fim = mid-1;
        else ini = mid+1;
    }

    if(ret == INF) ret = -1;
    cout << ret << "\n";

    return 0;
}
