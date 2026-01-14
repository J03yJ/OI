#include<bits/stdc++.h>

using namespace std;

ifstream fin("dungeon.in");
ofstream fout("dungeon.out");
#define cin fin
#define cout fout
#define endl '\n'

using ll=long long;
const int N=2e5+9;
const int lgN=2e1;
const ll inf=1e18;

int a[N],b[N],n;
int s[N],t[N],u[N],q;
ll p[N],ans[N];
vector<int> lq[N],rq[N];

vector<ll> val;
inline int LFind(ll x){return lower_bound(val.begin(),val.end(),x)-val.begin();}
inline int RFind(ll x){return upper_bound(val.begin(),val.end(),x)-val.begin()-1;}
inline int Find(ll x){return LFind(x);}
struct Fenwick{
	int lim;
	ll tr[N];
	inline void Modify(int x,ll k){while(x<=lim) tr[x]+=k,x+=x&-x;}
	inline void Modify(int l,int r,ll k){Modify(l,k),Modify(r+1,-k);}
	inline ll Query(int x){ll sum=0;while(x) sum+=tr[x],x&=x-1;return sum;}
}bt,kt;
inline void _Modify(int l,int r,ll k,ll b){kt.Modify(l,r,k),bt.Modify(l,r,b);}
inline ll _Query(int x){return kt.Query(x)*val[x]+bt.Query(x);}
inline void Modify(ll l,ll r,ll k,ll b){return _Modify(LFind(l),RFind(r),k,b);}
inline ll Query(ll x){return _Query(Find(x));}

int st[N][lgN],mx[N][lgN],lg[N];
inline void Init(){
	for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
	for(int i=1;i<=n;i++) st[i][0]=i,mx[i][0]=a[i];
	for(int k=1;k<=lg[n];k++){
		for(int i=1;i<=n-(1<<k)+1;i++){
			if(b[st[i][k-1]]<b[st[i+(1<<k-1)][k-1]]) st[i][k]=st[i][k-1];
			else st[i][k]=st[i+(1<<k-1)][k-1];
			mx[i][k]=max(mx[i][k-1],mx[i+(1<<k-1)][k-1]);
		}
	}
}
inline int MinPos(int l,int r){
	int k=lg[r-l+1];
	if(b[st[l][k]]<b[st[r-(1<<k)+1][k]]) return st[l][k];
	else return st[r-(1<<k)+1][k];
}
inline int Max(int l,int r){
	int k=lg[r-l+1];
	return max(mx[l][k],mx[r-(1<<k)+1][k]);
}

signed main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	for(int i=1;i<=q;i++) cin>>s[i]>>t[i]>>u[i];
	
	for(int i=1;i<=q;i++) val.push_back(u[i]);
	val.push_back(0),val.push_back(inf);
	sort(val.begin(),val.end());
	val.erase(unique(val.begin(),val.end()),val.end());
	bt.lim=kt.lim=val.size();
	
	Init();
	for(int i=2;i<=n+1;i++) p[i]=p[i-1]+a[i-1];
	for(int i=1;i<=q;i++){
		if(Max(s[i],t[i]-1)>u[i]) ans[i]=-1;
		else{
			lq[s[i]].push_back(i);
			int j=lower_bound(p+1,p+n+2,p[t[i]]-u[i])-p;
			j=max(j,s[i]);
			int mpos=MinPos(j,t[i]-1);
			rq[mpos].push_back(i);
			ans[i]=(p[t[i]]-p[mpos])*b[mpos];
		}
	}

	vector<int> mn;
	mn.push_back(n+1);
	for(int i=n;i>=1;i--){
		Modify(p[i+1]-p[i],inf,0,(p[i+1]-p[i])*b[i]);
		while(mn.size()&&b[i]<b[mn.back()]){
			int j=mn.back();
			mn.pop_back();
			int k=mn.back();
			Modify(p[j]-p[i]+1,p[k]-p[i],b[i]-b[j],(p[i]-p[j])*(b[i]-b[j]));
			Modify(p[k]-p[i]+1,inf,0,(p[k]-p[j])*(b[i]-b[j]));
		}
		mn.push_back(i);
		for(int j:lq[i]) ans[j]+=Query(u[j]);
		for(int j:rq[i]) ans[j]-=Query(u[j]);
	}

	for(int i=1;i<=q;i++) cout<<ans[i]<<endl;

	return 0;
}