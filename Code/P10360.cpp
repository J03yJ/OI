#include<bits/stdc++.h>

using namespace std;

const int N=3e2+9;
const int M=1e3+9;

int a[M],b[M],p[N],ans[N],n,m;
inline void DFS(int d){
	if(d>m){
		int cnt=count(p+1,p+n+1,1);
		for(int i=1;i<=n;i++){
			for(int j=i,cur=0;j<=n;j++){
				if(!p[j]) break ;
				if(p[j]==1) cur++;
				if(cur==cnt) ans[j-i+1]^=1;
			}
		}
		return ;
	}
	if(~p[a[d]]&&~p[b[d]]){
		if(p[a[d]]>p[b[d]]){
			swap(p[a[d]],p[b[d]]);
			DFS(d+1);
			swap(p[a[d]],p[b[d]]);
		}else DFS(d+1);
	}else if(~p[b[d]]){
		if(!p[b[d]]){
			swap(p[a[d]],p[b[d]]);
			DFS(d+1);
			swap(p[a[d]],p[b[d]]);
		}else DFS(d+1);
	}else if(~p[a[d]]){
		if(p[a[d]]){
			swap(p[a[d]],p[b[d]]);
			DFS(d+1);
			swap(p[a[d]],p[b[d]]);
		}else DFS(d+1);
	}else{
		p[a[d]]=p[b[d]]=0;
		DFS(d+1);
		p[a[d]]=p[b[d]]=1;
		DFS(d+1);
		p[a[d]]=p[b[d]]=-1;
	}
}

signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++) cin>>a[i]>>b[i];

	fill(p+1,p+n+1,-1);
	DFS(1);

	for(int i=1;i<=n;i++) cout<<ans[i]<<' ';cout<<endl;

	return 0;
}