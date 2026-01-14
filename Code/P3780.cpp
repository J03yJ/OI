#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e4+9;

int fa[N<<1],siz[N<<1],a[N<<1],v[N<<1],lf[N<<1],n,k,tot;
int dfn[N<<1],idfn[N<<1],nfd[N<<1],infd[N<<1],dcnt,ncnt;
vector<int> e[N<<1];
int tor[N<<1];
inline void DFS(int x,int *dfn,int *idfn,int &dcnt){
	siz[x]=1;
	if(a[x]) tor[x]=tor[fa[x]]+v[x];
	for(int y:e[x]){
		if(y==fa[x]) continue ;
		DFS(y,dfn,idfn,dcnt);
		siz[x]+=siz[y];
	}
	dfn[x]=++dcnt;
	idfn[dcnt]=x;
}

vector<int> f[N<<1],g[N<<1];

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin>>T;
	while(T--){
		cin>>n>>k;
		for(int i=1;i<=n;i++) cin>>fa[i]>>a[i]>>v[i];

		tot=n<<1;
		for(int i=2;i<=n;i++) e[fa[i]].push_back(i);
		for(int i=1;i<=n;i++){
			a[i+n]=a[i]-1;
			a[i]=1;
			v[i+n]=v[i];
			lf[i]=!e[i].size();
			e[i].push_back(i+n);
			fa[i+n]=i;
		}
		DFS(1,dfn,idfn,dcnt);
		for(int i=1;i<=n;i++) reverse(e[i].begin(),e[i].end());
		DFS(1,nfd,infd,ncnt);

		auto Work=[](auto &f,int *dfn,int *idfn){
			f[0]=vector<int>(k+1,0);
			for(int i=1;i<=tot;i++){
				int x=idfn[i];
				f[i]=f[i-siz[x]];
				deque<int> q;
				for(int j=0;j<=k;j++){
					while(q.size()&&q.front()+a[x]<j) q.pop_front();
					if(q.size()){
						int k=q.front();
						f[i][j]=max(f[i][j],f[i-1][k]+(j-k)*v[x]);
					}
					while(q.size()){
						int k=q.back();
						if(f[i-1][k]+1ll*(j-k)*v[x]>f[i-1][j]) break ;
						q.pop_back();
					}
					q.push_back(j);
				}
				f[i].shrink_to_fit();
			}
		};
		Work(f,dfn,idfn);
		Work(g,nfd,infd);

		int ans=0;
		for(int i=1;i<=n;i++){
			if(!lf[i]) continue ;
			int res=0;
			for(int j=0;j<=k;j++){
				res=max(res,f[max(0,dfn[i]-1)][j]+g[max(0,nfd[i]-2)][k-j]);
			}
			ans=max(ans,res+tor[i]);
		}

		cout<<ans<<endl;

		for(int i=1;i<=tot;i++){
			e[i].clear();
			e[i].shrink_to_fit();
			f[i].clear();
			f[i].shrink_to_fit();
			g[i].clear();
			g[i].shrink_to_fit();
		}
		dcnt=ncnt=0;
	}

	return 0;
}