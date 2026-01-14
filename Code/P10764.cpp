#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=5e5+9;
const int mod=1e9+7;

inline void AddAs(int &x,int y){if((x+=y)>=mod) x-=mod;}
inline void SubAs(int &x,int y){if((x-=y)<0) x+=mod;}
inline void MulAs(int &x,int y){x=1ll*x*y%mod;}
inline int Add(int x,int y){if((x+=y)>=mod) x-=mod;return x;}
inline int Sub(int x,int y){if((x-=y)<0) x+=mod;return x;}
inline int Mul(int x,int y){return 1ll*x*y%mod;}
inline int QPow(int x,int y){
	int res=1;
	while(y){
		if(y&1) MulAs(res,x);
		MulAs(x,x);
		y>>=1;
	}
	return res;
}
inline int Inv(int x){return QPow(x,mod-2);}

int a[N],b[N],n;

struct Node{
	int l,r,dat,tag;
}tr[N<<2];
inline void PushUp(int x){tr[x].dat=Add(tr[x<<1].dat,tr[x<<1|1].dat);}
inline void Push(int x,int k){MulAs(tr[x].dat,k),MulAs(tr[x].tag,k);}
inline void PushDown(int x){if(tr[x].tag!=1) Push(x<<1,tr[x].tag),Push(x<<1|1,tr[x].tag),tr[x].tag=1;}
inline void Build(int x,int l,int r){
	tr[x].l=l,tr[x].r=r,tr[x].dat=0,tr[x].tag=1;
	if(tr[x].l==tr[x].r) return ;
	int mid=tr[x].l+tr[x].r>>1;
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	PushUp(x);
}
inline void Set(int x,int pos,int k){
	if(tr[x].l==tr[x].r) return tr[x].dat=Mul(tr[x].tag,k),void();
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(pos<=mid) Set(x<<1,pos,k);
	else Set(x<<1|1,pos,k);
	PushUp(x);
}
inline void Modify(int x,int l,int r,int k){
	if(l<=tr[x].l&&tr[x].r<=r) return Push(x,k);
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(l<=mid) Modify(x<<1,l,r,k);
	if(r>mid) Modify(x<<1|1,l,r,k);
	PushUp(x);
}

vector<array<int,2>> op[N<<1];

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];

	vector<int> val={INT_MAX,0};
	for(int i=1;i<=n;i++) if(a[i]>b[i]) swap(a[i],b[i]);
	for(int i=1;i<=n;i++) val.insert(val.end(),{a[i],b[i]});
	sort(val.begin(),val.end(),greater<int>());
	val.erase(unique(val.begin(),val.end()),val.end());
	for(int i=1;i<=n;i++){
		int p=lower_bound(val.begin(),val.end(),b[i],greater<int>())-val.begin();
		int q=lower_bound(val.begin(),val.end(),a[i],greater<int>())-val.begin();
		op[p].push_back({i,0});
		op[q].push_back({i,1});
	}

	int ans=0,inv=Inv(2),cntb=n,cnts=0,cntt=0;
	Build(1,1,n);
	for(int i=1;i+1<val.size();i++){
		for(auto t:op[i]){
			int j=t[0];
			if(!t[1]){
				Set(1,j,j-1);
				if(j>1) Modify(1,1,j-1,2);
				cntb--,cnts++;
			}else{
				if(j<n) Modify(1,j+1,n,0);
				if(j>1) Modify(1,1,j-1,inv);
				cnts--,cntt++;
			}
		}
		SubAs(ans,Mul(Mul(val[i]-val[i+1],tr[1].dat),QPow(2,cntb+cntt)));
	}
	Build(1,1,n);
	cntb=n,cnts=0,cntt=0;
	for(int i=1;i+1<val.size();i++){
		for(auto t:op[i]){
			int j=t[0];
			if(!t[1]){
				Set(1,j,j);
				if(j<n) Modify(1,j+1,n,2);
				cntb--,cnts++;
			}else{
				if(j>1) Modify(1,1,j-1,0);
				if(j<n) Modify(1,j+1,n,inv);
				cnts--,cntt++;
			}
		}
		AddAs(ans,Mul(Mul(val[i]-val[i+1],tr[1].dat),QPow(2,cntb+cntt)));
	}
	cntb=n,cnts=0,cntt=0;
	for(int i=1;i+1<val.size();i++){
		for(auto t:op[i]){
			if(!t[1]) cntb--,cnts++;
			else cnts--,cntt++;
		}
		if(!cntt){
			if(cnts) SubAs(ans,Mul(val[i]-val[i+1],Mul(cnts,QPow(2,cntb+cntt+cnts-1))));
		}else{
			SubAs(ans,Mul(val[i]-val[i+1],Mul(cntt,QPow(2,cntb+cntt+cnts))));
			if(cnts) SubAs(ans,Mul(val[i]-val[i+1],Mul(cnts,QPow(2,cntb+cntt+cnts-1))));
		}
	}

	cout<<ans<<endl;

	return 0;
}