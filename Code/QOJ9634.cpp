#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using bint=__int128;
const int N=5e5+9;

struct Node{
	int l,r;
	bint dat,som,hsom,tag,lcr;
	inline int Len(){return r-l+1;}
}tr[N<<2];

inline bint GetSom(int x,bint k){
	if(k>tr[x].dat) return tr[x].Len()*k;
	if(tr[x].l==tr[x].r) return max(k,tr[x].dat);
	if(tr[x<<1].dat<=k) return k*tr[x<<1].Len()+GetSom(x<<1|1,k);
	else return GetSom(x<<1,k)+tr[x].som-tr[x<<1].som;
}
inline void PushUp(int x){
	tr[x].dat=max(tr[x<<1].dat,tr[x<<1|1].dat);
	tr[x].som=tr[x<<1].som+GetSom(x<<1|1,tr[x<<1].dat);
	tr[x].hsom=tr[x<<1].hsom+tr[x<<1|1].hsom+tr[x].lcr*(tr[x>>1].som-tr[x^1].som);
}
inline void OnlyHS(int x){
	tr[x].hsom=tr[x<<1].hsom+tr[x<<1|1].hsom+tr[x].lcr*(tr[x>>1].som-tr[x^1].som);
}
inline void PushAdd(int x,bint k){tr[x].hsom+=k*tr[x].Len(),tr[x].tag+=k;}
inline void DownAdd(int x){if(tr[x].tag) PushAdd(x<<1,tr[x].tag),PushAdd(x<<1|1,tr[x].tag),tr[x].tag=0;}
inline void PushLcr(int x,bint k){tr[x].lcr+=k,tr[x].hsom+=k*(tr[x>>1].som-tr[x^1].som);}
inline void Work(int x,bint k,bint c){
	if(tr[x].l==tr[x].r) return PushAdd(x,max(tr[x].dat,k)*c);
	DownAdd(x);
	if(tr[x<<1].dat<=k) PushAdd(x<<1,c*k),Work(x<<1|1,k,c);
	else PushLcr(x<<1|1,c),Work(x<<1,k,c);
	OnlyHS(x);
}
inline void DownLcr(int x){if(tr[x].lcr) Work(x,tr[x^1].dat,tr[x].lcr),tr[x].lcr=0,OnlyHS(x);}
inline void PushDown(int x){if(tr[x].l!=tr[x].r) DownLcr(x),DownAdd(x);}

int a[N];
inline void Build(int x,int l,int r){
	tr[x].l=l,tr[x].r=r;
	if(tr[x].l==tr[x].r) return tr[x].dat=tr[x].som=a[tr[x].l],void();
	int mid=tr[x].l+tr[x].r>>1;
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	PushUp(x);
}
inline void Modify(int x,int pos,bint k){
	if(tr[x].l==tr[x].r) return tr[x].dat=tr[x].som=k,void();
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(pos<=mid) PushDown(x<<1|1),Modify(x<<1,pos,k);
	else Modify(x<<1|1,pos,k);
	PushUp(x);
}
inline bint Stamp(int x,int l,int r,bint k,bint c){
	if(l<=tr[x].l&&tr[x].r<=r) return Work(x,k,c),max(tr[x].dat,k);
	DownAdd(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(r<=mid) k=Stamp(x<<1,l,r,k,c);
	else if(l>mid) k=Stamp(x<<1|1,l,r,k,c);
	else k=Stamp(x<<1|1,l,r,Stamp(x<<1,l,r,k,c),c);
	OnlyHS(x);
	return k;
}
inline bint HSom(int x,int l,int r){
	if(l<=tr[x].l&&tr[x].r<=r) return tr[x].hsom;
	PushDown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(r<=mid) return HSom(x<<1,l,r);
	else if(l>mid) return HSom(x<<1|1,l,r);
	else return HSom(x<<1,l,r)+HSom(x<<1|1,l,r);
}

inline void Write(bint x){
	if(x<10) cout<<(int)x;
	else Write(x/10),cout<<(int)(x%10);
}

int n,q;

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);
	
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];

	Build(1,1,n);
	while(q--){
		int op,x,y;
		cin>>op>>x>>y;
		if(op==1) Modify(1,x,y);
		else if(op==2) Stamp(1,x,y,0,1);
		else Write(HSom(1,x,y)),cout<<endl;
	}

	return 0;
}