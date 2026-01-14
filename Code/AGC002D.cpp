#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;
const int lgN=2e1;

int fi[N<<1],ne[N<<1],to[N<<1],adj=1;
void AdEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

int rt[N<<1],id[N<<1],n,m,q;
void InitFa(int lim){
    for(int i=1;i<=lim;i++) rt[i]=i;
}
int Find(int x){
    if(rt[x]==x) return x;
    else return rt[x]=Find(rt[x]);
}
void Merge(int x,int y){
    rt[Find(y)]=Find(x);
}

int fa[N][lgN],siz[N];
void DFS(int x){
    siz[x]=!fi[x];
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        fa[y][0]=x;
        DFS(y);
        siz[x]+=siz[y];
    }
}
int Root(int x,int time){
    for(int k=lgN-1;~k;k--) if(id[fa[x][k]]<=time) x=fa[x][k];
    return x;
}

int main(){
    cin>>n>>m;
    InitFa(n<<1);
    for(int i=1,u,v,cnt=n;i<=m;i++){
        cin>>u>>v;
        if(Find(u)==Find(v)) continue ;
        id[++cnt]=i;
        AdEg(cnt,Find(u));
        AdEg(cnt,Find(v));
        Merge(cnt,u);
        Merge(cnt,v);
    }

    int root=(n<<1)-1;
    fa[root][0]=root;
    DFS(root);
    for(int k=1;k<lgN;k++){
        for(int i=1;i<=root;i++) fa[i][k]=fa[fa[i][k-1]][k-1];
    }

    cin>>q;
    while(q--){
        int x,y,k;
        cin>>x>>y>>k;
        int l=-1,r=m+1;
        while(l+1<r){
            int mid=l+r>>1;
            int u=Root(x,mid),v=Root(y,mid);
            int res=siz[u]+siz[v];
            if(u==v) res-=siz[v];
            if(res>=k) r=mid;
            else l=mid;
        }
        cout<<r<<endl;
    }

    return 0;
}