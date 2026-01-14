#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
using bint=__int128;
const int N=1e5+9;

struct Node{
	int l,r;
	ll tag,cov;
	bint dat,sum;
}tr[N<<4];
inline void PushUp(int x){
	tr[x].dat=tr[x<<1].dat+tr[x<<1|1].dat;
	tr[x].sum=tr[x<<1].sum+tr[x<<1|1].sum;
}
inline void PushAdd(int x,ll k){tr[x].dat+=tr[x].sum*k,tr[x].tag+=k;}
inline void PushCov(int x,ll k){tr[x].dat=tr[x].sum*k,tr[x].cov=k,tr[x].tag=0;}
inline void PushDown(int x){
	if(~tr[x].cov) PushCov(x<<1,tr[x].cov),PushCov(x<<1|1,tr[x].cov),tr[x].cov=-1;
	if(tr[x].tag) PushAdd(x<<1,tr[x].tag),PushAdd(x<<1|1,tr[x].tag),tr[x].tag=0;
}
inline void Build(int x,int l,int r,vector<ll> &val){
	tr[x].l=l,tr[x].r=r,tr[x].dat=tr[x].tag=0,tr[x].cov=0;
	if(tr[x].l==tr[x].r) return tr[x].sum=val[tr[x].l+1]-val[tr[x].l],void();
	int mid=tr[x].l+tr[x].r>>1;
	Build(x<<1,l,mid,val),Build(x<<1|1,mid+1,r,val);
	PushUp(x);
}
inline void Modify(int x,int l,int r,ll k){
	if(l<=tr[x].l&&tr[x].r<=r) return PushAdd(x,k);
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(l<=mid) Modify(x<<1,l,r,k);
	if(r>mid) Modify(x<<1|1,l,r,k);
	PushUp(x);
}
inline ll Query(int x,int l,int r){
	if(l>r) return 0;
	if(l<=tr[x].l&&tr[x].r<=r) return tr[x].dat;
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(r<=mid) return Query(x<<1,l,r);
	else if(l>mid) return Query(x<<1|1,l,r);
	else return Query(x<<1,l,r)+Query(x<<1|1,l,r);
}
inline void Eat(int x,ll k){
	if(tr[x].l==tr[x].r) return tr[x].dat-=min(tr[x].dat,bint(k)),void();
	PushDown(x);
	if(k<=tr[x<<1].dat) Eat(x<<1,k);
	else k-=tr[x<<1].dat,PushCov(x<<1,0),Eat(x<<1|1,k);
	PushUp(x);
}

int n,m;
ll x[N],y[N],p[N],t[N];
inline bool Check(ll k){
	vector<ll> val={-1};
	for(int i=1;i<=n;i++) val.push_back(x[i]+min(p[i],k)),val.push_back(x[i]+k);
	for(int i=1;i<=m;i++) val.push_back(y[i]);
	sort(val.begin(),val.end());
	val.erase(unique(val.begin(),val.end()),val.end());
	int tot=val.size()-1;
	val.push_back(1e18);

	Build(1,1,tot,val);
	vector<array<ll,3>> opr;
	for(int i=1;i<=n;i++) opr.push_back({x[i],0,i});
	for(int i=1;i<=m;i++) opr.push_back({y[i],1,i});
	sort(opr.begin(),opr.end());
	for(auto du:opr){
		int i=du[2];
		if(du[1]==0){
			int l=lower_bound(val.begin(),val.end(),x[i]+min(k,p[i]))-val.begin();
			int r=lower_bound(val.begin(),val.end(),x[i]+k)-val.begin()-1;
			if(l<=r) Modify(1,l,r,1);
		}else{
			int p=lower_bound(val.begin(),val.end(),y[i])-val.begin();
			if(Query(1,1,p-1)) return 0;
			Eat(1,t[i]);
		}
	}
	return !Query(1,1,tot);
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>x[i]>>p[i];
	for(int i=1;i<=m;i++) cin>>y[i]>>t[i];
	
	ll lim=(accumulate(p+1,p+n+1,0ll)+accumulate(t+1,t+m+1,0ll))/n;

	ll l=-1,r=lim+1ll;
	while(l+1<r){
		ll mid=l+r>>1;
		if(Check(mid)) l=mid;
		else r=mid;
	}

	cout<<l<<endl;
	
	return 0;
}