#include<bits/stdc++.h>

using namespace std;

const int mod=1e9+7;
const int N=5e3+9;

int f[N][N];

int main(){
    int n,m;
    cin>>n;
    string s;
    cin>>s;
    m=s.size();

    f[0][0]=1;
    for(int i=0;i<n;i++){
        for(int j=0;j<=n;j++){
            f[i+1][j+1]=(f[i+1][j+1]+f[i][j])%mod;
            if(j) f[i+1][j-1]=(f[i+1][j-1]+f[i][j]*2%mod)%mod;
            else f[i+1][0]=(f[i+1][0]+f[i][0])%mod;
        }
    }
    cout<<f[n][m]<<endl;

    return 0;
}