#include<bits/stdc++.h>

using namespace std;

#define fir(x) x.first
#define sec(x) x.second
const int N=2e5+9;
using ll=long long;
using pii=pair<int,int>;

int fa[N],n;
inline int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
inline void Merge(int x,int y){fa[Find(y)]=Find(x);}

queue<pii> q;
ll ans;
set<int> in[N],tin[N],out[N],tout[N],vert[N];
inline ll C(int x){return 1ll*x*(x-1);}
inline void Link(int x,int y){
    int tx=Find(x),ty=Find(y);
    if(tx==ty) return ;
    if(tout[ty].find(tx)==tout[ty].end()){
        if(in[ty].find(x)==in[ty].end()){
            ans+=vert[ty].size();
            out[x].insert(ty),in[ty].insert(x);
            tout[tx].insert(ty),tin[ty].insert(tx);
        }
        return ;
    }
    ans-=C(vert[tx].size()),ans-=C(vert[ty].size());
    tin[tx].erase(ty),tout[ty].erase(tx);
    if(vert[tx].size()<vert[ty].size()) swap(tx,ty),swap(x,y);
    Merge(tx,ty);
    for(int u:vert[ty]){
        for(int v:out[u]){
            ans-=vert[v].size();
            in[v].erase(u);
            q.push({u,v});
        }
        out[u].clear();
    }
    for(int u:in[ty]){
        ans-=vert[ty].size();
        out[u].erase(ty);
        q.push({u,ty});
    }
    in[ty].clear();
    for(int u:tin[ty]) tout[u].erase(ty);
    for(int u:tout[ty]) tin[u].erase(ty);
    ans+=1ll*in[tx].size()*vert[ty].size();
    vert[tx].insert(vert[ty].begin(),vert[ty].end());
    vert[ty].clear();
    ans+=C(vert[tx].size());
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'
    
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++) fa[i]=i,vert[i].insert(i);
    while(m--){
        int u,v;
        cin>>u>>v;
        q.push({u,v});
        while(q.size()) Link(fir(q.front()),sec(q.front())),q.pop();
        cout<<ans<<endl;
    }

    return 0;
}