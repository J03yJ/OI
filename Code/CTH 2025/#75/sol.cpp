#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=3e5+9;

ll wsu[N];
int fa[N],u[N],v[N],lim[N],n,m;
priority_queue<int> td;
priority_queue<pair<ll,int>> cn[N];
inline int Find(int x){return fa[x]==x?x:fa[x]=Find(fa[x]);}
inline void Upd(int x){
	while(cn[x].size()&&wsu[x]>=-cn[x].top().first){
		td.push(-cn[x].top().second);
		cn[x].pop();
	}
}
inline void Merge(int x,int y){
	x=Find(x),y=Find(y);
	if(x==y) return ;
	if(cn[x].size()<cn[y].size()) swap(x,y);
	fa[y]=x;
	wsu[x]+=wsu[y];
	while(cn[y].size()) cn[x].push(cn[y].top()),cn[y].pop();
	Upd(x);
}
vector<int> ans;
inline bool Work(){
	while(td.size()){
		int i=-td.top();
		td.pop();
		if(Find(u[i])==Find(v[i])) continue ;
		if(wsu[Find(u[i])]+wsu[Find(v[i])]>=lim[i]){
			Merge(u[i],v[i]);
			ans.push_back(i);
		}else{
			int dlt=lim[i]-(wsu[Find(u[i])]+wsu[Find(v[i])])+1>>1;
			cn[Find(u[i])].push({-(dlt+wsu[Find(u[i])]),i});
			cn[Find(v[i])].push({-(dlt+wsu[Find(v[i])]),i});
		}
	}
	return 0;
}

signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>wsu[i],fa[i]=i;
	for(int i=1;i<=m;i++){
		cin>>u[i]>>v[i]>>lim[i];
		int dlt=lim[i]+1>>1;
		cn[u[i]].push({-dlt,i});
		cn[v[i]].push({-dlt,i});
	}

	for(int i=1;i<=n;i++) Upd(i);
	while(Work()) ;

	cout<<ans.size()<<endl;
	for(int x:ans) cout<<x<<' ';cout<<endl;

	return 0;
}