#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=3e5+9;

int a[N],nmx[N],nmn[N],t[N],n;
int qk[N],qi[N],ans[N],q;
vector<int> qry[N];

struct Node{
	int l,r;
	int rcov,atag,cov,siz,mx;
	array<int,2> val,dat;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define rcov(x) tr[x].rcov
#define atag(x) tr[x].atag
#define val(x) tr[x].val
#define dat(x) tr[x].dat
#define cov(x) tr[x].cov
#define siz(x) tr[x].siz
#define len(x) (r(x)-l(x)+1)
#define mx(x) tr[x].mx

inline void PushUp(int x){
	dat(x)=min(dat(x<<1),dat(x<<1|1));
	val(x)=min(val(x<<1),val(x<<1|1));
	siz(x)=siz(x<<1)+siz(x<<1|1);
	mx(x)=max(mx(x<<1),mx(x<<1|1));
}
inline void PushRecov(int x){rcov(x)|=1,dat(x)=val(x),atag(x)=0;}
inline void PushAdd(int x,int k){atag(x)+=k,dat(x)[0]+=k;}
inline void PushCov(int x,int k){cov(x)=k,siz(x)=k*len(x);}
inline void PushDown(int x){
	if(rcov(x)) PushRecov(x<<1),PushRecov(x<<1|1),rcov(x)=0;
	if(atag(x)) PushAdd(x<<1,atag(x)),PushAdd(x<<1|1,atag(x)),atag(x)=0;
	if(~cov(x)) PushCov(x<<1,cov(x)),PushCov(x<<1|1,cov(x)),cov(x)=-1;
}

inline void Build(int x,int l,int r){
	l(x)=l,r(x)=r,cov(x)=-1;
	if(l(x)==r(x)) return dat(x)=val(x)={t[l(x)],l(x)},mx(x)=a[l(x)],void();
	int mid=l(x)+r(x)>>1;
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	PushUp(x);
}
inline void Recover(int x,int l,int r){
	if(l<=l(x)&&r(x)<=r) return PushRecov(x);
	int mid=l(x)+r(x)>>1;
	PushDown(x);
	if(l<=mid) Recover(x<<1,l,r);
	if(r>mid) Recover(x<<1|1,l,r);
	PushUp(x);
}
inline void Add(int x,int l,int r,int k){
	if(l<=l(x)&&r(x)<=r) return PushAdd(x,k);
	int mid=l(x)+r(x)>>1;
	PushDown(x);
	if(l<=mid) Add(x<<1,l,r,k);
	if(r>mid) Add(x<<1|1,l,r,k);
	PushUp(x);
}
inline void Set(int x,int pos,int k){
	if(l(x)==r(x)) return dat(x)={k,l(x)},void();
	int mid=l(x)+r(x)>>1;
	PushDown(x);
	if(pos<=mid) Set(x<<1,pos,k);
	else Set(x<<1|1,pos,k);
	PushUp(x);
}
inline void Assign(int x,int l,int r,int k){
	if(l<=l(x)&&r(x)<=r) return PushCov(x,k);
	int mid=l(x)+r(x)>>1;
	PushDown(x);
	if(l<=mid) Assign(x<<1,l,r,k);
	if(r>mid) Assign(x<<1|1,l,r,k);
	PushUp(x);
}
inline int Find(int x,int k){
	if(l(x)==r(x)) return l(x);
	PushDown(x);
	if(k<=siz(x<<1)) return Find(x<<1,k);
	else return Find(x<<1|1,k-siz(x<<1));
}
inline int Rank(int x,int pos){
	if(l(x)==r(x)) return siz(x);
	int mid=l(x)+r(x)>>1;
	PushDown(x);
	if(pos<=mid) return Rank(x<<1,pos);
	else return siz(x<<1)+Rank(x<<1|1,pos);
}
inline int Max(int x,int l,int r){
	if(l<=l(x)&&r(x)<=r) return mx(x);
	int mid=l(x)+r(x)>>1;
	if(l<=mid&&r>mid) return max(Max(x<<1,l,r),Max(x<<1|1,l,r));
	else if(l<=mid) return Max(x<<1,l,r);
	else return Max(x<<1|1,l,r); 
}

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=q;i++) cin>>qk[i]>>qi[i],qry[qk[i]].push_back(i);

	vector<int> stk;
	for(int i=n;i>=1;i--){
		while(stk.size()&&a[stk.back()]<=a[i]) stk.pop_back();
		nmx[i]=stk.size()?stk.back():n<<1;
		stk.push_back(i);
	}
	stk.clear();
	for(int i=n;i>=1;i--){
		while(stk.size()&&a[stk.back()]>=a[i]) stk.pop_back();
		nmn[i]=stk.size()?stk.back():n<<1;
		stk.push_back(i);
	}
	for(int i=1;i<=n;i++){
		if(nmn[i]==i+1) t[i]=nmn[nmn[i]]<nmx[i]?nmn[nmn[i]]-i-1:n<<1;
		else t[i]=nmn[i]<nmx[i]?nmn[i]-i-1:n<<1;
	}

	Build(1,1,n);
	Assign(1,1,n,1);
	for(int k=1;k<=n;k++){
		for(int i:qry[n-k+1]){
			if(qi[i]<n-k+1){
				int l=Find(1,qi[i]),r=Find(1,qi[i]+1)-1;
				ans[i]=Max(1,l,r);
			}else{
				if(k==n) ans[i]=Max(1,1,n);
				else{
					int p=Find(1,qi[i]-1);
					if(nmx[p]>n) ans[i]=a[n];
					else ans[i]=Max(1,nmx[p],n);
				}
			}
		}
		Add(1,1,n,-1);
		if(dat(1)[0]==0){
			int p=dat(1)[1],q=Find(1,Rank(1,p)+1),r=nmn[q];
			Recover(1,p,n);
			Assign(1,r,n,1);
			Assign(1,p+1,r-1,0);
			Add(1,p+1,r-1,n<<1);
			Set(1,p,nmn[r]<nmx[p]?nmn[r]-r:n<<1);
		}
	}

	for(int i=1;i<=q;i++) cout<<ans[i]<<endl;

	return 0;
}