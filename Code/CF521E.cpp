#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e5+9;

int fi[N],ne[N<<1],to[N<<1],adj;
inline void AddEdge(int x,int y){
	ne[++adj]=fi[x];
	fi[x]=adj;
	to[adj]=y;
}

int fa[N],dep[N],vis[N],u[N],v[N],n,m;
inline vector<int> AncPath(int u,int v){
	vector<int> res;
	bool flag=dep[u]<dep[v];
	if(dep[u]<dep[v]) swap(u,v);
	int cur=u;
	while(cur){
		res.push_back(cur);
		if(cur==v) break ;
		cur=fa[cur];
	}
	if(flag) reverse(res.begin(),res.end());
	return res;
}
bool err;
inline void Work(int x){
	vis[x]=1;
	for(int i=fi[x];i;i=ne[i]){
		int y=to[i];
		if(y==fa[x]) continue ;
		if(!vis[y]){
			fa[y]=x;
			dep[y]=dep[x]+1;
			Work(y);
			if(err) return ;
		}else if(dep[x]>dep[y]){
			int cur=x;
			do{
				if(u[cur]){
					int ruc=fa[cur];
					while(ruc!=y&&u[ruc]==u[cur]) ruc=fa[ruc];
					cout<<cur<<' '<<ruc<<endl;
					auto tmp=AncPath(cur,ruc);
					cout<<tmp.size()<<' ';
					for(int i:tmp) cout<<i<<' ';
					cout<<endl;
					auto tmp1=AncPath(cur,x);
					auto tmp2=AncPath(y,ruc);
					cout<<tmp1.size()+tmp2.size()<<' ';
					for(int i:tmp1) cout<<i<<' ';
					for(int i:tmp2) cout<<i<<' ';
					cout<<endl;
					tmp1=AncPath(cur,u[cur]);
					tmp2=AncPath(v[cur],ruc);
					cout<<tmp1.size()+tmp2.size()<<' ';
					for(int i:tmp1) cout<<i<<' ';
					for(int i:tmp2) cout<<i<<' ';
					cout<<endl;
					err=1;
					return ;
				}
				u[cur]=x,v[cur]=y;
				cur=fa[cur];
			}while(cur!=y);
		}
	}
}

inline void Clear(){
	for(int i=1;i<=n;i++) fa[i]=dep[i]=vis[i]=u[i]=v[i]=fi[i]=0;
	adj=err=0;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	int T;
	cin>>T;
	while(T--){
		cin>>n>>m;
		for(int i=1,u,v;i<=m;i++){
			cin>>u>>v;
			AddEdge(u,v);
			AddEdge(v,u);
		}

		for(int i=1;i<=n;i++) if(!err&&!vis[i]) Work(i);
		if(!err) cout<<-1<<endl;

		Clear();
	}

	return 0;
}