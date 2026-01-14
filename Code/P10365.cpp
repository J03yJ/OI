#include<bits/stdc++.h>

#define endl '\n'
using namespace std;

using ll=long long;
const int N=5e5+9;
const int mod=1e9+7;
const int lgN=2e1+9;

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
#define Inv(x) QPow(x,mod-2)

namespace Chth{
	struct Seg{
		int l,r,v;
		Seg(){};
		Seg(int _l,int _r,int _v){l=_l,r=_r,v=_v;}
		bool friend operator <(const Seg s,const Seg t){return s.l<t.l;}
	};
	set<Seg> s;
	inline auto Split(int p){
		auto it=s.lower_bound(Seg(p,0,0));
		if(it!=s.end()&&it->l==p) return it;
		it--;
		int l=it->l,r=it->r,v=it->v;
		s.erase(it);
		s.insert(Seg(l,p-1,v));
		return s.insert(Seg(p,r,v)).first;
	}
	inline void Assign(int l,int r,int v){
		auto rit=Split(r+1),lit=Split(l);
		s.erase(lit,rit);
		s.insert(Seg(l,r,v));
	}
	inline int Query(int p){return (--s.lower_bound(Seg(p+1,0,0)))->v;}
}
namespace Fenw{
	int tr[N<<1],lim;
	inline void Init(int _lim){lim=_lim;}
	inline void Modify(int x,int k){while(x<=lim) tr[x]+=k,x+=x&-x;}
	inline int Query(int x){int sum=0;while(x) sum+=tr[x],x&=x-1;return sum;}
	inline int Query(int l,int r){return Query(r)-Query(l-1);}
}

int lp[N],rp[N],n;
vector<tuple<int,int,int&>> opr[N];

int dep[N],lfa[N][lgN],rfa[N][lgN],dom[N][lgN],lw[N][lgN],rw[N][lgN];
inline int LCA(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int k=lgN-1;~k;k--) if(dep[dom[x][k]]>=dep[y]) x=dom[x][k];
	if(x==y) return x;
	for(int k=lgN-1;~k;k--) if(dom[x][k]!=dom[y][k]) x=dom[x][k],y=dom[y][k];
	return dom[x][0];
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n;
	for(int i=n;i>=1;i--) cin>>lp[i]>>rp[i];

	lp[0]=0,rp[0]=2*n+1;
	Chth::s.insert(Chth::Seg(0,2*n+1,0));
	for(int i=1;i<=n;i++){
		lfa[i][0]=Chth::Query(lp[i]);
		rfa[i][0]=Chth::Query(rp[i]);
		Chth::Assign(lp[i],rp[i],i);
		opr[i].push_back({lp[i]-1,1,lw[i][0]});
		opr[lfa[i][0]].push_back({lp[i]-1,-1,lw[i][0]});
		opr[i].push_back({rp[i],1,rw[i][0]});
		opr[rfa[i][0]].push_back({rp[i],-1,rw[i][0]});
		dom[i][0]=LCA(lfa[i][0],rfa[i][0]);
		dep[i]=dep[dom[i][0]]+1;
		for(int k=1;k<lgN;k++){
			dom[i][k]=dom[dom[i][k-1]][k-1];
			lfa[i][k]=lfa[lfa[i][k-1]][k-1];
			rfa[i][k]=rfa[rfa[i][k-1]][k-1];
		}
	}
	Fenw::Init(n<<1|1);
	for(int i=1;i<=n;i++){
		Fenw::Modify(rp[i],1);
		for(auto &t:opr[i]) get<2>(t)+=Fenw::Query(get<0>(t))*get<1>(t);
	}
	for(int i=1;i<=n;i++){
		for(int k=1;k<lgN;k++){
			lw[i][k]=lw[i][k-1]+lw[lfa[i][k-1]][k-1];
			rw[i][k]=rw[i][k-1]+rw[rfa[i][k-1]][k-1];
		}
	}

	int ans=0;
	for(int i=1;i<=n;i++){
		int sum=0,lx=i,rx=i;
		for(int k=lgN-1;~k;k--){
			if(lfa[lx][k]>=dom[i][0]) sum-=lw[lx][k],lx=lfa[lx][k];
			if(rfa[rx][k]>=dom[i][0]) sum+=rw[rx][k],rx=rfa[rx][k];
		}
		AddAs(ans,Inv(sum));
	}

	cout<<ans<<endl;

	return 0;
}