#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=1e5+9;
const int lgV=6e1;

int fi[N],ne[N<<1],to[N<<1],adj;
ll w[N<<1];
inline void AddEdge(int x,int y,ll z){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
    w[adj]=z;
}

ll b[lgV];
inline void Insert(ll k){
    for(int i=lgV-1;~i&&k;i--){
        if(~k>>i&1) continue ;
        if(!b[i]){
            b[i]=k;
            break ;
        }else k^=b[i];
    }
}
inline ll Query(ll x){
    for(int i=lgV-1;~i;i--) x=max(x,x^b[i]);
    return x;
}

ll dep[N];
int fa[N],dfn[N],n,m,dcnt;
inline void DFS(int x){
    dfn[x]=++dcnt;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        if(!dfn[y]){
            fa[y]=x;
            dep[y]=dep[x]^w[i];
            DFS(y);
        }else if(dfn[y]<dfn[x]) Insert(dep[y]^dep[x]^w[i]);
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;ll w;
        cin>>u>>v>>w;
        AddEdge(u,v,w);
        AddEdge(v,u,w);
    }

    DFS(1);

    cout<<Query(dep[1]^dep[n])<<endl;

    return 0;
}