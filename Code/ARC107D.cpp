#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=4e3+9;
const int mod=998244353;

int f[N][N],n,k;

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n>>k;

    f[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=i;j>=1;j--){
            f[i][j]=f[i-1][j-1]+f[i][j*2];
            if(f[i][j]>mod) f[i][j]-=mod;
        }
    }
    
    cout<<f[n][k]<<endl;
    
    return 0;
}