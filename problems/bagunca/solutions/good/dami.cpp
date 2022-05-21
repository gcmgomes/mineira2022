#include <iostream>
#include <string>

using namespace std;

int m[501][501];
int L, C;
int dx[] = {0, -1, -1, -1, 0, 1, 1, 1};
int dy[] = {-1, -1, 0, 1, 1, 1, 0, -1};

bool dentro(int x, int y){
    return x>=0 && y>=0 && x<L && y<C;
}

int contaVizinhos(int x, int y){
    int ret = 0;
    for(int k=0; k<8; k++){
        ret += dentro(x+dx[k], y+dy[k]);
    }
    return ret;
}

void distribui(int x, int y, int brinquedos){
    for(int k=0; k<8; k++){
        if(dentro(x+dx[k], y+dy[k])){
            m[x+dx[k]][y+dy[k]] += brinquedos;
        }
    }
}

pair<int, int> proximoAzulejo(int x, int y){
    int ma = -1;
    int a, b;
    for(int k=0; k<8; k++){
        int xx = x+dx[k], yy = y+dy[k];
        if(dentro(xx, yy) && m[xx][yy] > ma){
            ma = m[xx][yy];
            a = xx, b = yy;
        }
    }
    return {a, b};
}

int solve(int x, int y){
    int t = 0;
    while(t < L+C){
        int vizinhos = contaVizinhos(x, y);
        if(!vizinhos) break;
        int brinquedosDistribuir = m[x][y]/vizinhos;
        distribui(x, y, brinquedosDistribuir);
        m[x][y] -= (brinquedosDistribuir*vizinhos);
        pair<int, int> next = proximoAzulejo(x, y);
        x = next.first, y = next.second;
        t++;
    }

    int ret = 0;

    for(int i=0; i<L; i++)
    for(int j=0; j<C; j++)
    ret = max(ret, m[i][j]);
    
    return ret;
}

int main(){

    int A, B;

    cin >> L >> C;

    for(int i=0; i<L; i++)
    for(int j=0; j<C; j++)
    cin >> m[i][j];

    cin >> A >> B; --A; --B;

    cout << solve(A, B) << endl;

    return 0;
}