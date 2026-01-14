#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=2e5+9;

ll dlt[N];
int a[N],c[N],n,m,k;

struct KS{
	int llim,rlim;
	vector<ll> v,res;
	priority_queue<array<ll,4>> q;
	inline void Init(){
		ll sum=0;
		sort(v.begin(),v.end());
		rlim=min(rlim,signed(v.size()));
		if(llim>v.size()) return ;
		for(int i=0;i<llim;i++) sum+=v[i];
		q.push({-sum,llim-1,llim-1,ll(v.size())});
	}
	inline void Insert(int x){v.push_back(x);}
	inline bool Extend(int i){
		while(q.size()&&res.size()<i){
			auto t=q.top();
			q.pop();
			res.push_back(-t[0]);
			if(t[1]==t[2]&&t[3]==v.size()&&t[2]+1<rlim){
				q.push({-(-t[0]+v[t[1]+1]),t[1]+1,t[2]+1,t[3]});
			}
			if(~t[2]&&t[2]+1<t[3]){
				q.push({-(-t[0]-v[t[2]]+v[t[2]+1]),t[1],t[2]+1,t[3]});
			}
			if(t[1]>0&&t[1]<t[2]){
				q.push({-(-t[0]-v[t[1]-1]+v[t[1]]),t[1]-1,t[1],t[2]});
			}
		}
		return res.size()>=i;
	}
	inline ll operator [](int x){return res[x];}
}p[N];

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>m>>k;
	for(int i=1;i<=n;i++) cin>>a[i]>>c[i],p[a[i]].Insert(c[i]);
	for(int i=1;i<=m;i++) cin>>p[i].llim>>p[i].rlim,p[i].Init();

	ll sum=0;
	vector<int> id;
	for(int i=1;i<=m;i++){
		if(!p[i].Extend(1)){
			while(k--) cout<<-1<<endl;
			return 0;
		}
		sum+=p[i][0];
		if(p[i].Extend(2)){
			id.push_back(i);
			dlt[i]=p[i][1]-p[i][0];
		}
	}
	sort(id.begin(),id.end(),[](int i,int j){return dlt[i]<dlt[j];});

	priority_queue<array<ll,4>> q;
	q.push({-sum,-1,0});
	while(q.size()&&k--){
		auto t=q.top();
		q.pop();
		cout<<-t[0]<<endl;

		if(~t[1]&&p[id[t[1]]].Extend(t[2]+2)){
			q.push({-(-t[0]-p[id[t[1]]][t[2]]+p[id[t[1]]][t[2]+1]),t[1],t[2]+1});
		}
		if(t[1]+1<id.size()){
			q.push({-(-t[0]-p[id[t[1]+1]][0]+p[id[t[1]+1]][1]),t[1]+1,1});
		}
		if(t[1]+1<id.size()&&t[2]==1){
			q.push({-(-t[0]-p[id[t[1]]][1]+p[id[t[1]]][0]-p[id[t[1]+1]][0]+p[id[t[1]+1]][1]),t[1]+1,1});
		}
	}
	while(k-->0) cout<<-1<<endl;

	return 0;
}