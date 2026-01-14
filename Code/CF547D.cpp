#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=4e5+9;
const int M=N<<1;
const int V=2e5;

int fi[M],d[M],ne[M<<1],to[M<<1],adj=1;
inline void AddEdge(int x,int y){
	ne[++adj]=fi[x];
	fi[x]=adj;
	to[adj]=y;
	d[x]++;
}

int a[N],b[N],n;
bool vis[M],op[M];
inline void DFS(int x){
	for(int &i=fi[x];i;i=ne[i]){
		if(vis[i>>1]) continue ;
		vis[i>>1]=1;
		op[i>>1]=i&1;
		DFS(to[i]);
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i]>>b[i];

	for(int i=1;i<=n;i++){
		AddEdge(a[i],b[i]+V);
		AddEdge(b[i]+V,a[i]);
	}
	for(int i=1;i<=(V<<1);i++){
		if(d[i]&1){
			AddEdge(0,i);
			AddEdge(i,0);
		}
	}
	for(int i=1;i<=(V<<1);i++) DFS(i);

	for(int i=1;i<=n;i++) cout<<(op[i]?'b':'r');
	cout<<endl;
	
	return 0;
}