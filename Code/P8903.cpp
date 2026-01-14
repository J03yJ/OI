#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e3+9;

int f[N][N],g[N][N],a[N],b[N],c[N],w[N],p[N],alim,blim,n;

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n>>blim>>alim;
    for(int i=1;i<=n;i++) cin>>c[i]>>b[i]>>w[i];
    for(int i=1;i<=n;i++) a[i]=w[i]*b[i];

    iota(p+1,p+n+1,1);
    sort(p+1,p+n+1,[](int i,int j){return w[i]<w[j];});
    for(int i=1;i<=n;i++){
        copy(f[i-1],f[i-1]+alim+1,f[i]);
        for(int j=alim;j>=a[p[i]];j--) f[i][j]=max(f[i][j],f[i][j-a[p[i]]]+c[p[i]]);
        partial_sum(f[i],f[i]+alim+1,f[i],[](int x,int y){return max(x,y);});
    }
    for(int i=n;i>=1;i--){
        copy(g[i+1],g[i+1]+blim+1,g[i]);
        for(int j=blim;j>=b[p[i]];j--) g[i][j]=max(g[i][j],g[i][j-b[p[i]]]+c[p[i]]);
        partial_sum(g[i],g[i]+blim+1,g[i],[](int x,int y){return max(x,y);});
    }

    int ans=0;
    for(int i=1;i<=n;i++){
        ans=max(ans,f[i-1][alim]+g[i+1][blim]);
        for(int j=0;j<=min(b[p[i]],blim);j++){
            int k=(b[p[i]]-j)*w[p[i]];
            if(j>blim||k>alim) continue ;
            ans=max(ans,c[p[i]]+f[i-1][alim-k]+g[i+1][blim-j]);
        }
    }
    cout<<ans<<endl;

    return 0;
}