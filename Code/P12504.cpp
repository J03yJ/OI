#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=5e5+9;

vector<int> e[N];
int fa[N],dep[N],siz[N],hson[N],n,d;
vector<array<int,2>> ans;
struct Data{
	multiset<array<int,2>> s[2];
	priority_queue<array<int,3>> q;
	inline void Try(int x,int lim){
		auto it=s[dep[x]&1^1].upper_bound({d+lim*2-dep[x],n+1});
		if(it!=s[dep[x]&1^1].begin()){
			int y=(*prev(it))[1];
			q.push({dep[x]+dep[y]-d>>1,x,y});
		}
	}
	inline void Insert(int x,int lim){
		s[dep[x]&1].insert({dep[x],x});
		Try(x,lim);
	}
	inline void Work(int lim){
		while(q.size()){
			if(lim>q.top()[0]) break;
			int x=q.top()[1],y=q.top()[2];
			q.pop();
			auto ix=s[dep[x]&1].find({dep[x],x});
			auto iy=s[dep[y]&1].find({dep[y],y});
			if(ix==s[dep[x]&1].end()) continue ;
			if(iy==s[dep[y]&1].end()) continue ;
			ans.push_back({(*ix)[1],(*iy)[1]});
			auto iw=s[dep[x]&1].end();
			auto iz=s[dep[y]&1].end();
			if(ix!=s[dep[x]&1].begin()) iw=prev(ix);
			if(iy!=s[dep[y]&1].begin()) iz=prev(iy);
			s[dep[x]&1].erase(ix);
			s[dep[y]&1].erase(iy);
			if(iw!=s[dep[x]&1].end()) Try((*iw)[1],lim);
			if(iz!=s[dep[y]&1].end()) Try((*iz)[1],lim);
		}
	}
	inline void Merge(Data x,int lim){
		for(int k:{0,1}){
			for(auto t:x.s[k]) Insert(t[1],lim);
			x.s[k].clear();
		}
		while(x.q.size()) x.q.pop();
	}
}dat[N];
inline void Solve(int x){
	siz[x]=1;
	for(int y:e[x]){
		if(y==fa[x]) continue ;
		dep[y]=dep[x]+1;
		fa[y]=x;
		Solve(y);
		siz[x]+=siz[y];
		if(!hson[x]||siz[y]>siz[hson[x]]) hson[x]=y;
	}
	swap(dat[x],dat[hson[x]]);
	dat[x].Insert(x,dep[x]);
	for(int y:e[x]){
		if(y==fa[x]) continue ;
		if(y==hson[x]) continue ;
		dat[x].Merge(dat[y],dep[x]);
	}
	dat[x].Work(dep[x]);
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>d;
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}

	d-=d&1^1;
	Solve(1);

	for(auto p:dat[1].s[0]){
		auto it=dat[1].s[1].upper_bound({d-p[0],n+1});
		if(it!=dat[1].s[1].begin()){
			it=prev(it);
			ans.push_back({p[1],(*it)[1]});
			dat[1].s[1].erase(it);
		}
	}

	cout<<ans.size()<<endl;
	for(auto t:ans) cout<<t[0]<<' '<<t[1]<<endl;

	return 0;
}