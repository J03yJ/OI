#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;

struct Graph{
    int fi[N],ne[N<<1],to[N<<1],adj;
    void AdEg(int x,int y){
        ne[++adj]=fi[x];
        fi[x]=adj;
        to[adj]=y;
    }
    int dep[N],fa[N];
    void DFS(int x){
        for(int i=fi[x];i;i=ne[i]){
            int y=to[i];
            if(y==fa[x]) continue ;
            fa[y]=x;
            dep[y]=dep[x]+1;
            DFS(y);
        }
    }
}r,b;
bool Check(int x,int y){
    if(b.dep[x]<b.dep[y]) swap(x,y);
    if(b.dep[x]==b.dep[y]) return b.fa[x]==b.fa[y];
    else if(b.dep[x]==b.dep[y]+1) return b.fa[x]==y;
    else if(b.dep[x]==b.dep[y]+2) return b.fa[b.fa[x]]==y;
    else return 0;
}
int ned[N],err,mxdep;
void Solve(int x){
    if(r.dep[x]>=b.dep[x]) return ;
    mxdep=max(mxdep,b.dep[x]);
    if(ned[x]) err=1;
    for(int i=r.fi[x];i;i=r.ne[i]){
        int y=r.to[i];
        if(y==r.fa[x]) continue ;
        Solve(y);
    }
}

int n,x,y;

int main(){
    cin>>n>>x>>y;
    for(int i=1,u,v;i<n;i++) cin>>u>>v,r.AdEg(u,v),r.AdEg(v,u);
    for(int i=1,u,v;i<n;i++) cin>>u>>v,b.AdEg(u,v),b.AdEg(v,u);

    r.DFS(x);
    b.DFS(y);
    for(int i=1;i<=n;i++){
        if(r.fa[i]&&!Check(r.fa[i],i)) ned[i]=ned[r.fa[i]]=1;
    }
    Solve(x);

    if(err) cout<<-1<<endl;
    else cout<<mxdep*2<<endl;

    return 0;
}