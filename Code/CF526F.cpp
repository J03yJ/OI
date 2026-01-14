#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=3e5+9;
const int inf=1e9+7;

int p[N],n;

struct Node{
	int l,r;
	int val,cnt,tag;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define val(x) tr[x].val
#define cnt(x) tr[x].cnt
#define tag(x) tr[x].tag

inline void PushUp(int x){
	if(val(x<<1)==val(x<<1|1)) val(x)=val(x<<1),cnt(x)=cnt(x<<1)+cnt(x<<1|1);
	else if(val(x<<1)<val(x<<1|1)) val(x)=val(x<<1),cnt(x)=cnt(x<<1);
	else val(x)=val(x<<1|1),cnt(x)=cnt(x<<1|1);
}
inline void Push(int x,int k){
	val(x)+=k;
	tag(x)+=k;
}
inline void PushDown(int x){
	if(!tag(x)) return ;
	Push(x<<1,tag(x));
	Push(x<<1|1,tag(x));
	tag(x)=0;
}

inline void Build(int x,int l,int r){
	l(x)=l,r(x)=r,tag(x)=0;
	if(l(x)==r(x)) return val(x)=inf,cnt(x)=1,void();
	int mid=l(x)+r(x)>>1;
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	PushUp(x);
}
inline void Modify(int x,int l,int r,int k){
	if(l>r) return ;
	if(l<=l(x)&&r(x)<=r) return Push(x,k);
	int mid=l(x)+r(x)>>1;
	PushDown(x);
	if(l<=mid) Modify(x<<1,l,r,k);
	if(r>mid) Modify(x<<1|1,l,r,k);
	PushUp(x);
}
inline void Set(int x,int pos,int k){
	if(l(x)==r(x)) return val(x)=k,void();
	int mid=l(x)+r(x)>>1;
	PushDown(x);
	if(pos<=mid) Set(x<<1,pos,k);
	else Set(x<<1|1,pos,k);
	PushUp(x);
}
inline int Query(int x,int pos){
	if(l(x)==r(x)) return val(x);
	int mid=l(x)+r(x)>>1;
	PushDown(x);
	if(pos<=mid) return Query(x<<1,pos);
	else return Query(x<<1|1,pos);
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	
	cin>>n;
	for(int i=1,r,c;i<=n;i++){
		cin>>r>>c;
		p[r]=c;
	}

	ll ans=0;
	Build(1,1,n);
	vector<int> mx,mn;
	for(int i=1;i<=n;i++){
		while(mx.size()&&p[i]>p[mx.back()]){
			int j=mx.back();
			mx.pop_back();
			Modify(1,(mx.size()?mx.back():0)+1,j,p[i]-p[j]);
		}
		mx.push_back(i);
		while(mn.size()&&p[i]<p[mn.back()]){
			int j=mn.back();
			mn.pop_back();
			Modify(1,(mn.size()?mn.back():0)+1,j,p[j]-p[i]);
		}
		mn.push_back(i);
		Modify(1,1,i-1,-1);
		Set(1,i,0);
		ans+=cnt(1);
	}

	cout<<ans<<endl;
	
	return 0;
}