#include <bits/stdc++.h>
using namespace std;

int n, vet[100005];
long long int dp[100005][2];

long long int solve(int p, int mod){

    if(p >= n) return 0;
    if(dp[p][mod]) return dp[p][mod];

    long long int p1 = 0;
    if(!mod) p1 = solve(p+1, 1) + vet[p];
    long long int p2 = solve(p+1, 0);

    return dp[p][mod] = max(p1, p2);
}

int main(){
    cin >> n;

    for(int i = 0 ; i < n ; i++){
        cin >> vet[i];
    }

    cout << solve(0, 0) << "\n";
}
