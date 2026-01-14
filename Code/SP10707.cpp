#include<bits/stdc++.h>
using namespace std;

const int N=2e5+9;
int fi[N],ne[N<<1],to[N<<1],adj;
void adeg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

vector<int> Eul;
int st[N],ed[N];
int fa[N][21],dep[N];
void dfs(int x){
    st[x]=Eul.size();
    Eul.push_back(x);
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(dep[y]) continue ;
        fa[y][0]=x;
        dep[y]=dep[x]+1;
        dfs(y);
    }
    ed[x]=Eul.size();
    Eul.push_back(x);
}
void Init(int n){
    for(int k=1;k<20;k++){
        for(int i=1;i<=n;i++){
            fa[i][k]=fa[fa[i][k-1]][k-1];
        }
    }
}
int Lca(int x,int y){
    if(dep[x]<dep[y]) swap(x,y);
    for(int k=19;~k;k--){
        if(dep[fa[x][k]]>=dep[y]) x=fa[x][k];
    }
    if(x==y) return x;
    for(int k=19;~k;k--){
        if(fa[x][k]!=fa[y][k]) x=fa[x][k],y=fa[x][k];
    }
    return fa[x][0];
}

map<int,int> mp;
int a[N],blk[N];

struct Q{
    int l,r,u,v,id;
    bool operator <(Q x){
        if(blk[l]!=blk[x.l]) return blk[l]<blk[x.l];
        else return r<x.r;
    }
}q[N];

int c[N];bool vis[N];
void Modify(int &ans,int x){
    int k=a[x];
    if(vis[x]){
        vis[x]=0;
        c[k]--;
        if(!c[k]) ans--/*,cout<<"~"<<k<<endl*/;
    }else{
        vis[x]=1;
        if(!c[k]) ans++/*,cout<<"+"<<k<<endl*/;
        c[k]++;
    }
}
int res[N];

int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1,cnt=0;i<=n;i++){
        int x;
        cin>>x;
        if(!mp[x]) mp[x]=++cnt;
        a[i]=mp[x];
    }

    for(int i=1;i<n;i++){
        int x,y;
        cin>>x>>y;
        adeg(x,y);
        adeg(y,x);
    }

    // fa[1][0]=-1;
    dep[1]=1;
    dfs(1);
    Init(n);
    int B=sqrt(m);
    for(int i=1;i<=(n<<1);i++) blk[i]=(i-1)/B+1;

    // for(int i=0;i<Eul.size();i++) cout<<Eul[i]<<'/'<<a[Eul[i]]<<' ';cout<<endl;

    for(int i=1;i<=m;i++){
        cin>>q[i].u>>q[i].v;
        if(st[q[i].u]>st[q[i].v]) swap(q[i].u,q[i].v);
        if(ed[q[i].u]<ed[q[i].v]) q[i].l=ed[q[i].u],q[i].r=st[q[i].v];
        else q[i].l=st[q[i].u],q[i].r=st[q[i].v];
        q[i].id=i;
    }
    sort(q+1,q+m+1);

    for(int i=1,ans=0,l=0,r=-1;i<=m;i++){
        // cout<<q[i].l<<' '<<q[i].r<<' '<<q[i].u<<' '<<q[i].v<<' '<<q[i].id<<endl;

        while(l>q[i].l) Modify(ans,Eul[--l]);
        while(r<q[i].r) Modify(ans,Eul[++r]);
        while(l<q[i].l) Modify(ans,Eul[l++]);
        while(r>q[i].r) Modify(ans,Eul[r--]);

        int Lc=Lca(q[i].u,q[i].v);

        // cout<<Lc<<endl;

        if(Lc!=q[i].u&&Lc!=q[i].v) Modify(ans,Lc);
        res[q[i].id]=ans;
        if(Lc!=q[i].u&&Lc!=q[i].v) Modify(ans,Lc);
    }

    for(int i=1;i<=m;i++) cout<<res[i]<<endl;

    return 0;
}