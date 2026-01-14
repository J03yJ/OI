#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>

#define endl '\n'
using namespace std;

using bint=__int128;
using uint=unsigned;

const int N=1e5+9;

int n,q;
uint a[N];
bint s1[N],s2[N],s3[N];
mt19937 rng(4649);

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];

	__gnu_pbds::gp_hash_table<int,uint> h;
	for(int i=1;i<=n;i++){
		if(!h[a[i]]) h[a[i]]=rng();
		a[i]=h[a[i]];
		s1[i]=s1[i-1]+bint(a[i]);
		s2[i]=s2[i-1]+bint(a[i])*a[i];
		s3[i]=s3[i-1]+bint(a[i])*a[i]*a[i];
	}

	while(q--){
		int l1,r1,l2,r2;
		cin>>l1>>r1>>l2>>r2;
		
		bint d1=(s1[r1]-s1[l1-1])-(s1[r2]-s1[l2-1]);
		bint d2=(s2[r1]-s2[l1-1])-(s2[r2]-s2[l2-1]);
		bint d3=(s3[r1]-s3[l1-1])-(s3[r2]-s3[l2-1]);
		if(d1<0) d1=-d1,d2=-d2,d3=-d3;

		bint x=d2-d1*d1;
		if(x<0||!d1||x%(2*d1)) cout<<"NE"<<endl;
		else{
			x/=2*d1;
			bint y=x+d1;
			if(d3!=y*y*y-x*x*x) cout<<"NE"<<endl;
			else cout<<"DA"<<endl;
		}
	}
	
	return 0;
}