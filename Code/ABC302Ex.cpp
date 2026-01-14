#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;

int fi[N],ne[N<<1],to[N<<1],adj;
void AdEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

int a[N],b[N],fa[N],vcnt[N],ecnt[N],n;
int Find(int x){
    if(fa[x]==x) return x;
    else return Find(fa[x]);
}
void Merge(int x,int y,int &res,vector<array<int,4>> &rb){
    x=Find(x),y=Find(y);
    rb.push_back({x,fa[x],vcnt[x],ecnt[x]});
    rb.push_back({y,fa[y],vcnt[y],ecnt[y]});
    if(x==y){
        res-=min(ecnt[x],vcnt[x]);
        ecnt[x]++;
        res+=min(ecnt[x],vcnt[x]);
    }else{
        res-=min(ecnt[x],vcnt[x]);
        res-=min(ecnt[y],vcnt[y]);
        if(vcnt[x]<vcnt[y]) swap(x,y);
        fa[y]=x;
        vcnt[x]+=vcnt[y];
        ecnt[x]+=ecnt[y];
        ecnt[x]++;
        res+=min(ecnt[x],vcnt[x]);
    }
}
void RollBack(vector<array<int,4>> &rb){
    while(rb.size()){
        auto t=rb.back();
        fa[t[0]]=t[1];
        vcnt[t[0]]=t[2];
        ecnt[t[0]]=t[3];
        rb.pop_back();
    }
}
int ans[N],res;
void DFS(int x,int f){
    vector<array<int,4>> rb;
    int tmp=res;
    // cout<<x<<" : "<<endl;
    for(int i=1;i<=n;i++){
        // cout<<i<<" : "<<fa[i]<<' '<<vcnt[i]<<' '<<ecnt[i]<<endl;
    }
    Merge(a[x],b[x],res,rb);
    ans[x]=res;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==f) continue ;
        DFS(y,x);
    }
    RollBack(rb);
    res=tmp;
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i]>>b[i],vcnt[i]=1;
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;
        AdEg(u,v),AdEg(v,u);
    }

    iota(fa+1,fa+n+1,1);
    DFS(1,-1);
    for(int i=2;i<=n;i++) cout<<ans[i]<<' ';cout<<endl;

    return 0;
}