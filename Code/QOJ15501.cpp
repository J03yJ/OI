#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=5e5+9;

ll su[N][2],ans[N];
char s[N],t[N];
int c[N],ddl[N],ql[N],qr[N],n,q;
vector<int> qry[N<<1];

struct Fenw{
	ll tr[N];
	inline void Add(int x,ll k){while(x<=n) tr[x]+=k,x+=x&-x;}
	inline ll Ask(int x){ll sum=0;while(x) sum+=tr[x],x&=x-1;return sum;}
	inline ll Ask(int l,int r){return Ask(r)-Ask(l-1);}
	inline void Clear(){for(int i=1;i<=n;i++) tr[i]=0;}
}k,b;

set<array<int,2>> seg;
priority_queue<array<int,2>> cnd;
inline void Insert(int l,int r){
	seg.insert({l,r});
	ll f=su[r][r&1]-su[l-1][r&1],g=su[r][~r&1]-su[l-1][~r&1];
	// cerr<<l<<" ~ "<<r<<" = "<<f<<' '<<g<<endl;
	if(g-f+1<=n) cnd.push({-(ddl[l]=g-f+1),l});
}
inline void Update(int l){
	auto it=seg.lower_bound({l,0});
	int r=(*it)[1],flag=1;
	ddl[l]=-1e9;
	k.Add(l+1,-(r-l)/2);
	b.Add(l+1,-(su[r][~r&1]-su[l-1][~r&1]));
	cerr<<"! "<<l<<' '<<r<<endl;
	if(next(it)!=seg.end()){
		auto jt=next(it);
		int jl=(*jt)[0],jr=(*jt)[1];
		seg.erase(jt);
		ddl[jl]=-1e9;
		k.Add(jl+1,-(jr-jl)/2);
		b.Add(jl+1,-(su[jr][~jr&1]-su[jl-1][~jr&1]));
		r=jr;
	}else flag=0;
	if(it!=seg.begin()){
		auto jt=prev(it);
		int jl=(*jt)[0],jr=(*jt)[1];
		seg.erase(jt);
		ddl[jl]=-1e9;
		k.Add(jl+1,-(jr-jl)/2);
		b.Add(jl+1,-(su[jr][~jr&1]-su[jl-1][~jr&1]));
		l=jl;
	}else flag=0;
	seg.erase(it);
	cerr<<"! "<<l<<' '<<r<<' '<<flag<<endl;
	if(flag){
		Insert(l,r);
		k.Add(l+1,(r-l)/2);
		b.Add(l+1,su[r][~r&1]-su[l-1][~r&1]);
	}else if((l^r)&1){
		k.Add(l+1,(r-l+1)/2);
		b.Add(l+1,max(su[r][0]-su[l-1][0],su[r][1]-su[l-1][1]));
	}else{
		k.Add(l+1,(r-l)/2+1);
		b.Add(l+1,su[r][r&1]-su[l-1][r&1]);
	}
}

signed main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>s[i];
	for(int i=1;i<=n;i++) cin>>t[i];
	
	for(int i=1;i<=n;i++) c[i]=c[i-1]+(s[i]-t[i])/* ,cout<<i<<" : "<<c[i]<<endl */;
	for(int i=1;i<=n;i++){
		for(int k:{0,1}) su[i][k]=su[i-1][k];
		su[i][i&1]+=c[i];
	}

	for(int i=1;i<=q;i++){
		cin>>ql[i]>>qr[i];
		if(qr[i]-ql[i]+1<3) ans[i]=-int(string(s+ql[i],s+qr[i]+1)!=string(t+ql[i],t+qr[i]+1));
		else if(c[ql[i]-1]==c[qr[i]]) qry[-c[ql[i]-1]+N].push_back(i);
		else ans[i]=-1;
	}
	
	for(int i=1;i<=n;i++) cerr<<c[i]<<' ';cerr<<endl;
	for(int o:{0,1}){
		for(int i=1;i<=n;i++) Insert(i,i);
		for(int i=-n;i<=n;i++){
			while(cnd.size()&&-cnd.top()[0]<=i){
				int j=cnd.top()[1],x=-cnd.top()[0];
				cnd.pop();
				if(ddl[j]!=x) continue ;
				cerr<<i<<' '<<j<<' '<<x<<endl;
				Update(j);
			}
			for(int j:qry[i+N]){
				cerr<<j<<" @ "<<i<<endl;
				ans[j]+=k.Ask(ql[j],qr[j])*i+b.Ask(ql[j],qr[j]);
			}
			cerr<<"# "<<i<<" = ";
			for(int j=1;j<=n;j++) cerr<<k.Ask(j,j)<<'/'<<b.Ask(j,j)<<' ';cerr<<endl;
		}
		k.Clear();
		b.Clear();
		seg.clear();
		while(cnd.size()) cnd.pop();
		for(int i=1;i<=n;i++){
			c[i]=-c[i];
			for(int k:{0,1}) su[i][k]=-su[i][k];
			qry[i+N].swap(qry[-i+N]);
		}
		for(int i=1;i<=q;i++) cerr<<ans[i]<<' ';cerr<<endl;
	}

	for(int i=1;i<=q;i++) cout<<ans[i]<<endl;

	return 0;
}