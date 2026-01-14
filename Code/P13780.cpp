#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=1e6+9;

int a[N],ans[N],n,q;
vector<int> c[N];
vector<array<int,2>> seg[N],opt[N],qry[N];

struct Node{
	int lc,rc,dat;
}tr[N*32];
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc
#define dat(x) tr[x].dat

int root[N],cnt;
inline int Allc(){return ++cnt;}
inline int Clone(int x){int y=Allc();tr[y]=tr[x];return y;}
inline void Clear(){while(cnt) memset(&tr[cnt--],0,sizeof Node());}
inline void PushUp(int x){dat(x)=min(dat(lc(x)),dat(rc(x)));}
inline void Build(int &x,int L,int R){
	x=Allc();
	if(L==R) return dat(x)=0,void();
	int mid=L+R>>1;
	Build(lc(x),L,mid),Build(rc(x),mid+1,R);
	PushUp(x);
}
inline void Set(int &x,int L,int R,int pos,int k,bool flag){
	if(flag) x=Clone(x);
	if(L==R) return dat(x)=max(dat(x),k),void();
	int mid=L+R>>1;
	if(pos<=mid) Set(lc(x),L,mid,pos,k,flag);
	else Set(rc(x),mid+1,R,pos,k,flag);
	PushUp(x);
}
inline int MinPos(int x,int L,int R,int lim){
	if(L==R) return L;
	int mid=L+R>>1;
	if(dat(lc(x))<lim) return MinPos(lc(x),L,mid,lim);
	else return MinPos(rc(x),mid+1,R,lim);
}
inline int Mex(int l,int r){return MinPos(root[r],1,n+2,l);}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1,l,r;i<=q;i++){
		cin>>l>>r;
		qry[r].push_back({l,i});
	}

	Build(root[0],1,n+2);
	for(int i=1;i<=n;i++) Set(root[i]=root[i-1],1,n+2,a[i],i,1);
	for(int i=1;i<=n;i++) c[a[i]].push_back(i);
	for(int i=1;i<=n;i++){
		c[i].push_back(0);
		c[i].push_back(n+1);
		sort(c[i].begin(),c[i].end());
	}

	for(int i=1;i<=n;i++){
		if(a[i]==1) seg[2].push_back({i,i});
		else seg[1].push_back({i,i});
	}
	for(int i=2;i<=n;i++){
		for(auto t:seg[i]){
			int l=t[0],r=t[1];
			int lp=*--upper_bound(c[i].begin(),c[i].end(),l);
			int rp=*lower_bound(c[i].begin(),c[i].end(),r);
			if(lp!=0) seg[Mex(lp,r)].push_back({lp,r});
			if(rp!=n+1) seg[Mex(l,rp)].push_back({l,rp});
		}
		sort(seg[i+1].begin(),seg[i+1].end(),[](auto x,auto y){return x[0]^y[0]?x[0]>y[0]:x[1]<y[1];});
		vector<array<int,2>> tmp;
		for(auto t:seg[i+1]){
			if(!tmp.size()||t[1]<tmp.back()[1]) tmp.push_back(t);
		}
		swap(seg[i+1],tmp);
	}
	for(int i=1;i<=n+1;i++) for(auto t:seg[i]) opt[t[1]].push_back({t[0],i});
	Clear();
	for(int i=1;i<=n+1;i++) seg[i].clear(),seg[i].shrink_to_fit();
	for(int i=1;i<=n;i++) c[i].clear(),c[i].shrink_to_fit();

	Build(root[0],1,n+2);
	for(int i=1;i<=n;i++){
		root[i]=root[i-1];
		for(auto t:opt[i]) Set(root[i],1,n+2,t[1],t[0],0);
		for(auto t:qry[i]) ans[t[1]]=MinPos(root[i],1,n+2,t[0]);
		opt[i].clear();
		opt[i].shrink_to_fit();
		qry[i].clear();
		qry[i].shrink_to_fit();
	}

	for(int i=1;i<=q;i++) cout<<ans[i]<<endl;

	return 0;
}