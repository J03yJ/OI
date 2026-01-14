#include<bits/stdc++.h>

using namespace std;

#define double long double
#define endl '\n'
const int N=1e5+9;

int op[N];
double a[N],b[N];
vector<int> mul[N],add[N],ass[N];

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	int n,m,k;
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1,j;i<=m;i++){
		cin>>op[i]>>j>>b[i];
		if(op[i]==1) ass[j].push_back(i);
		else if(op[i]==2) add[j].push_back(i);
		else if(op[i]==3) mul[j].push_back(i);
	}
	vector<int> res;
	for(int i=1;i<=n;i++){
		sort(ass[i].begin(),ass[i].end(),[](int i,int j){return b[i]<b[j];});
		if(ass[i].size()){
			add[i].push_back(ass[i].back());
			b[ass[i].back()]-=a[i];
		}
		sort(add[i].begin(),add[i].end(),[](int i,int j){return b[i]>b[j];});
		for(int j:add[i]){
			a[i]+=b[j];
			b[j]=a[i]/(a[i]-b[j]);
			mul[i].push_back(j);
		}
		res.insert(res.end(),mul[i].begin(),mul[i].end());
	}
	sort(res.begin(),res.end(),[](int i,int j){return b[i]>b[j];});
	while(res.size()&&b[res.back()]<=1) res.pop_back();
	if(res.size()>k) res.erase(res.begin()+k,res.end());
	sort(res.begin(),res.end(),[](int i,int j){return op[i]<op[j];});

	cout<<res.size()<<endl;
	for(int i:res) cout<<i<<' ';cout<<endl;

	return 0;
}