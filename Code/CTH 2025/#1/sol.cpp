#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=3e3+9;

int ban[N][N],n,m;
char a[N][N],lu[N][N],rd[N][N];
inline bool Valid(char c[N][N],int i,int j){return c[i][j]!='*'&&c[i][j];}
template<class T> inline int Merge(vector<T> u,vector<T> v){
	int cnt=0;
	while(u.size()){
		while(v.size()&&v.back()>u.back()) v.pop_back();
		if(v.size()&&v.back()==u.back()) cnt+=!ban[v.back()[0]][v.back()[1]];
		u.pop_back();
	}
	return cnt;
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) cin>>a[i][j];
	}

	int cnt=0;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cnt+=(a[i][j]=='.');
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]=='*') lu[i][j]='*';
			else if(i==1&&j==1) lu[i][j]='.';
			else if(Valid(lu,i,j-1)||Valid(lu,i-1,j)) lu[i][j]='~';
			else lu[i][j]='*';
		}
	}
	for(int i=n;i>=1;i--){
		for(int j=m;j>=1;j--){
			if(a[i][j]=='*') ;
			else if(i==n&&j==m) rd[i][j]='.';
			else if(Valid(rd,i,j+1)||Valid(rd,i+1,j)) rd[i][j]='~';
			else rd[i][j]='*';
		}
	}

	if(!Valid(rd,1,1)){
		cout<<1ll*cnt*(cnt-1)/2<<endl;
		return 0;
	}

	vector<array<int,2>> rp;
	for(int i=1,j=1;;){
		rp.push_back({i,j});
		if(rd[i][j]=='.') break ;
		else if(Valid(rd,i,j+1)) j++;
		else if(Valid(rd,i+1,j)) i++;
	}

	ll ans=0,c=0;
	for(int i=1,j=1;;){
		int k=1;
		while(i-k>=1&&j+k<=m&&(!Valid(lu,i-k,j+k)||!Valid(rd,i-k,j+k))) k++;
		if(i-k<1||j+k>m) ans+=cnt-c-1;
		else{
			vector<array<int,2>> lp;
			for(int p=i-k,q=j+k;;){
				lp.push_back({p,q});
				if(lu[p][q]=='.') break ;
				else if(Valid(lu,p,q-1)) q--;
				else if(Valid(lu,p-1,q)) p--;
			}
			reverse(lp.begin(),lp.end());
			lp.pop_back();
			for(int p=i-k,q=j+k;;){
				lp.push_back({p,q});
				if(rd[p][q]=='.') break ;
				else if(Valid(rd,p+1,q)) p++;
				else if(Valid(rd,p,q+1)) q++;
			}
			ans+=Merge(lp,rp);
		}
		c++;
		ban[i][j]=1;
		if(rd[i][j]=='.') break ;
		else if(Valid(rd,i+1,j)) i++;
		else if(Valid(rd,i,j+1)) j++;
	}
	
	cout<<ans<<endl;

	return 0;
}