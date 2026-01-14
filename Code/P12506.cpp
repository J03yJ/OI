#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=1e5+9;

int x[N],y[N],fa[N<<1],r,n;
inline void Init(int lim){iota(fa+1,fa+lim+1,1);}
inline int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
inline void Merge(int x,int y){fa[Find(y)]=Find(x);}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>r;
	for(int i=1;i<=n;i++) cin>>x[i]>>y[i];

	Init(n<<1|1);
	int b=sqrt(0.5l)*r;
	map<array<int,2>,vector<int>> mp;
	for(int i=1;i<=n;i++) mp[{x[i]/b,y[i]/b}].push_back(i);
	for(auto t:mp){
		vector<int> p=t.second;
		int ix=t.first[0],iy=t.first[1];
		if(p.size()>2) for(int i:p) Merge(i<<1,i<<1|1);
		else{
			if(p.size()==2){
				Merge(p.front()<<1,p.back()<<1|1);
				Merge(p.front()<<1|1,p.back()<<1);
			}
			for(int stp=1;stp<=3;stp++){
				for(int dx=-stp;dx<=stp;dx++){
					int lft=stp-abs(dx);
					for(int dy:{-lft,lft}){
						if(!mp.count({ix+dx,iy+dy})) continue ;
						vector<int> q=mp[{ix+dx,iy+dy}];
						for(int i:p){
							for(int j:q){
								if(hypotl(x[i]-x[j],y[i]-y[j])>r) continue ;
								Merge(i<<1,j<<1|1);
								Merge(i<<1|1,j<<1);
							}
						}
						if(!lft) break ;
					}
				}
			}
		}
	}

	for(int i=1;i<=n;i++) cout<<(Find(i<<1)==Find(i<<1|1));cout<<endl;

	return 0;
}