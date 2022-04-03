#include <iostream>
#include <string>

using namespace std;

int n, m;
int dx[8] = {0, -1, -1, -1, 0, 1, 1, 1};
int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int a[1001][1001];

bool dentro (int x, int y){
    return (x>=0 and y>=0 and x<n and y<m);
}

int getValidNeighbors(int x, int y){
    int neighbors = 0;
    for(int i=0; i<8; i++){
        int nx = x + dx[i];
        int ny = y + dy[i];       
        neighbors += dentro(nx, ny);
    }
    return neighbors;
}

pair<int, int> play(int x, int y){
    
    int neighbors = getValidNeighbors(x, y);
    int toNeighbors = a[x][y]/neighbors;
    a[x][y] = a[x][y]%neighbors;
    int maior = 0;
    pair<int, int> next;
    
    for(int i=0; i<8; i++){
        
        int nx = x + dx[i];
        int ny = y + dy[i];
        
        if(!dentro(nx, ny)) continue;
        
        a[nx][ny] += toNeighbors;
        
        if(a[nx][ny] > maior){
            next = {nx, ny};
            maior = a[nx][ny];
        }
    }
    
    return next;
}

int main()
{
  int pn, pm, t, maior = 0;
  
  cin >> n >> m;
  t = n+m;
  
  for(int i=0; i<n; i++)
    for(int j=0; j<m; j++) 
        cin >> a[i][j];

  cin >> pn >> pm;
  
  while(t--){
    pair<int, int> nextPosition = play(pn, pm);
    pn = nextPosition.first;
    pm = nextPosition.second;
  }
  
  for(int i=0; i<n; i++)
    for(int j=0; j<m; j++) 
        maior = max(maior, a[i][j]);       
        
  cout << maior << endl;
        
}
