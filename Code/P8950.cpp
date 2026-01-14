#include<bits/stdc++.h>

using namespace std;

#define int long long
#define ssiz(x) (signed)x.size()
const int N=2e5+9;
const int K=21;
const int mod=998244353;
const int inf=1e18;

int fi[N],ne[N],to[N],w[N],adj,n,m,k;
void AdEg(int x,int y,int z){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
    w[adj]=z;
}
int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}
#define Inv(x) QPow(x,mod-2)

namespace SCC{
    int dfn[N],low[N],ins[N],bel[N],siz[N],dcnt,scnt;
    vector<int> stk;
    void Tj(int x){
        dfn[x]=low[x]=++dcnt;
        ins[x]=1;
        stk.push_back(x);
        for(int i=fi[x];i;i=ne[i]){
            int y=to[i];
            if(!dfn[y]){
                Tj(y);
                low[x]=min(low[x],low[y]);
            }else if(ins[y]) low[x]=min(low[x],dfn[y]);
        }
        if(low[x]==dfn[x]){
            scnt++;
            while(ssiz(stk)){
                int p=stk.back();
                stk.pop_back();
                ins[p]=0;
                bel[p]=scnt;
                siz[scnt]++;
                if(p==x) break ;
            }
        }
    }
    int ind[N];
    bool IfNG(){
        for(int i=1;i<=n;i++) if(!dfn[i]) Tj(i);
        for(int x=1;x<=n;x++){
            for(int i=fi[x];i;i=ne[i]){
                int y=to[i];
                if(bel[x]==bel[y]) continue ;
                ind[bel[y]]++;
            }
        }
        int tmp=0;
        for(int i=1;i<=scnt;i++) if(!ind[i]) tmp=max(tmp,n-siz[i]+1);
        return k<tmp;
    }
}
namespace Brute{
    int d[K][K];
    void Floyd(){
        for(int x=1;x<=n;x++){
            for(int y=1;y<=n;y++){
                if(x!=y) d[x][y]=inf;
            }
        }
        for(int x=1;x<=n;x++){
            for(int i=fi[x];i;i=ne[i]){
                int y=to[i];
                d[x][y]=min(d[x][y],w[i]);
            }
        }
        for(int k=1;k<=n;k++){
            for(int i=1;i<=n;i++){
                for(int j=1;j<=n;j++){
                    d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
                }
            }
        }
    }
    int a[N],nxt[1<<K],val[1<<K];
    int Solve(){
        int cnt=0,res=0;
        for(int sta=1;sta<(1<<n)-1;sta++){
            for(int i=0;i<n;i++) a[i+1]=inf;
            for(int i=0;i<n;i++){
                if((sta>>i)&1){
                    for(int j=1;j<=n;j++) a[j]=min(a[j],d[i+1][j]);
                }
            }
            int pos=n+1,mn=inf;
            for(int i=0;i<n;i++){
                if((sta>>i)&1) continue ;
                if(a[i+1]<mn) mn=a[i+1],pos=i+1;
            }
            nxt[sta]=pos;
            val[sta]=mn;
            // cout<<sta<<" : "<<pos<<endl;
        }
        for(int sta=0;sta<(1<<n);sta++){
            if(__builtin_popcount(sta)!=k) continue ;
            int sum=0,tta=sta;
            while(tta!=(1<<n)-1){
                // cout<<sta<<" : "<<tta<<' '<<val[tta]<<' '<<nxt[tta]<<endl;
                sum=(sum+val[tta])%mod;
                tta|=1<<(nxt[tta]-1);
            }
            cnt++,res=(res+sum)%mod;
        }
        // cout<<res<<' '<<cnt<<endl;
        return res*Inv(cnt)%mod;
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'
    
    cin>>n>>m>>k;
    for(int i=1,u,v,w;i<=m;i++){
        cin>>u>>v>>w;
        AdEg(v,u,w);
    }
    if(k==n){
        cout<<0<<endl;
        return 0;
    }
    if(SCC::IfNG()){
        cout<<-1<<endl;
        return 0;
    }
    Brute::Floyd();
    cout<<Brute::Solve()<<endl;

    return 0;
}