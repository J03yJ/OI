#include<bits/stdc++.h>

using namespace std;

const int N=1.5e2+9;
const int V=1.5e2;
using ll=long long;

int a[N],n,m,c;
ll f[N][N][N],g[N][N],w[N][N];
template<class T1,class T2> inline void ChMin(T1 &x,T2 y){if(y<x) x=y;}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n>>m>>c;
    for(int i=1;i<=n;i++) cin>>a[i];
    
    memset(w,0x3f,sizeof w);
    for(int i=1,v,d,t;i<=m;i++){
        cin>>v>>d>>t;
        ChMin(w[d][t],v);
    }
    for(int i=n;i>=1;i--){
        for(int j=V;j>=1;j--) ChMin(w[i][j],min(w[i+1][j],w[i][j+1]));
    }

    memset(f,0x3f,sizeof f);
    for(int k=V;k>=1;k--){
        memset(g,0x3f,sizeof g);
        for(int i=1;i<=n;i++) f[k][i][i-1]=g[i][i-1]=0;
        for(int i=1;i<=n;i++){
            for(int j=i;j<=n;j++){
                g[i][j]=g[i][j-1]+1ll*max(a[j]-k,0)*c;
                for(int p=i;p<=j;p++) ChMin(g[i][j],g[i][p-1]+f[k+1][p][j]);
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=i;j<=n;j++){
                f[k][i][j]=f[k][i][j-1]+1ll*a[j]*c;
                for(int p=i;p<=j;p++){
                    ChMin(f[k][i][j],f[k][i][p-1]+min(f[k+1][p][j],w[j-p+1][k]+g[p][j]));
                }
            }
        }
    }

    cout<<f[1][1][n]<<endl;

    return 0;
}