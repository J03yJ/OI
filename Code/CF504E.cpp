#include<bits/stdc++.h>

using namespace std;

const int N=1e6+9;
const int lgN=2e1;

#define endl '\n'
using ll=long long;
const int mod=998244353;
const int base=127;

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
#define Inv(x) QPow(x,mod-2)

int fi[N],ne[N<<1],to[N<<1],adj;
inline void AddEdge(int x,int y){
	ne[++adj]=fi[x];
	fi[x]=adj;
	to[adj]=y;
}

char a[N];
int fa[N],dep[N],elr[N<<1],pos[N<<1],lg[N<<1],ecnt,n,q;
int pre[N],suf[N],mn[N<<1][lgN+1],bpw[N],ibpw[N];
int siz[N],hson[N],top[N],dfn[N],idfn[N],dcnt;
inline void DFS(int x){
	elr[++ecnt]=x;
	pos[x]=ecnt;
	siz[x]=1;
	for(int i=fi[x];i;i=ne[i]){
		int y=to[i];
		if(y==fa[x]) continue ;
		fa[y]=x;
		dep[y]=dep[x]+1;
		pre[y]=Add(Mul(pre[x],bpw[1]),a[y]);
		suf[y]=Add(Mul(a[y],bpw[dep[y]]),suf[x]);
		DFS(y);
		elr[++ecnt]=x;
		siz[x]+=siz[y];
		if(!hson[x]||siz[y]>siz[hson[x]]) hson[x]=y;
	}
}
inline void GetTop(int x,int t){
	top[x]=t;
	dfn[x]=++dcnt;
	idfn[dcnt]=x;
	if(hson[x]) GetTop(hson[x],t);
	for(int i=fi[x];i;i=ne[i]){
		int y=to[i];
		if(y==fa[x]) continue ;
		if(y==hson[x]) continue ;
		GetTop(y,y);
	}
}
inline void InitLCA(){
	for(int i=2;i<=ecnt;i++) lg[i]=lg[i>>1]+1;
	for(int i=1;i<=ecnt;i++) mn[i][0]=pos[elr[i]];
	for(int k=1;k<=lg[ecnt];k++){
		for(int i=1;i<=ecnt-(1<<k)+1;i++){
			mn[i][k]=min(mn[i][k-1],mn[i+(1<<k-1)][k-1]);
		}
	}
}
inline int LCA(int x,int y){
	x=pos[x],y=pos[y];
	if(x>y) swap(x,y);
	int k=lg[y-x+1];
	return elr[min(mn[x][k],mn[y-(1<<k)+1][k])];
}
inline int Hash(int u,int v){
	int lca=LCA(u,v);
	int ans=Mul(a[lca],bpw[dep[u]-dep[lca]]);
	AddAs(ans,Sub(pre[u],Mul(pre[lca],bpw[dep[u]-dep[lca]])));
	AddAs(ans,Mul(Mul(Sub(suf[v],suf[lca]),ibpw[dep[lca]]),bpw[dep[u]-dep[lca]]));
	return ans;
}
inline int KthAnc(int u,int k){
	while(k>dep[u]-dep[top[u]]) k-=dep[u]-dep[fa[top[u]]],u=fa[top[u]];
	return idfn[dfn[u]-k];
}
inline int KthPath(int u,int v,int k){
	k--;
	int lca=LCA(u,v),len=dep[u]+dep[v]-2*dep[lca];
	assert(lca);
	if(k<=dep[u]-dep[lca]) return Hash(u,KthAnc(u,k));
	else return Hash(u,KthAnc(v,len-k));
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		AddEdge(u,v);
		AddEdge(v,u);
	}

	bpw[0]=ibpw[0]=1;
	for(int i=1;i<=n;i++) bpw[i]=Mul(bpw[i-1],base);
	for(int i=1;i<=n;i++) ibpw[i]=Mul(ibpw[i-1],Inv(base));
	
	pre[1]=suf[1]=a[1];
	DFS(1);
	GetTop(1,1);
	InitLCA();

	cin>>q;
	while(q--){
		int u1,v1,u2,v2;
		cin>>u1>>v1>>u2>>v2;
		int lca1=LCA(u1,v1);
		int lca2=LCA(u2,v2);
		int l=0,r=min(dep[u1]+dep[v1]-2*dep[lca1],dep[u2]+dep[v2]-2*dep[lca2])+2;
		while(l+1<r){
			int mid=l+r>>1;
			if(KthPath(u1,v1,mid)==KthPath(u2,v2,mid)) l=mid;
			else r=mid;
		}
		cout<<l<<endl;
	}

	return 0;
}