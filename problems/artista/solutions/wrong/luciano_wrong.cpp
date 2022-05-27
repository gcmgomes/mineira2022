#include <bits/stdc++.h>

using namespace std;

long long N, v[100005];
long long dp[100005];

int main(){
    
    cin >> N;
    for(int i=0; i<N; i++) cin >> v[i];
    
    dp[0] = v[0];
    dp[1] = v[1];

    for (int i = 2; i < N; i++){
        dp[i] = max(v[i] + dp[i-2], dp[i-1]);
    }

    cout << dp[N - 1] << endl;
    
    return 0;
}
