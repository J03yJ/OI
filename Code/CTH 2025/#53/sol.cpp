#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=6e5+9;

int c[N],n,m,k;
vector<int> e[N];

int dis[N],pre[N],in[N];
inline void LPFA(){
	queue<int> q;
	for(int i=1;i<=n;i++){
		dis[i]=pre[i]=0;
		if(!in[i]) q.push(i);
	}
	while(q.size()){
		int x=q.front();
		q.pop();
		for(int y:e[x]){
			if(dis[x]+1>dis[y]){
				pre[y]=x;
				dis[y]=dis[x]+1;
			}
			if(!--in[y]) q.push(y);
		}
	}
}
inline void Solve(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++) cin>>c[i];
	for(int i=1,u,v;i<=m;i++){
		cin>>u>>v;
		if(c[u]>c[v]) e[u].push_back(v),in[v]++;
		else e[v].push_back(u),in[u]++;
	}

	LPFA();

	int p=max_element(dis+1,dis+n+1)-dis;
	cout<<dis[p]+1<<' ';
	for(int i=1;i<=n;i++) cout<<dis[i]+1<<' ';cout<<endl;
	while(p) cout<<p<<' ',p=pre[p];cout<<endl;

	for(int i=1;i<=n;i++) e[i].clear();
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);
	
	int T;
	cin>>T;
	while(T--) Solve();
	
	return 0;
}