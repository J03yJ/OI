#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=3e5+9;
const ll inf=1e18;


ll dis[N];
int fi[N],ne[N<<2],to[N<<2],w[N<<2],adj;
inline void AddEdge(int x,int y,int z){
	ne[++adj]=fi[x];
	fi[x]=adj;
	to[adj]=y;
	w[adj]=z;
}

struct Node{
	int dat,lc,rc;
}tr[N<<6];

int cnt;
mt19937 rng(4649);
inline int Allc(){return ++cnt;}
inline int Allc(int k){int x=Allc();tr[x].dat=k;return x;}
inline int Clone(int x){int y=Allc();tr[y]=tr[x];return y;}
inline int Merge(int x,int y){
	if(!x||!y) return x|y;
	if(w[tr[x].dat]>w[tr[y].dat]) swap(x,y);
	x=Clone(x);
	if(rng()&1) swap(tr[x].lc,tr[x].rc);
	tr[x].rc=Merge(tr[x].rc,y);
	return x;
}
inline int Pop(int x){return Merge(tr[x].lc,tr[x].rc);}

int a[N],fa[N],root[N],n,k,s,t;

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];

	s=0,t=n+1;
	for(int i=1;i<=n;i++){
		for(int k:{1,2,3}) if(i-k>0) AddEdge(i-k,i,a[i]);
	}
	for(int i=1;i<=min(n,2);i++){
		AddEdge(s,i,a[i]);
		AddEdge(n-i+1,t,0);
	}

	for(int i=s;i<=t;i++) dis[i]=inf;
	dis[t]=0;
	for(int x=n;x>=s;x--){
		for(int i=fi[x];i;i=ne[i]){
			int y=to[i];
			if(dis[y]+w[i]<dis[x]){
				dis[x]=dis[y]+w[i];
				fa[x]=y;
			}
		}
	}
	for(int x=t;x>=s;x--){
		for(int i=fi[x];i;i=ne[i]){
			int y=to[i];
			if(y==fa[x]) continue ;
			w[i]+=-dis[x]+dis[y];
			root[x]=Merge(root[x],Allc(i));
		}
		root[x]=Merge(root[x],root[fa[x]]);
	}

	cout<<dis[s]<<endl,k--;
	priority_queue<pair<ll,int>> q;
	if(root[s]) q.push({-(dis[s]+w[tr[root[s]].dat]),root[s]});
	while(q.size()&&k-->0){
		int x=q.top().second;
		ll sum=-q.top().first;
		q.pop();
		cout<<sum<<endl;
		int i=tr[x].dat;
		if(root[to[i]]) q.push({-(sum+w[tr[root[to[i]]].dat]),root[to[i]]});
		for(int y:{tr[x].lc,tr[x].rc}){
			if(y) q.push({-(sum-w[tr[x].dat]+w[tr[y].dat]),y});
		}
	}
	while(k-->0) cout<<-1<<endl;

	return 0;
}