#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e2+9;

int p[N],q[N],c[N],f[N][N][N],n,lim;
void ChMin(int &x,int y){if(y<x) x=y;}

signed main(){
    cin>>n>>lim;
    for(int i=1;i<=lim;i++) cin>>c[i];
    for(int i=1;i<=n;i++) cin>>p[i];
    for(int i=1;i<=n;i++) q[p[i]]=i;

    memset(f,0x3f,sizeof f);
    for(int i=1;i<=n;i++){
        f[lim+1][i][i]=0;
        for(int j=i+1;j<=n;j++){
            if(q[j]<q[j-1]) break ;
            f[lim+1][i][j]=0;
        }
    }
    for(int k=lim;k>=1;k--){
        for(int i=1;i<=n;i++){
            for(int j=i;j<=n;j++){
                f[k][i][j]=f[k+1][i][j];
                for(int p=i;p<j;p++){
                    ChMin(f[k][i][j],f[k+1][i][p]+f[k+1][p+1][j]+c[k]*(j-p));
                }
            }
        }
    }
    if(f[1][1][n]>1e18) cout<<-1<<endl;
    else cout<<f[1][1][n]<<endl;

    return 0;
}