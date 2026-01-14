#include<bits/stdc++.h>

using namespace std;

const int N=5e5+9;
using ll=long long;

int fi[N],to[N<<1],ne[N<<1],w[N<<1],adj;
void AdEg(int x,int y,int z){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
    w[adj]=z;
}

int imp[N],fa[N],c[N],v[N],n,k;
void DFS(int x){
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        fa[y]=x,v[y]=w[i];
        DFS(y);
    }
}

ll ans[N],dep[N],deq[N];
void Find(int x,ll *dep,int fa=-1){
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa) continue ;
        if(!c[y]) continue ;
        dep[y]=dep[x]+w[i];
        Find(y,dep,x);
    }
}

void Solve(int x,ll res,int fa=-1){
    if(c[x]) res=ans[x];
    else ans[x]=res;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa) continue ;
        Solve(y,res+w[i],x);
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n>>k;
    for(int i=1,u,v,w;i<n;i++){
        cin>>u>>v>>w;
        AdEg(u,v,w);
        AdEg(v,u,w);
    }
    for(int i=1;i<=k;i++) cin>>imp[i];
    if(!k){
        for(int i=1;i<=n;i++) cout<<0<<endl;
        return 0;
    }

    ll sum=0;
    const int root=imp[1];
    DFS(root);
    c[root]=1;
    for(int i=1;i<=k;i++){
        int cur=imp[i];
        while(!c[cur]) c[cur]=1,sum+=v[cur],cur=fa[cur];
    }

    int p=0,q=0;
    Find(root,dep);
    for(int i=1;i<=n;i++) if(!p||dep[i]>dep[p]) p=i;
    for(int i=1;i<=n;i++) dep[i]=0;
    Find(p,dep);
    for(int i=1;i<=n;i++) if(!q||dep[i]>dep[q]) q=i;
    Find(q,deq);
    
    for(int i=1;i<=n;i++) if(c[i]) ans[i]=sum*2-max(dep[i],deq[i]);
    Solve(root,0);

    for(int i=1;i<=n;i++) cout<<ans[i]<<endl;

    return 0;
}