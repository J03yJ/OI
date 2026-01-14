#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
using bint=__int128;
const int N=6e5+9;
const int inf=1e9+7;

int x[N],n,q,d,x0;
struct SgT{
	struct Node{
		bint sum,val,btag,ktag;
		int lc,rc;
	}tr[N<<4];
	#define lc(x) tr[x].lc
	#define rc(x) tr[x].rc
	#define val(x) tr[x].val
	#define sum(x) tr[x].sum
	#define btag(x) tr[x].btag
	#define ktag(x) tr[x].ktag

	int root=1,cnt=1;
	inline int Allc(){return ++cnt;}
	inline void Push(int &x,int L,int R,bint b,bint k){
		if(!x) x=Allc();
		btag(x)+=b;
		ktag(x)+=k;
		val(x)+=b+(R-L)*k;
		sum(x)+=bint(b)*(R-L+1);
		sum(x)+=bint(k)*(R-L)*(R-L+1)/2;
	}
	inline void PushDown(int x,int L,int R){
		if(!btag(x)&&!ktag(x)) return ;
		int mid=L+R>>1;
		Push(lc(x),L,mid,btag(x),ktag(x));
		Push(rc(x),mid+1,R,btag(x)+(mid-L+1)*ktag(x),ktag(x));
		btag(x)=ktag(x)=0;
	}
	inline void PushUp(int x){
		val(x)=val(rc(x));
		sum(x)=sum(lc(x))+sum(rc(x));
	}
	inline void Modify(int &x,int L,int R,int l,int r,bint b,bint k){
		if(l>r) return ;
		if(!x) x=Allc();
		if(l<=L&&R<=r) return Push(x,L,R,b,k);
		int mid=L+R>>1;
		PushDown(x,L,R);
		if(r<=mid) Modify(lc(x),L,mid,l,r,b,k);
		else if(l>mid) Modify(rc(x),mid+1,R,l,r,b,k);
		else{
			Modify(lc(x),L,mid,l,mid,b,k);
			Modify(rc(x),mid+1,R,mid+1,r,b+(mid-l+1)*k,k);
		}
		PushUp(x);
	}
	inline int Find(int &x,int L,int R,bint k){
		if(!x) x=Allc();
		if(L==R) return L;
		if(!lc(x)){
			if(!ktag(x)) return L;
			bint tmp=k-btag(x);
			return L+max(bint(0),(tmp+ktag(x)-1)/ktag(x));
		}
		int mid=L+R>>1;
		PushDown(x,L,R);
		if(k<=val(lc(x))) return Find(lc(x),L,mid,k);
		else return Find(rc(x),mid+1,R,k);
	}
	inline bint Sum(int x,int L,int R,int l,int r){
		if(!x) x=Allc();
		if(l>r) return 0;
		if(l<=L&&R<=r) return sum(x);
		if(!lc(x)){
			bint lsum=btag(x)*(l-L)+ktag(x)*(l-L)*(l-L-1)/2;
			bint rsum=btag(x)*(r-L+1)+ktag(x)*(r-L+1)*(r-L)/2;
			return rsum-lsum;
		}
		int mid=L+R>>1;
		PushDown(x,L,R);
		if(r<=mid) return Sum(lc(x),L,mid,l,r);
		else if(l>mid) return Sum(rc(x),mid+1,R,l,r);
		else return Sum(lc(x),L,mid,l,mid)+Sum(rc(x),mid+1,R,mid+1,r);
	}
};
struct Convex{
	SgT tr;
	bint st;
	inline void Insert(int x){
		st+=1ll*x*x;
		int p=(x%d)<=d/2?x/d:x/d+1;
		tr.Modify(tr.root,0,inf,0,p-1,1ll*d*d-2ll*d*x,2ll*d*d);
	}
	inline ll Query(int k){
		int pos=tr.Find(tr.root,0,inf,-k);
		return st+tr.Sum(tr.root,0,inf,0,pos-1)+1ll*k*pos;
	}
}f,g;

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n;
	for(int i=1;i<=n;i++) cin>>x[i];
	cin>>x0>>d;
	sort(x+1,x+n+1);

	int m=0;
	while(m<n&&x[m+1]<=x0) m++;
	for(int i=1;i<=m;i++) f.Insert(x0-x[i]);
	for(int i=m+1;i<=n;i++) g.Insert(x[i]-x0);

	cin>>q;
	while(q--){
		int k;
		cin>>k;
		cout<<ll(min(f.Query(k)+g.Query(2*k),f.Query(2*k)+g.Query(k)))<<endl;
	}

	return 0;
}