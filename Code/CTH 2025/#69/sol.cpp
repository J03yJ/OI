#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=3e5+9;

int a[N],c[N],n,m;

inline void Solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];

	vector<int> val(a,a+n+1);
	sort(val.begin(),val.end());
	val.erase(unique(val.begin(),val.end()),val.end());
	m=val.size()-1;

	for(int i=1;i<=n;i++){
		c[lower_bound(val.begin(),val.end(),a[i])-val.begin()]++;
	}
	
	int ans=n-m+1,sum=0;
	priority_queue<int> q;
	for(int i=m;i>=1;i--){
		q.push(c[i]+1),sum+=c[i]+1,ans++;
		if(sum>=m-i+1) sum-=q.top(),ans--,q.pop();
		c[i]=0;
	}

	cout<<ans<<endl;
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}