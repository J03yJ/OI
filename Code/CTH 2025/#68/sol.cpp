#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=2e5+9;
const int inf=1e9+7;
const ll lnf=1e18;
const int V=1e6;

struct Line{
	ll k,b;
	Line(){}
	Line(ll _k,ll _b){k=_k,b=_b;}
	inline ll operator ()(ll x){return k*x+b;}
};

struct Node{
	ll tag;
	int lc,rc;
	Line f=Line(inf,lnf);
}tr[N<<6];

int cnt;
inline int Allc(){return ++cnt;}
inline void Push(int &x,ll k){
	if(!x) return ;
	tr[x].f.b+=k,tr[x].tag+=k;
}
inline void PushDown(int x){
	if(tr[x].tag){
		Push(tr[x].lc,tr[x].tag);
		Push(tr[x].rc,tr[x].tag);
		tr[x].tag=0;
	}
}
inline bool Beat(int L,int R,Line f,Line g){return f(L)<g(L)&&f(R)<g(R);}
inline bool NoUse(int L,int R,Line f,Line g){return f(L)>=g(L)&&f(R)>=g(R);}
inline bool Invalid(Line f){return f.k>=inf/10||f.b>=lnf/10;}
inline void Update(int &x,int L,int R,int l,int r,Line f){
	if(!x) x=Allc();
	if(l<=L&&R<=r){
		if(L<R) PushDown(x);
		if(Beat(L,R,f,tr[x].f)) tr[x].f=f,tr[x].tag=0;
		else if(L<R){
			int mid=L+R>>1;
			if(!NoUse(L,mid,f,tr[x].f)) Update(tr[x].lc,L,mid,l,r,f);
			if(!NoUse(mid+1,R,f,tr[x].f)) Update(tr[x].rc,mid+1,R,l,r,f);
		}
		return ;
	}
	PushDown(x);
	int mid=L+R>>1;
	if(l<=mid) Update(tr[x].lc,L,mid,l,r,f);
	if(r>mid) Update(tr[x].rc,mid+1,R,l,r,f);
}
inline ll Min(int x,int L,int R,int pos){
	if(!x) return lnf;
	if(L==R) return tr[x].f(pos);
	PushDown(x);
	int mid=L+R>>1;
	if(pos<=mid) return min(tr[x].f(pos),Min(tr[x].lc,L,mid,pos));
	else return min(tr[x].f(pos),Min(tr[x].rc,mid+1,R,pos));
}
inline void Merge(int &x,int y,int L,int R){
	if(!y||Invalid(tr[y].f)) return ;
	if(!x||Invalid(tr[x].f)) return x=y,void();
	Update(x,L,R,L,R,tr[y].f);
	if(L==R) return ;
	int mid=L+R>>1;
	PushDown(x),PushDown(y);
	Merge(tr[x].lc,tr[y].lc,L,mid);
	Merge(tr[x].rc,tr[y].rc,mid+1,R);
}

vector<int> e[N];
int c[N],fa[N],root[N],n;
inline void Solve(int x){
	if(!e[x].size()){
		Update(root[x],1,V,1,V,Line(c[x],0));
	}else{
		ll sum=0;
		for(int y:e[x]){
			Solve(y);
			ll t=Min(root[y],1,V,c[x]);
			sum+=t;
			Push(root[y],-t);
			Merge(root[x],root[y],1,V);
		}
		Push(root[x],sum);
	}
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n;
	for(int i=2;i<=n;i++) cin>>fa[i],e[fa[i]].push_back(i);
	for(int i=1;i<=n;i++) cin>>c[i];

	if(n==1){
		cout<<0<<endl;
		return 0;
	}

	Solve(1);

	cout<<Min(root[1],1,V,c[1])<<endl;

	return 0;
}