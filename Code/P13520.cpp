#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=2e5;
const int inf=1e9+7;

struct Node{
	int l,r,dat,tag;
}tr[N<<2];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define dat(x) tr[x].dat
#define tag(x) tr[x].tag

inline void PushUp(int x){dat(x)=min(dat(x<<1),dat(x<<1|1));}
inline void Push(int x,int k){tag(x)+=k,dat(x)+=k;}
inline void PushDown(int x){
	if(!tag(x)) return ;
	Push(x<<1,tag(x));
	Push(x<<1|1,tag(x));
	tag(x)=0;
}
inline void Build(int x,int l,int r){
	l(x)=l,r(x)=r;
	if(l(x)==r(x)) return ;
	int mid=l(x)+r(x)>>1;
	Build(x<<1,l,mid);
	Build(x<<1|1,mid+1,r);
	PushUp(x);
}
inline void Modify(int x,int l,int r,int k){
	if(l<=l(x)&&r(x)<=r) return Push(x,k);
	int mid=l(x)+r(x)>>1;
	PushDown(x);
	if(l<=mid) Modify(x<<1,l,r,k);
	if(r>mid) Modify(x<<1|1,l,r,k);
	PushUp(x);
}

int a[N],b[N],n,tot;
vector<int> val;

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i]>>b[i];

	val.push_back(0);
	val.push_back(inf);
	for(int i=1;i<=n;i++) val.push_back(b[i]);
	sort(val.begin(),val.end());
	val.erase(unique(val.begin(),val.end()),val.end());
	tot=val.size()-1;

	Build(1,1,tot);
	for(int i=1;i<=n;i++){
		int bp=lower_bound(val.begin(),val.end(),b[i])-val.begin();
		Modify(1,1,bp,1);
		int ap=lower_bound(val.begin(),val.end(),a[i])-val.begin();
		Modify(1,1,ap,-1);
		cout<<-dat(1)<<endl;
	}

	return 0;
}