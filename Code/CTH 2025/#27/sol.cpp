#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=(1<<18)+9;

int n;
ll a[N];
__gnu_pbds::gp_hash_table<ll,ll> b;
inline void Construct(vector<ll> v,int d){
	if(d<0||!v.size()) return ;
	vector<ll> s[2];
	for(ll x:v) s[x>>d&1].push_back(x);
	Construct(s[0],d-1);
	Construct(s[1],d-1);
	for(ll x:s[1]){
		swap(b[x],b[x^(1ll<<d)]);
		b[x^(1ll<<d)]|=1ll<<d;
	}
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],b[a[i]]=0;

	Construct(vector<ll>(a+1,a+n+1),60);

	for(int i=1;i<=n;i++) cout<<b[a[i]]<<endl;

	return 0;
}