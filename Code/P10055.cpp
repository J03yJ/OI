#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=1e6+9;

int f[N],g[N],o[N],n,m;
char s[N];
vector<array<int,2>> b,ans;

inline void Constr(int l,int r){
	int mid=l+r>>1,pl=mid,pr=mid;
	while(b[pl][1]==1) pl--;
	while(b[pr][1]==1) pr++;
	int t=pl-l,d=(r-l-2*t)/2;
	for(int i=pr-d+1;i<=pr+d-1;i++) o[i]=1;
	vector<int> stk[2];
	for(int i=l;i<=r;i++){
		ans.push_back({1,b[i][1]});
		if(i==pl||i==pr) ans.push_back({2,b[i][1]});
		else if(pr!=mid&&i==pr-d) ;
		else if(pr!=mid&&i==pr+d){
			ans.push_back({2,b[stk[o[i]].back()][1]+b[i][1]+b[pr-d][1]});
			stk[o[i]].pop_back();
		}else if(stk[o[i]].size()&&b[stk[o[i]].back()][0]==b[i][0]){
			ans.push_back({2,b[stk[o[i]].back()][1]+b[i][1]});
			stk[o[i]].pop_back();
		}else stk[o[i]].push_back(i);
	}
}
inline void Output(){
	cout<<"Yes"<<endl;
	int i=0;
	vector<array<int,2>> res;
	for(auto t:ans){
		if(t[0]==1){
			for(int i=1;i<=t[1];i++) res.push_back({1,0});
		}else res.push_back(t);
	}
	cout<<res.size()<<endl;
	for(auto t:res){
		if(t[0]==1) cout<<t[0]<<endl;
		else cout<<t[0]<<' '<<t[1]<<endl;
	}
}

inline void Solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>s[i];

	b.push_back({0,0});
	for(int i=1;i<=n;i++){
		if(s[i]!=b.back()[0]) b.push_back({s[i],1});
		else b.back()[1]++;
	}
	m=b.size()-1;

	for(int i=1,r=0;i<=m;i++){
		if(b[i][1]>1) r=0;
		else r++;
		f[i]=max(f[i-1],r);
	}
	for(int i=m,r=0;i>=1;i--){
		if(b[i][1]>1) r=0;
		else r++;
		g[i]=max(g[i+1],r);
	}

	if(m&1){
		if(f[m]>=m/2&&b[m+1>>1][1]==1) cout<<"No"<<endl;
		else{
			Constr(1,m);
			Output();
		}
	}else{
		bool flag=0;
		for(int i=1;i<m;i++){
			if(f[i]>=i/2&&b[i+1>>1][1]==1) continue ;
			if(g[i+1]>=(m-i)/2&&b[i+m+1>>1][1]==1) continue ;
			Constr(1,i),Constr(i+1,m);
			Output();
			flag=1;
			break ;
		}
		if(!flag) cout<<"No"<<endl;
	}

	for(int i=1;i<=n;i++) f[i]=g[i]=o[i]=0;
	b.clear(),ans.clear();
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--) Solve();

	return 0;
}