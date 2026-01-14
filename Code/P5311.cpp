#include<bits/stdc++.h>

using namespace std;

#define allc(x) x.begin(),x.end()
const int N=1e5+9;

int fi[N],ne[N<<1],to[N<<1],adj;
void AdEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

int a[N],ans[N],ql[N],qr[N],qx[N],n,m;
vector<int> q[N];

int siz[N],vis[N],root;
void DFS1(int x,int tot,int fa,vector<int> &v){
    int flag=1;
    siz[x]=1,v.push_back(x);
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(vis[y]) continue ;
        if(y==fa) continue ;
        DFS1(y,tot,x,v);
        siz[x]+=siz[y];
        if(siz[y]>(tot>>1)) flag=0;
    }
    if(tot-siz[x]>(tot>>1)) flag=0;
    if(flag) root=x;
}
int mx[N],mn[N];
void DFS2(int x,int fa){
    siz[x]=1;
    mx[x]=max(mx[x],x),mn[x]=min(mn[x],x);
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(vis[y]) continue ;
        if(y==fa) continue ;
        mx[y]=mx[x],mn[y]=mn[x];
        DFS2(y,x);
        siz[x]+=siz[y];
    }
}
int tr[N],pos[N];
void Add(int x,int k){
    while(x<=n){
        tr[x]+=k;
        x+=x&-x;
    }
}
int Ask(int x){
    int sum=0;
    while(x){
        sum+=tr[x];
        x&=x-1;
    }
    return sum;
}
int Ask(int l,int r){return Ask(r)-Ask(l-1);}
void Solve(int x,int tot){
    vector<int> son;
    DFS1(x,tot,-1,son);
    x=root,vis[x]=1;

    for(int u:son) mx[u]=0,mn[u]=n+1;
    DFS2(x,-1);
    vector<array<int,3>> pr;
    for(int u:son){
        vector<int> tmp;
        for(int i:q[u]){
            if(ql[i]<=mn[u]&&mx[u]<=qr[i]) pr.push_back({qr[i],i,1});
            else tmp.push_back(i);
        }
        q[u]=tmp;
    }
    for(int u:son) pr.push_back({mx[u],u,0});
    sort(allc(pr),[](auto x,auto y){return x[0]^y[0]?x[0]<y[0]:x[2]<y[2];});
    vector<pair<int,int>> rb;
    for(auto t:pr){
        if(t[2]){
            ans[t[1]]=Ask(ql[t[1]],n);
        }else{
            if(mn[t[1]]>pos[a[t[1]]]){
                if(pos[a[t[1]]]){
                    Add(pos[a[t[1]]],-1);
                    rb.push_back({pos[a[t[1]]],-1});
                }
                pos[a[t[1]]]=mn[t[1]];
                Add(mn[t[1]],1);
                rb.push_back({mn[t[1]],1});
            }
        }
    }
    for(auto t:pr) pos[a[t[1]]]=0;
    for(auto p:rb) Add(p.first,-p.second);

    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(vis[y]) continue ;
        Solve(y,siz[y]);
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1,u,v;i<n;i++) cin>>u>>v,AdEg(u,v),AdEg(v,u);
    for(int i=1;i<=m;i++) cin>>ql[i]>>qr[i]>>qx[i],q[qx[i]].push_back(i);
    
    Solve(1,n);
    for(int i=1;i<=m;i++) cout<<ans[i]<<endl;

    return 0;
}