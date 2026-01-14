#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=2e5+9;
const int mod=998244353;

inline void AddAs(int &x,int y){if((x+=y)>=mod) x-=mod;}
inline void SubAs(int &x,int y){if((x-=y)<0) x+=mod;}
inline void MulAs(int &x,int y){x=1ll*x*y%mod;}
inline int Add(int x,int y){if((x+=y)>=mod) x-=mod;return x;}
inline int Sub(int x,int y){if((x-=y)<0) x+=mod;return x;}
inline int Mul(int x,int y){return 1ll*x*y%mod;}
inline int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) MulAs(res,x);
        MulAs(x,x);
        y>>=1;
    }
    return res;
}
inline int Inv(int x){return QPow(x,mod-2);}

int fac[N],ifac[N];
inline void InitFact(int lim){
    fac[0]=1;
    for(int i=1;i<=lim;i++) fac[i]=Mul(fac[i-1],i);
    ifac[lim]=Inv(fac[lim]);
    for(int i=lim-1;~i;i--) ifac[i]=Mul(ifac[i+1],i+1);
}
inline int C(int n,int m){
    if(m<0||m>n) return 0;
    else return Mul(fac[n],Mul(ifac[m],ifac[n-m]));
}

vector<int> e[N];
vector<array<int,2>> edge[N];
int d[N],fa[N],dep[N],siz[N],dfn[N],idfn[N],n,dcnt;
inline int DFS(int x,int up,int f){
    siz[x]=1;
    dfn[x]=++dcnt;
	idfn[dcnt]=x;
    if(d[x]!=2){
        if(up) edge[n-(dep[x]-dep[up]+1)].push_back({x,up});
    }
    int mx=0,smx=0,u=0;
    auto Insert=[&](int x){
        if(x>mx) smx=exchange(mx,x);
        else if(x>smx) smx=x;
    };
    for(int y:e[x]){
        if(y==fa[x]) continue ;
        fa[y]=x;
        dep[y]=dep[x]+1;
        int v=DFS(y,d[x]!=2?x:up,d[x]!=2?f:y);
        edge[dfn[y]+siz[y]-(dep[v]-dep[x]+1)].push_back({x+n,v});
        u|=v;
        siz[x]+=siz[y];
        Insert(dfn[y]+siz[y]-1);
    }
	int tmp=0;
    if(dfn[x]>1) tmp=max(tmp,dfn[x]-1);
    if(dfn[x]+siz[x]<=n) tmp=max(tmp,dfn[x]+siz[x]);
	Insert(tmp);
    edge[smx].push_back({x,x+n});
    if(up){
        int k=n-siz[x]-(dep[x]-dep[up]);
        edge[k<dfn[x]?k:siz[x]+k].push_back({x+n,up});
    }
    return d[x]!=2?x:u;
}

int f[N<<1],vsiz[N<<1],ans[N],cur;
inline void InitDSU(){
    cur=1;
    for(int i=1;i<=(n<<1);i++) f[i]=i,vsiz[i]=(i>n);
}
inline int Find(int x){return f[x]==x?x:f[x]=Find(f[x]);}
inline void Merge(int x,int y){
    x=Find(x),y=Find(y);
    if(x==y) return ;
    f[y]=x;
    MulAs(cur,Mul(ifac[vsiz[x]],ifac[vsiz[y]]));
    vsiz[x]+=vsiz[y];
    MulAs(cur,fac[vsiz[x]]);
}
inline void Del(int x){
	x=Find(x);
	MulAs(cur,Mul(ifac[vsiz[x]],fac[vsiz[x]-1]));
	vsiz[x]--;
}

inline void Solve(){
    cin>>n;
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
        d[u]++,d[v]++;
    }

    int root=min_element(d+1,d+n+1)-d;
    DFS(root,0,0);

	InitDSU();
    InitFact(n);
	for(int i=n;i>=1;i--){
		ans[i]=Mul(C(n,i),cur);
		for(auto p:edge[i]) Merge(p[0],p[1]);
		Del(idfn[i]+n);
	}

	for(int i=1;i<=n;i++) cout<<ans[i]<<' ';cout<<endl;

	dcnt=0;
	for(int i=0;i<=n+1;i++){
		d[i]=fa[i]=0;
		e[i].clear();
		edge[i].clear();
	}
}

signed main(){
    cin.tie(0),cout.tie(0);
    ios::sync_with_stdio(0);

    int T;
    cin>>T;
    while(T--) Solve();

    return 0;
}