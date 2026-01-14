#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=2e5+9;
const int mod=998244353;

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

int typ,n;
vector<int> e[N];

namespace Case1{
	struct Zint{
		int x,z;
		Zint(){}
		Zint(int _x){x=_x?_x:1,z=_x?0:1;}
		Zint(int _x,int _z){*this=Zint(_x),z+=_z;}
		inline Zint friend operator +(Zint a,Zint b){
			if(a.z>b.z) return b;
			else if(a.z<b.z) return a;
			else return Zint(Add(a.x,b.x),a.z);
		}
		inline Zint friend operator -(Zint a){return Zint(Sub(0,a.x),a.z);}
		inline Zint friend operator -(Zint a,Zint b){return a+(-b);}
		inline Zint friend operator *(Zint a,Zint b){return Zint(Mul(a.x,b.x),a.z+b.z);}
		inline Zint friend operator /(Zint a,Zint b){return Zint(Mul(a.x,Inv(b.x)),a.z-b.z);}
		inline int Val(){return assert(z>=0),!z?x:0;}
	};

	int fa[N],to[N];
	inline void Init(int lim){iota(fa+1,fa+lim+1,1);}
	inline int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
	inline void Merge(int x,int y){fa[Find(y)]=Find(x);}
	
	Zint f[N];
	inline void Solve(){
		Init(n);
		int ans=0;
		for(int u=1;u<=n;u++){
			f[u]=Zint(1);
			for(int v:e[u]){
				if(v>u) continue ;
				Zint tmp(1);
				for(int r=Find(v);to[r];r=Find(r)){
					tmp=tmp*(f[r])/(f[r]+Zint(1));
					Merge(to[r],r);
				}
				f[Find(v)]=f[Find(v)]*tmp;
				f[u]=f[u]*(f[Find(v)]+Zint(1));
				to[Find(v)]=u;
			}
			AddAs(ans,f[u].Val());
		}
		cout<<ans<<endl;
	}
}

namespace Case2{
	struct Node{
		int lc,rc,tag;
		array<int,2> dat;
	}tr[N<<6];
	#define lc(x) tr[x].lc
	#define rc(x) tr[x].rc
	#define tag(x) tr[x].tag
	#define dat(x) tr[x].dat

	int trs[N<<6],cnt,tot;
	inline int Allc(int len){
		int x=tot?trs[tot--]:cnt++;
		tag(x)=0,dat(x)={0,len};
		return x;
	}
	inline void DeAllc(int x){
		trs[++tot]=x;
		lc(x)=rc(x)=tag(x)=0;
		dat(x)={0,0};
	}
	inline array<int,2> Calc(array<int,2> a,array<int,2> b){
		if(a[0]^b[0]) return min(a,b);
		else return {a[0],a[1]+b[1]};
	}
	inline void PushUp(int x,int L,int R){
		if(lc(x)) dat(x)=Calc(dat(lc(x)),dat(rc(x)));
		else dat(x)={0,R-L+1};
		dat(x)[0]+=tag(x);
	}
	inline void Push(int x,int k){dat(x)[0]+=k,tag(x)+=k;}
	inline void Modify(int &x,int L,int R,int l,int r,int k){
		if(!x) x=Allc(R-L+1);
		if(l<=L&&R<=r) return Push(x,k);
		int mid=L+R>>1;
		if(l<=mid) Modify(lc(x),L,mid,l,r,k);
		if(r>mid) Modify(rc(x),mid+1,R,l,r,k);
		PushUp(x,L,R);
	}
	inline array<int,2> Query(int x,int L,int R,int l,int r){
		if(!x) return {0,min(R,r)-max(L,r)+1};
		if(l<=L&&R<=r) return dat(x);
		int mid=L+R>>1;
		array<int,2> res;
		if(r<=mid) res=Query(lc(x),L,mid,l,r);
		else if(l>mid) res=Query(rc(x),mid+1,R,l,r);
		else res=Calc(Query(lc(x),L,mid,l,r),Query(rc(x),mid+1,R,l,r));
		res[0]+=tag(x);
		return res;
	}
	inline void Merge(int &x,int &y,int L,int R){
		if(!x||!y) return x=x|y,void();
		if(L==R){
			tag(x)+=tag(y);
			PushUp(x,L,R);
			DeAllc(y);
		}
		int mid=L+R>>1;
		Merge(lc(x),lc(y),L,mid),Merge(rc(x),rc(y),mid+1,R);
		PushUp(x,L,R);
		DeAllc(y);
	}

	int f[N];
	vector<int> t0[N],t1[N];
	inline void Init(int lim){iota(f+1,f+lim+1,1);}
	inline int Find(int x){return x==f[x]?x:f[x]=Find(f[x]);}
	inline void Merge(int x,int y){f[Find(y)]=Find(x);}
	inline void GetT0(){
		Init(n);
		for(int i=1;i<=n;i++){
			for(int j:e[i]){
				if(j>i) continue ;
				t0[i].push_back(Find(j));
				Merge(i,Find(j));
				cout<<" T0 : "<<i<<" -> "<<j<<endl;
			}
		}
	}
	inline void GetT1(){
		Init(n);
		for(int i=n;i>=1;i--){
			for(int j:e[i]){
				if(j<i) continue ;
				t1[i].push_back(Find(j));
				Merge(i,Find(j));
				cout<<" T1 : "<<i<<" -> "<<j<<endl;
			}
		}
	}
	int fa[N],dep[N],siz[N],hson[N];
	inline void GetHSon(int x){
		siz[x]=1;
		for(int y:t1[x]){
			fa[y]=x;
			dep[y]=dep[x]+1;
			GetHSon(y);
			siz[x]+=siz[y];
			if(!hson[x]||siz[y]>siz[hson[x]]) hson[x]=y;
		}
	}
	int dfn[N],top[N],dcnt;
	inline void GetTop(int x,int t){
		top[x]=t;
		dfn[x]=++dcnt;
		if(hson[x]) GetTop(hson[x],t);
		for(int y:t1[x]){
			if(y==hson[x]) continue ;
			GetTop(y,y);
		}
	}

	int root[N],ans;
	vector<array<int,2>> mdf[N];
	inline void AddToRoot(int &root,int x,int k){
		cout<<x<<" += "<<k<<endl;
		while(x){
			Modify(root,1,n,dfn[top[x]],dfn[x],k);
			x=fa[top[x]];
		}
	}
	inline array<int,2> QueryToRoot(int root,int x){
		array<int,2> res={INT_MAX,0};
		while(x){
			res=Calc(res,Query(root,1,n,dfn[top[x]],dfn[x]));
			x=fa[top[x]];
		}
		return res;
	}
	inline void Work(int x){
		cout<<" Beg "<<x<<endl;
		Modify(root[x],1,n,dfn[x],dfn[x],-1);
		for(auto t:mdf[x]) AddToRoot(root[x],t[0],t[1]);
		for(int y:t0[x]){
			Work(y);
			Merge(root[x],root[y],1,n);
		}
		array<int,2> res=QueryToRoot(root[x],x);
		cout<<x<<" End "<<endl;
		if(res[0]==1) AddAs(ans,res[1]);
		cout<<" : ";for(int i=1;i<=n;i++) cout<<Query(root[x],1,n,dfn[i],dfn[i])[0]<<' ';cout<<endl;
	}

	inline void Solve(){
		GetT0(),GetT1();
		GetHSon(1),GetTop(1,1);
		for(int i=1;i<=n;i++){
			mdf[i].push_back({i,2});
			for(int j:t0[i]) mdf[i].push_back({j,-1});
			for(int j:t1[i]) mdf[j].push_back({i,-1});
		}
		Work(n);
		cout<<ans<<endl;
	}
}

signed main(){
	cin>>typ>>n;
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}

	if(typ==1) Case1::Solve();
	else Case2::Solve();

	return 0;
}