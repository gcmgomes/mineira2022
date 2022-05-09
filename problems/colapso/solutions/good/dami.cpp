#include <bits/stdc++.h>

using namespace std;

int N, M, K, Q;
int m[401][401];
int s[401][401];
const int INF = 1e9+10;

int getSquareSum(int i, int j){
    int ret = s[i][j];
    int esq = j-K, cima = i-K;
    if(esq >= 0) ret -= s[i][esq];
    if(cima >= 0) ret -= s[cima][j];
    if(esq >= 0 && cima >= 0) ret += s[cima][esq];
    return ret;
}

void buildPrefixSum(int t){

    memset(s, 0, sizeof(s));

    s[0][0] = (m[0][0] <= t);
    for(int i=1; i<N; i++) s[i][0] = s[i-1][0] + (m[i][0] <= t);
    for(int i=1; i<M; i++) s[0][i] = s[0][i-1] + (m[0][i] <= t);

    for(int i=1; i<N; i++)
    for(int j=1; j<M; j++)
        s[i][j] = (m[i][j] <= t) + s[i][j-1] + s[i-1][j] - s[i-1][j-1];
    
}

bool solve(int t){
    buildPrefixSum(t);
    for(int i=K-1; i<N; i++)
    for(int j=K-1; j<M; j++){
        int sum = getSquareSum(i, j);
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
