#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;

#define endl '\n'
using ll=long long;
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
#define Inv(x) QPow(x,mod-2)

int fac[N<<1],ifac[N<<1];
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

inline int G(int n,int m,int x){
	int ans=0;
	for(int i=0;i<=m/(x+1);i++){
		if(~i&1) AddAs(ans,Mul(C(n,i),C(m+n-i*(x+1)-1,n-1)));
		else SubAs(ans,Mul(C(n,i),C(m+n-i*(x+1)-1,n-1)));
	}
	return ans;
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	Init(4e5);

	int T;
	cin>>T;
	while(T--){
		int n,m;
		cin>>n>>m;

		int ans=0;
		for(int x=0;x<=m;x++){
			int g1=G(n-1,m-x,x),g2=G(n-2,m-2*x,x);
			AddAs(ans,Mul(x,g1));
			AddAs(ans,Mul(n-1,Mul(x,g2)));
			SubAs(ans,Mul(Mul(m-x,Inv(n-1)),g1));
			SubAs(ans,Mul(m-2*x,g2));
			SubAs(ans,Mul(x,g2));
		}

		cout<<ans<<endl;
	}

	return 0;
}