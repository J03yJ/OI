#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;
const int inf=1e9;

int fi[N],ne[N<<1],to[N<<1],adj;
void AdEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

int f[N][2],fa[N],dfn[N],low[N],dcnt,n,m;
void Work(int x,int y){
    int g[2],lst[2];
    g[0]=g[1]=lst[0]=lst[1]=0;
    for(int z=y;z!=x;z=fa[z]){
        g[0]=f[z][0]+lst[0],g[1]=f[z][1]+lst[1];
        lst[0]=max(g[0],g[1]),lst[1]=g[0];
    }
    f[x][0]+=lst[0];

    g[0]=g[1]=lst[0]=0,lst[1]=-inf;
    for(int z=y;z!=x;z=fa[z]){
        g[0]=f[z][0]+lst[0],g[1]=f[z][1]+lst[1];
        lst[0]=max(g[0],g[1]),lst[1]=g[0];
    }
    f[x][1]+=lst[1];
}
void Tj(int x){
    dfn[x]=low[x]=++dcnt;
    f[x][1]=1,f[x][0]=0;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        if(!dfn[y]){
            fa[y]=x;
            Tj(y);
            low[x]=min(low[x],low[y]);
        }else low[x]=min(low[x],dfn[y]);
        if(low[x]>dfn[x]) f[x][0]+=max(f[y][0],f[y][1]),f[x][1]+=f[y][0];
    }
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(fa[y]==x) continue ;
        if(dfn[y]<dfn[x]) continue ;
        Work(x,y);
    }
}

int main(){
    cin>>n>>m;
    for(int i=1,u,v;i<=m;i++){
        cin>>u>>v;
        AdEg(u,v);
        AdEg(v,u);
    }

    Tj(1);
    cout<<max(f[1][0],f[1][1])<<endl;

    return 0;
}