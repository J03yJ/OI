#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=1e5+9;
const int inf=1e9+7;

struct RARMQ{
	struct Node{
		int l,r;
		ll tag;
		pair<ll,int> dat;
	}tr[N<<2];

	inline void PushUp(int x){tr[x].dat=min(tr[x<<1].dat,tr[x<<1|1].dat);}
	inline void Push(int x,ll k){tr[x].dat.first+=k,tr[x].tag+=k;}
	inline void PushDown(int x){
		if(tr[x].tag){
			Push(x<<1,tr[x].tag);
			Push(x<<1|1,tr[x].tag);
			tr[x].tag=0;
		}
	}
	
	inline void Build(int x,int l,int r){
		tr[x].l=l,tr[x].r=r,tr[x].tag=0;
		if(tr[x].l==tr[x].r) return tr[x].dat={0,l},void();
		int mid=l+r>>1;
		Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
		PushUp(x);
	}
	inline void Modify(int x,int l,int r,ll k){
		if(l>r) return ;
		if(l<=tr[x].l&&tr[x].r<=r) return Push(x,k);
		PushDown(x);
		int mid=tr[x].l+tr[x].r>>1;
		if(l<=mid) Modify(x<<1,l,r,k);
		if(r>mid) Modify(x<<1|1,l,r,k);
		PushUp(x);
	}
	inline pair<ll,int> Query(int x,int l,int r){
		if(l>r) return {inf,0};
		if(l<=tr[x].l&&tr[x].r<=r) return tr[x].dat;
		PushDown(x);
		int mid=tr[x].l+tr[x].r>>1;
		if(r<=mid) return Query(x<<1,l,r);
		else if(l>mid) return Query(x<<1|1,l,r);
		else return min(Query(x<<1,l,r),Query(x<<1|1,l,r));
	}
}L,R;
struct PSRMQ{
	struct DelHeap{
		priority_queue<array<int,2>> p,q;
		inline void Insert(array<int,2> x){p.push(x);}
		inline void Erase(array<int,2> x){q.push(x);}
		inline array<int,2> Top(){
			while(q.size()&&p.top()==q.top()) p.pop(),q.pop();
			return p.top();
		}
		inline void Clear(){
			while(p.size()) p.pop();
			while(q.size()) q.pop();
		}
	}h[N];
	struct Node{
		int l,r;
		array<int,2> dat;
	}tr[N<<2];
	inline void PushUp(int x){tr[x].dat=min(tr[x<<1].dat,tr[x<<1|1].dat);}
	inline void Build(int x,int l,int r){
		tr[x].l=l,tr[x].r=r;
		if(tr[x].l==tr[x].r){
			h[l].Clear();
			h[l].Insert({-inf,0});
			tr[x].dat={inf,0};
			return ;
		}
		int mid=l+r>>1;
		Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
		PushUp(x);
	}
	inline void Update(int x,int pos){
		if(tr[x].l==tr[x].r){
			tr[x].dat={-h[pos].Top()[0],h[pos].Top()[1]};
			return ;
		}
		int mid=tr[x].l+tr[x].r>>1;
		if(pos<=mid) Update(x<<1,pos);
		else Update(x<<1|1,pos);
		PushUp(x);
	}
	inline array<int,2> Query(int x,int l,int r){
		if(l<=tr[x].l&&tr[x].r<=r) return tr[x].dat;
		int mid=tr[x].l+tr[x].r>>1;
		if(r<=mid) return Query(x<<1,l,r);
		else if(l>mid) return Query(x<<1|1,l,r);
		else return min(Query(x<<1,l,r),Query(x<<1|1,l,r));
	}
}P;

ll ans[N];
vector<int> st[N],ed[N];
int a[N],l[N],r[N],c[N],lc[N],rc[N],n,m;
inline void Solve(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=m;i++){
		cin>>l[i]>>r[i]>>c[i];
		if(!c[i]) continue ;
		st[l[i]].push_back(i);
		ed[r[i]].push_back(i);
	}

	L.Build(1,0,n+1),R.Build(1,0,n+1),P.Build(1,0,n+1);
	for(int i=1;i<=n;i++) R.Modify(1,i,n,a[i]);
	for(int x=1;x<=n;x++){
		for(int i:st[x]){
			lc[i]=0,rc[i]=c[i];
			P.h[r[i]].Insert({-l[i],i});
			P.Update(1,r[i]);
			R.Modify(1,0,r[i]-1,c[i]);
		}
		while(true){
			auto p=R.Query(1,x-1,n);
			auto q=P.Query(1,x-1,p.second);
			if(!q[1]) break ;
			int i=q[1];
			ll tmp=min(ll(rc[i]),R.Query(1,x-1,r[i]-1).first-p.first);
			lc[i]+=tmp,rc[i]-=tmp;
			L.Modify(1,l[i]+1,n+1,tmp);
			R.Modify(1,0,r[i]-1,-tmp);
			if(!rc[i]){
				P.h[r[i]].Erase({-l[i],i});
				P.Update(1,r[i]);
			}
		}
		ans[x]=L.Query(1,1,x).first+R.Query(1,x-1,n).first;
		for(int i:ed[x]){
			if(rc[i]){
				P.h[r[i]].Erase({-l[i],i});
				P.Update(1,r[i]);
			}
			L.Modify(1,l[i]+1,n+1,-lc[i]);
			R.Modify(1,0,r[i]-1,-rc[i]);
		}
		R.Modify(1,x,n,-a[x]);
		L.Modify(1,1,x,a[x]);
	}

	for(int i=1;i<=n;i++) cout<<ans[i]<<' ';cout<<endl;

	for(int i=1;i<=n;i++){
		st[i].clear();
		ed[i].clear();
	}
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}