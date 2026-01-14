#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=1e5+9;
const int inf=1e9+7;

struct Node{
	int l,r,dat,tag;
}tr[N<<2];

inline void PushUp(int x){tr[x].dat=min(tr[x<<1].dat,tr[x<<1|1].dat);}
inline void Push(int x,int k){tr[x].dat+=k,tr[x].tag+=k;}
inline void PushDown(int x){
	if(tr[x].tag){
		Push(x<<1,tr[x].tag);
		Push(x<<1|1,tr[x].tag);
		tr[x].tag=0;
	}
}
inline void Build(int x,int l,int r){
	tr[x].l=l,tr[x].r=r,tr[x].tag=0;
	if(tr[x].l==tr[x].r) return tr[x].dat=inf,void();
	int mid=tr[x].l+tr[x].r>>1;
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	PushUp(x);
}
inline void Set(int x,int pos,int k){
	if(tr[x].l==tr[x].r) return tr[x].dat=min(tr[x].dat,k),void();
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(pos<=mid) Set(x<<1,pos,k);
	else Set(x<<1|1,pos,k);
	PushUp(x);
}
inline void Modify(int x,int l,int r,int k){
	if(l>r) return ;
	if(l<=tr[x].l&&tr[x].r<=r) return Push(x,k);
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(l<=mid) Modify(x<<1,l,r,k);
	if(r>mid) Modify(x<<1|1,l,r,k);
	PushUp(x);
}
inline int Query(int x,int l,int r){
	if(l>r) return inf;
	if(l<=tr[x].l&&tr[x].r<=r) return tr[x].dat;
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1,ans=inf;
	if(l<=mid) ans=min(ans,Query(x<<1,l,r));
	if(r>mid) ans=min(ans,Query(x<<1|1,l,r));
	return ans;
}

int a[N],f[N],n,p,k;

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>p>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	a[++n]=inf;

	int ans=0;
	for(int i=1;i<p;i++) if(a[i]>=a[p]) ans++;
	
	vector<int> val(a,a+n+1);
	sort(val.begin(),val.end());
	val.erase(unique(val.begin(),val.end()));
	for(int i=1;i<=n;i++) a[i]=lower_bound(val.begin(),val.end(),a[i])-val.begin();

	f[p]=0;
	for(int i=p+1;i<=n;i++) f[i]=inf;
	for(int o=1;o<=k;o++){
		Build(1,1,n);
		for(int i=p;i<=n;i++){
			int tmp=f[i];
			f[i]=Query(1,1,a[i]-1);
			Modify(1,1,a[i]-1,1);
			Set(1,a[i],tmp);
		}
	}
	ans+=f[n];
	
	cout<<(ans<inf/2?ans:-1)<<endl;

	return 0;
}