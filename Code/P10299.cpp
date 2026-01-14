#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=2e5+9;

int f[N][4],n;
ll a[2][N],s[2][N];

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n;
	for(int k:{0,1}) for(int i=1;i<=n;i++) cin>>a[k][i];

	ll sum=0;
	for(int k:{0,1}) for(int i=1;i<=n;i++) sum+=a[k][i];
	for(int k:{0,1}){
		for(int i=1;i<=n;i++){
			a[k][i]=2*n*a[k][i]-sum;
			s[k][i]=s[k][i-1]+a[k][i];
		}
	}

	map<ll,int> occ[2];
	occ[0][0]=occ[1][0]=0;
	memset(f,-0x3f,sizeof f);
	f[0][0]=0;
	for(int i=1;i<=n;i++){
		f[i][3]=*max_element(f[i-1],f[i-1]+4);
		for(int k:{0,1}){
			int p=occ[k].count(s[k][i])?occ[k][s[k][i]]:-1;
			int q=occ[k^1].count(-s[k][i])?occ[k^1][-s[k][i]]:-1;
			if(!~p&&!~q) continue ;
			int j=max(p,q);
			if(q<j) f[i][1<<k]=max(f[j][1<<k],f[j][3])+1;
			else if(p<j) f[i][1<<k]=max(f[j][1<<!k],f[j][3])+1;
			else f[i][1<<k]=f[j][0]+1;
		}
		if(s[0][i]+s[1][i]==0) f[i][0]=*max_element(f[i],f[i]+4)+1;
		occ[0][s[0][i]]=occ[1][s[1][i]]=i;
	}

	cout<<f[n][0]<<endl;

	return 0;
}