#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;
const int p=998244353;

namespace tr{
    int fi[N],ne[N<<1],to[N<<1],adj=1;
    void adeg(int x,int y){
        ne[++adj]=fi[x];
        fi[x]=adj;
        to[adj]=y;
    }

    int dep[N],fa[N],siz[N],hson[N];
    void dfs1(int x){
        siz[x]=1;
        for(int i=fi[x];i;i=ne[i]){
            int y=to[i];
            if(y==fa[x]) continue ;
            dep[y]=dep[x]+1;
            fa[y]=x;
            dfs1(y);
            siz[x]+=siz[y];
            if(siz[y]>siz[hson[x]]) hson[x]=y;
        }
    }
    int top[N],dfn[N],dcnt;
    void dfs2(int x,int t){
        top[x]=t;
        dfn[x]=++dcnt;
        if(hson[x]) dfs2(hson[x],t);
        else return ;
        for(int i=fi[x];i;i=ne[i]){
            int y=to[i];
            if(y==fa[x]) continue ;
            if(y==hson[x]) continue ;
            dfs2(y,y);
        }
    }
    int lca(int x,int y){
        while(top[x]!=top[y]){
            if(dep[top[x]]<dep[top[y]]) swap(x,y);
            x=fa[top[x]];
        }
        if(dep[x]>dep[y]) swap(x,y);
        return x;
    }
}

int a[N],n;
vector<int> c[N];

namespace vtr{
    int fi[N],ne[N<<2],to[N<<2],adj=1;
    void adeg(int x,int y){
        ne[++adj]=fi[x];
        fi[x]=adj;
        to[adj]=y;
    }

    bool imp[N];
    bool cmp(int x,int y){
        return tr::dfn[x]<tr::dfn[y];
    }
    vector<int> node;
    int build(vector<int> a){
        int n=a.size();
        sort(a.begin(),a.end(),cmp);
        for(int x:a) imp[x]=1;
        for(int i=1;i<n;i++) a.push_back(tr::lca(a[i-1],a[i]));
        sort(a.begin(),a.end(),cmp);
        n=unique(a.begin(),a.end())-a.begin();
        for(int i=1;i<n;i++) adeg(tr::lca(a[i-1],a[i]),a[i]);
        for(int i=0;i<n;i++) node.push_back(a[i]);
        return a[0];
    }
    long long f[N],ans;
    void dfs(int x,int col){
        f[x]=1;
        for(int i=fi[x];i;i=ne[i]){
            int y=to[i];
            if(tr::dfn[y]<tr::dfn[x]) continue ;
            dfs(y,col);
            f[x]=f[x]*(f[y]+1)%p;
        }
        if(a[x]!=col){
            f[x]=(f[x]+p-1)%p;
            long long res=f[x];
            for(int i=fi[x];i;i=ne[i]){
                int y=to[i];
                if(tr::dfn[y]<tr::dfn[x]) continue ;
                res=(res+p-f[y])%p;
            }
            ans=(ans+res)%p;
        }else ans=(ans+f[x])%p;
    }
    void clear(){
        for(int x:node) imp[x]=0,fi[x]=0,f[x]=0;
        node.clear();
        adj=1;
        ans=0;
    }
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i],c[a[i]].push_back(i);
    for(int i=1;i<n;i++){
        int x,y;
        cin>>x>>y;
        tr::adeg(x,y);
        tr::adeg(y,x);
    }

    tr::fa[1]=1;
    tr::dfs1(1);
    tr::dfs2(1,1);

    long long res=0;
    for(int i=1;i<=n;i++){
        if(!c[i].size()) continue ;
        vtr::dfs(vtr::build(c[i]),i);
        res=(res+vtr::ans)%p;
        vtr::clear();
    }
    cout<<res<<endl;

    return 0;
}