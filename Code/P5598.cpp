#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
using bint=__int128;
const int N=5e5+9;

int nxt[N],n,mod;
ll a[N];
vector<int> c[N],p[N];

using ll=long long;

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

int fac[N],ifac[N];
inline void Init(int lim){
	fac[0]=1;
	for(int i=1;i<=lim;i++) fac[i]=Mul(fac[i-1],i);
	ifac[lim]=Inv(fac[lim]);
	for(int i=lim-1;~i;i--) ifac[i]=Mul(ifac[i+1],i+1);
}
inline int C(int n,int m){
	if(m<0||m>n) return 0;
	else return Mul(fac[n],Mul(ifac[m],ifac[n-m]));
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>mod;
	for(int i=1;i<=n;i++) cin>>a[i];
	
	Init(mod-1);
	for(int i=1;i<=n;i++){
		ll x=a[i];
		while(x) c[i].push_back(x%mod),x/=mod;
		for(int j=0;j<c[i].size();j++) if(c[i][j]) p[i].push_back(j);
	}

	nxt[n+1]=n+1;
	for(int i=n;i>=1;i--) nxt[i]=a[i+1]?i+1:nxt[i+1];
	
	ll ans=0;
	for(int i=1;i<=n;i++){
		int tmp=1;
		vector<int> t(60,0);
		for(int j=i;j<=n;j=nxt[j]){
			for(int k:p[j]){
				t[k]+=c[j][k];
				MulAs(tmp,C(t[k],c[j][k]));
			}
			ans+=1ll*(nxt[j]-j)*tmp;
			if(!tmp) break ;
		}
	}

	cout<<ans<<endl;

	return 0;
}