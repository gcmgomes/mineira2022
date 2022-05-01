#include <bits/stdc++.h>

using namespace std;

int N, v[100005];
long long dp[100005];

long long solve(int i){
    if(i >= N) return 0;
    if(dp[i] != -1) return dp[i];
    return dp[i] = max(v[i] + solve(i+2), solve(i+1));
}

int main(){
    
    cin >> N;
    for(int i=0; i<N; i++) cin >> v[i];
    
    memset(dp, -1, sizeof(dp));
    
    cout << solve(0) << "\n";
    
    return 0;
}
