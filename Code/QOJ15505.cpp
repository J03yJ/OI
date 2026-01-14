#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=2e5+9;

int op[N],m,q;
vector<int> ar[N];

vector<pair<int&,int>> rcll;
int fa[N],siz[N],pl[N],pr[N],ext[N],now[N];
inline void Init(){for(int i=1;i<=m;i++) fa[i]=pl[i]=pr[i]=i,siz[i]=1,ext[i]=0;}
inline int Find(int x){return fa[x]==x?x:Find(fa[x]);}
inline void Record(int &x){rcll.push_back({x,x});}
inline void Recall(int prv){
	while(rcll.size()>prv){
		rcll.back().first=rcll.back().second;
		rcll.pop_back();
	}
}
vector<int> tmp;
vector<pair<int,int>> ncll;
inline void Necord(int i){ncll.push_back({i,now[i]});}
inline void Necall(int prv){
	while(ncll.size()>prv){
		tmp.push_back(ncll.back().first);
		now[ncll.back().first]=ncll.back().second;
		ncll.pop_back();
	}
}
inline void Merge(int x,int y){
	x=Find(x),y=Find(y);
	if(x==y){
		if(!ext[x]){
			Record(ext[x]),Record(pl[x]),Necord(pr[x]);
			tmp.push_back(pr[x]);
			ext[x]=1,pl[x]=0,now[pr[x]]=pl[x];
		}
	}else{
		if(siz[x]<siz[y]) swap(x,y);
		Record(fa[y]),Record(siz[x]),Record(pl[x]),Record(pr[x]),Record(ext[x]);
		Necord(pr[x]),Necord(pr[y]);
		tmp.push_back(pr[x]);
		tmp.push_back(pr[y]);
		now[pr[x]]=now[pr[y]]=0;
		fa[y]=x;
		siz[x]+=siz[y];
		pl[x]=min(pl[x],pl[y]);
		pr[x]=max(pr[x],pr[y]);
		ext[x]|=ext[y];
		if(ext[x]) pl[x]=0;
		now[pr[x]]=pl[x];
	}
}

vector<array<int,2>> e[N<<2],upd[N];
int eu[N],ev[N],lst[N],id[N],st[N],ed[N],n;
inline void Insert(int x,int L,int R,int l,int r,int u,int v){
	if(l<=L&&R<=r) return e[x].push_back({u,v});
	int mid=L+R>>1;
	if(l<=mid) Insert(x<<1,L,mid,l,r,u,v);
	if(r>mid) Insert(x<<1|1,mid+1,R,l,r,u,v);
}
inline void Conquer(int x,int L,int R){
	int dprv=rcll.size(),nprv=ncll.size();
	for(auto p:e[x]) Merge(p[0],p[1]);
	if(L==R){
		for(int i:tmp){
			if(lst[i]==now[i]) continue ;
			upd[L].push_back({i,now[i]});
			lst[i]=now[i];
		}
		tmp.clear();
	}else{
		int mid=L+R>>1;
		Conquer(x<<1,L,mid);
		Conquer(x<<1|1,mid+1,R);
	}
	Recall(dprv),Necall(nprv);
}

struct Node{
	int l,r;
	ll mx,sum;
	inline int Len(){return r-l+1;}
}tr[N<<2];

inline ll Calc(int x,ll k){
	if(k>=tr[x].mx) return k*tr[x].Len();
	if(tr[x].l==tr[x].r) return tr[x].mx;
	if(k<tr[x<<1].mx) return Calc(x<<1,k)+tr[x].sum-tr[x<<1].sum;
	else return k*tr[x<<1].Len()+Calc(x<<1|1,k);
}
inline void PushUp(int x){
	tr[x].mx=max(tr[x<<1].mx,tr[x<<1|1].mx);
	tr[x].sum=tr[x<<1].sum+Calc(x<<1|1,tr[x<<1].mx);
}

inline void Build(int x,int l,int r){
	tr[x].l=l,tr[x].r=r;
	if(tr[x].l==tr[x].r) return tr[x].mx=tr[x].sum=l,void();
	int mid=tr[x].l+tr[x].r>>1;
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	PushUp(x);
}
inline void Modify(int x,int pos,ll k){
	if(tr[x].l==tr[x].r) return tr[x].mx=tr[x].sum=k,void();
	int mid=tr[x].l+tr[x].r>>1;
	if(pos<=mid) Modify(x<<1,pos,k);
	else Modify(x<<1|1,pos,k);
	PushUp(x);
}
inline array<ll,2> Query(int x,int l,int r,ll k){
	if(l>r) return {0,0};
	if(l<=tr[x].l&&tr[x].r<=r) return {Calc(x,k),max(k,tr[x].mx)};
	int mid=tr[x].l+tr[x].r>>1;
	if(r<=mid) return Query(x<<1,l,r,k);
	else if(l>mid) return Query(x<<1|1,l,r,k);
	else{
		auto lv=Query(x<<1,l,r,k);
		auto rv=Query(x<<1|1,l,r,lv[1]);
		return {lv[0]+rv[0],rv[1]};
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>m>>q;
	for(int i=1;i<=q;i++){
		cin>>op[i];
		if(op[i]==1) ar[i].resize(2);
		else if(op[i]==2) ar[i].resize(1);
		else ar[i].resize(4);
		for(int &x:ar[i]) cin>>x;
	}

	for(int i=1;i<=q;i++){
		if(op[i]==1){
			n++;
			eu[n]=ar[i][0];
			ev[n]=ar[i][1];
			id[i]=n;
			st[id[i]]=i;
			ed[id[i]]=q;
		}else if(op[i]==2){
			id[i]=ar[i][0];
			ed[id[i]]=i-1;
		}
	}
	Init();
	for(int i=1;i<=n;i++) Insert(1,1,q,st[i],ed[i],eu[i],ev[i]);
	for(int i=1;i<=m;i++) lst[i]=now[i]=i;
	Conquer(1,1,q);
	
	Build(1,1,m);
	for(int i=1;i<=q;i++){
		if(op[i]==3){
			ll ans=0;
			int mnl=ar[i][0],mxl=ar[i][1],mnr=ar[i][2],mxr=ar[i][3];
			mxl=min(mxl,mxr),mnr=max(mnr,mnl);
			if(mnl>mxl||mnr>mxr){
				cout<<0<<endl;
				continue ;
			}
			ans=1ll*(mxl-mnl+1)*(mxr-mnr+1);
			int len=max(0,(min(mxl,mxr)-max(mnl,mnr)+1));
			ans-=1ll*len*(len-1)/2;
			ans-=Query(1,1,mxr,mnl-1)[0]-1ll*mxr*(mnl-1);
			ans+=Query(1,1,mnr-1,mnl-1)[0]-1ll*(mnr-1)*(mnl-1);
			ans+=Query(1,1,mxr,mxl)[0]-1ll*mxr*mxl;
			ans-=Query(1,1,mnr-1,mxl)[0]-1ll*(mnr-1)*mxl;
			cout<<ans<<endl;
		}else for(auto p:upd[i]) Modify(1,p[0],p[1]);
	}

	return 0;
}