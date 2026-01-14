#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=2e5+9;

int fi[N],ne[N<<1],to[N<<1],adj;
void AdEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

int f[N],ff[N],n,mod;
void DFS(int x,int fa){
    f[x]=1;
    vector<int> son;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa) continue ;
        DFS(y,x);
        f[x]=f[x]*(f[y]+1)%mod;
        son.push_back(y);
    }
    vector<int> pre(son.size()),suc(son.size());
    for(int i=0;i<son.size();i++){
        pre[i]=(i?pre[i-1]:1)*(f[son[i]]+1)%mod;
    }
    for(int i=son.size()-1;~i;i--){
        suc[i]=(i!=son.size()-1?suc[i+1]:1)*(f[son[i]]+1)%mod;
    }
    for(int i=0;i<son.size();i++){
        ff[son[i]]=(i?pre[i-1]:1)*(i!=son.size()-1?suc[i+1]:1)%mod;
    }
}
int ans[N];
void Solve(int x,int fa){
    ff[x]++;
    ans[x]=f[x]*ff[x]%mod;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa) continue;
        ff[y]=ff[y]*ff[x]%mod;
        Solve(y,x);
    }
}

signed main(){
    cin>>n>>mod;
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;
        AdEg(u,v),AdEg(v,u);
    }

    DFS(1,-1);
    Solve(1,-1);
    for(int i=1;i<=n;i++) cout<<ans[i]<<endl;

    return 0;
}