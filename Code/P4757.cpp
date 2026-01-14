#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=1e3+9;
const int M=1e6+9;
const int lgN=1e1;
const int K=1e1+9;
const int S=(1<<10)+9;
template<class S,class T> inline void ChMax(S &x,T y){if(y>x) x=y;}
template<class S,class T> inline void ChMin(S &x,T y){if(y<x) x=y;}

int fi[N],ne[N<<1],to[N<<1],adj;
inline void AddEdge(int x,int y){
	ne[++adj]=fi[x];
	fi[x]=adj;
	to[adj]=y;
}

int fa[N][lgN],dep[N],n;
inline void DFS(int x){
	for(int k=1;k<lgN;k++) fa[x][k]=fa[fa[x][k-1]][k-1];
	for(int i=fi[x];i;i=ne[i]){
		int y=to[i];
		if(y==fa[x][0]) continue ;
		fa[y][0]=x;
		dep[y]=dep[x]+1;
		DFS(y);
	}
}

inline int LCA(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int k=lgN-1;~k;k--) if(dep[fa[x][k]]>=dep[y]) x=fa[x][k];
	if(x==y) return x;
	for(int k=lgN-1;~k;k--) if(fa[x][k]!=fa[y][k]) x=fa[x][k],y=fa[y][k];
	return fa[x][0];
}
inline int Approx(int x,int y){
	for(int k=lgN-1;~k;k--) if(dep[fa[x][k]]>dep[y]) x=fa[x][k];
	return x;	
}

int u[M],v[M],m;
vector<int> qry[N],sub[N];
int f[N],id[N],son[N][K],ban[N][N],w[N][K][K],g[N][S];
inline void Work(int x){
	int c=0;
	for(int i=fi[x];i;i=ne[i]){
		int y=to[i];
		if(y==fa[x][0]) continue ;
		Work(y);
		id[y]=++c;
		son[x][c]=y;
	}

	for(int i=1;i<=c;i++){
		for(int j=i+1;j<=c;j++){
			w[x][i][j]=f[son[x][i]]+f[son[x][j]];
		}
		w[x][0][i]=f[son[x][i]];
	}
	for(int i:qry[x]){
		int p=Approx(u[i],x),q=Approx(v[i],x);
		if(p==x) ChMax(w[x][0][id[q]],ban[q][v[i]]+1);
		else if(q==x) ChMax(w[x][0][id[p]],ban[p][u[i]]+1);
		else{
			if(id[p]>id[q]) swap(p,q),swap(u[i],v[i]);
			ChMax(w[x][id[p]][id[q]],ban[p][u[i]]+ban[q][v[i]]+1);
		}
	}

	for(int sta=0;sta<(1<<c);sta++){
		for(int i=1;i<=c;i++){
			if(sta>>i-1&1) continue ;
			ChMax(g[x][sta|1<<i-1],g[x][sta]+w[x][0][i]);
			for(int j=i+1;j<=c;j++){
				if(sta>>j-1&1) continue ;
				ChMax(g[x][sta|1<<i-1|1<<j-1],g[x][sta]+w[x][i][j]);
			}
		}
	}

	ban[x][x]=f[x]=g[x][(1<<c)-1];
	for(int i=1;i<=c;i++){
		int y=son[x][i];
		for(int z:sub[y]){
			sub[x].push_back(z);
			ban[x][z]=ban[y][z]+g[x][((1<<c)-1)^(1<<i-1)];
		}
	}
	sub[x].push_back(x);

	for(int i=0;i<=c;i++){
		son[x][i]=0;
		for(int j=0;j<=c;j++) w[x][i][j]=0;
	}
	for(int sta=0;sta<(1<<c);sta++) g[x][sta]=0;
}

inline void Clear(){
	for(int i=1;i<=n;i++){
		id[i]=f[i]=fi[i]=0;
		for(int j:sub[i]) ban[i][j]=0;
		sub[i].clear();
		qry[i].clear();
	}
	adj=0;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	int T;
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1,u,v;i<n;i++){
			cin>>u>>v;
			AddEdge(u,v);
			AddEdge(v,u);
		}
		dep[1]=1;
		DFS(1);

		cin>>m;
		for(int i=1;i<=m;i++){
			cin>>u[i]>>v[i];
			qry[LCA(u[i],v[i])].push_back(i);
		}

		Work(1);
		cout<<f[1]<<endl;

		Clear();
	}

	return 0;
}