#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=3e2+9;
const int SQV=4e4+9;
const int LIM=sqrt(1e9);
const int inf=1e9+7;

vector<array<int,2>> fg[N],bg[N];
int p[N],f[N][SQV],g[N][SQV],vis[N][SQV],n,m;
inline void GetF(){
	f[1][1]=1;
	queue<array<int,2>> q;
	q.push({1,1});
	while(q.size()){
		int x=q.front()[0],val=q.front()[1];
		q.pop();
		for(auto e:fg[x]){
			if(1ll*e[1]*val>LIM) continue ;
			if(1ll*e[1]*val>p[e[0]]) continue ;
			if(f[e[0]][e[1]*val]) continue ;
			f[e[0]][e[1]*val]=1;
			q.push({e[0],e[1]*val});
		}
	}
}
inline void GetG(){
	g[n][1]=p[n];
	priority_queue<array<int,3>> q;
	q.push({g[n][1],n,1});
	while(q.size()){
		int x=q.top()[1],val=q.top()[2];
		q.pop();
		if(vis[x][val]) continue ;
		vis[x][val]=1;
		g[x][val]=min(g[x][val],p[x]);
		for(auto e:bg[x]){
			if(1ll*e[1]*val>LIM) continue ;
			if(g[x][val]/e[1]>g[e[0]][val*e[1]]){
				g[e[0]][val*e[1]]=g[x][val]/e[1];
				q.push({g[e[0]][val*e[1]],e[0],val*e[1]});
			}
		}
	}
}

inline void Clear(){
	for(int i=1;i<=n;i++) fg[i].clear(),bg[i].clear();
	for(int i=1;i<=n;i++) for(int j=1;j<=LIM;j++) f[i][j]=g[i][j]=vis[i][j]=0;
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--){
		cin>>n>>m;
		for(int i=1;i<=n;i++) cin>>p[i];
		for(int i=1,u,v,w;i<=m;i++){
			cin>>u>>v>>w;
			fg[u].push_back({v,w});
			bg[v].push_back({u,w});
		}

		GetF();
		GetG();
		int ans=-1;
		for(int i=1;i<=n;i++){
			for(auto e:fg[i]){
				int j=e[0],k=e[1];
				for(int p=1,q=LIM;p<=LIM;p++){
					while(q&&g[j][q]<1ll*p*k) q--;
					if(f[i][p]&&q) ans=max(ans,p*k*q); 
				}
			}
		}

		cout<<ans<<endl;

		Clear();
	}

	return 0;
}