#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e4+9;

int a[N],n;
vector<vector<int>> ans;

inline void Solve(int l,int r,int s){
	if(l==r) return ;
	int mid=l+r>>1;
	vector<array<int,2>> cur({{a[l]>mid,1}});
	for(int i=l+1;i<=r;i++){
		if((a[i]>mid)==(a[i-1]>mid)) cur.back()[1]++;
		else cur.push_back({!cur.back()[0],1});
	}
	while(cur.size()>2||cur.front()[0]){
		vector<int> tmp;
		vector<array<int,2>> nxt;
		int f=!cur.front()[0];
		for(int i=0;i<cur.size();i++){
			if(i%3==(f+2)%3){
				tmp.push_back(cur[i][1]);
				nxt.push_back(cur[i]);
			}else if(i%3==f){
				if(i+1<cur.size()){
					tmp.push_back(cur[i][1]+cur[i+1][1]);
					nxt.push_back(cur[i+1]);
					nxt.push_back(cur[i]);
				}else{
					tmp.push_back(cur[i][1]);
					nxt.push_back(cur[i]);
				}
			}
		}
		cur.clear();
		for(auto p:nxt){
			if(!cur.size()||cur.back()[0]!=p[0]) cur.push_back(p);
			else cur.back()[1]+=p[1];
		}
		if(s>=ans.size()) ans.resize(ans.size()+1);
		int T=l-1-accumulate(ans[s].begin(),ans[s].end(),0);
		while(T--) ans[s].push_back(1);
		ans[s].insert(ans[s].end(),tmp.begin(),tmp.end());
		int st=l;
		for(int x:tmp){
			reverse(a+st,a+st+x);
			st+=x;
		}
		s++;
	}
	Solve(l,mid,s);
	Solve(mid+1,r,s);
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);
	
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];

	Solve(1,n,0);

	for(auto &v:ans){
		int T=n-accumulate(v.begin(),v.end(),0);
		while(T--) v.push_back(1);
	}
	if(ans.size()&1) ans.push_back(vector<int>(n,1));
	for(int i=1;i<ans.size();i+=2) reverse(ans[i].begin(),ans[i].end());

	vector<int> tmp;
	for(int i=ans.size();i--;) if(ans[i].size()==1) tmp.push_back(i);
	for(int i:tmp) ans.erase(ans.begin()+i);

	cout<<ans.size()<<endl;
	for(auto &v:ans){
		cout<<v.size()<<' ';
		for(int x:v) cout<<x<<' ';
		cout<<endl;
	}

	return 0;
}