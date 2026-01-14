#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=1e3+9;
const int M=1e5+9;
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

int fac[M],ifac[M],n,m;
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

int res[N];
vector<int> e[N];

int dep[N];
inline void DFS(int x,int fa){
	for(int y:e[x]){
		if(y==fa) continue ;
		dep[y]=dep[x]+1;
		DFS(y,x);
	}
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>m;
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}

	Init(m);
	for(int i=1;i<=n;i++){
		for(int j=0;j*i+1<=m;j++){
			for(int p=j*i+1;p<=m;p++){
				int tmp=QPow(n-i,p-(j*i+1));
				MulAs(tmp,QPow(n,m-p));
				MulAs(tmp,C(p-1,j*i));
				MulAs(tmp,fac[j*i]);
				MulAs(tmp,QPow(ifac[j],i));
				AddAs(res[i],tmp);
			}
		}
	}

	int ans=0;
	for(int i=1;i<=n;i++){
		dep[i]=1,DFS(i,0);
		for(int j=1;j<=n;j++) AddAs(ans,res[dep[j]]);
	}

	cout<<ans<<endl;

	return 0;
}