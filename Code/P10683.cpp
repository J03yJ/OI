#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e5+9;

multiset<int> s;
vector<array<int,5>> rb;
int a[N],b[N],fa[N<<1],siz[N<<1],dlt[N<<1],ac[N<<1],n;
inline void Init(int lim){
	rb.clear();
	for(int i=1;i<=lim;i++) fa[i]=i,siz[i]=1,dlt[i]=ac[i]=0;
}
inline int Find(int x){return fa[x]==x?x:Find(fa[x]);}
inline void Merge(int x,int y,bool t=0){
	x=Find(x),y=Find(y);
	if(x==y) return ;
	if(t){
		rb.push_back({x,fa[x],siz[x],dlt[x],ac[x]});
		rb.push_back({y,fa[y],siz[y],dlt[y],ac[y]});
	}
	s.erase(dlt[x]);
	s.erase(dlt[y]);
	if(siz[x]<siz[y]) swap(x,y);
	siz[x]+=siz[y];
	dlt[x]+=dlt[y];
	ac[x]+=ac[y];
	fa[y]=x;
	s.insert(dlt[x]);
}
inline void Recall(){
	auto t=rb.back();
	rb.pop_back();
	fa[t[0]]=t[1],siz[t[0]]=t[2],dlt[t[0]]=t[3],ac[t[0]]=t[4];
}

inline void Solve(int typ){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];

	if(typ==0){
		int ans=0;
		Init(n<<1);
		for(int i=1;i<=n;i++) ac[i]++,dlt[i]++,dlt[i+n]--;
		for(int i=1;i<=n;i++) Merge(a[i],b[i]+n);
		for(int i=1;i<=(n<<1);i++) if(i==Find(i)) ans+=ac[i]-max(dlt[i],0);
		cout<<ans<<endl;
	}else{
		
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	int T,typ;
	cin>>T>>typ;
	while(T--) Solve(typ);

	return 0;
}