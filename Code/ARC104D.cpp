#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=1e2+9;
const int V=1e6+9;

int f[N][V],ans[N],n,k,mod;
inline void AddAs(int &x,int y){if((x+=y)>=mod) x-=mod;}
inline void SubAs(int &x,int y){if((x-=y)<0) x+=mod;}
inline int Mul(int x,int y){return 1ll*x*y%mod;}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n>>k>>mod;
    
    int lim=n*n*k;
    f[0][0]=1;
    for(int i=1,tmp=0;i<=n;i++){
        tmp+=k+1;
        memcpy(f[i],f[i-1],4*(lim+1));
        for(int j=i;j<=lim;j++) AddAs(f[i][j],f[i][j-i]);
        for(int j=lim;j>=tmp;j--) SubAs(f[i][j],f[i][j-tmp]);
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<=lim;j++) AddAs(ans[i],Mul(k+1,Mul(f[i-1][j],f[n-i][j])));
        SubAs(ans[i],1);
        cout<<ans[i]<<endl;
    }

    return 0;
}