#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=2e5+9;
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

int a[N],c[N],n,m;
vector<int> e[N];
inline int DFS(int x,vector<int> &v){
	bool flag=0;
	v.push_back(x);
	for(int y:e[x]){
		if(!c[y]){
			c[y]=-c[x];
			flag|=DFS(y,v);
		}else if(c[y]==c[x]) flag|=1;
	}
	return flag;
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1,u,v;i<=m;i++){
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}

	Init(n);
	int res=1;
	for(int i=1;i<=n;i++){
		if(c[i]) continue ;
		vector<int> v;
		c[i]=1;
		if(DFS(i,v)) MulAs(res,QPow(2,v.size()-1));
		else{
			int cnt=0;
			for(int x:v) cnt+=a[x]^(c[x]>0);
			MulAs(res,C(v.size(),cnt));
		}
	}

	cout<<res<<endl;

	return 0;
}