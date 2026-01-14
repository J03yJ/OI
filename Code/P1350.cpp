#include<bits/stdc++.h>

using namespace std;

const int N=2e3+9;
const int mod=1e5+3;

int f[N][N],h[N],a,b,c,d,k;

int main(){
    cin>>a>>b>>c>>d>>k;
    for(int i=1;i<=c;i++) h[i]=d;
    for(int i=1;i<=a;i++) h[i+c]=b+d;
    f[0][0]=1;
    for(int i=1;i<=a+c;i++){
        f[i][0]=1;
        for(int j=1;j<=k;j++) f[i][j]=(f[i-1][j]+1ll*f[i-1][j-1]*(h[i]-j+1)%mod)%mod;
    }
    cout<<f[a+c][k]<<endl;

    return 0;
}