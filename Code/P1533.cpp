#include<bits/stdc++.h>
using namespace std;
const int N=2.5e7+9;
struct node{
	int lc,rc;
	int dat;
}t[N];
#define lc(x) t[x].lc
#define rc(x) t[x].rc
#define v(x) t[x].dat
int root[N],cnt;
int build(int l,int r){
	int x=++cnt;
	if(l==r){
		v(x)=0;
		return x;
	}
	int mid=l+r>>1;
	lc(x)=build(l,mid);
	rc(x)=build(mid+1,r);
	return x;
}
int modify(int now,int l,int r,int pos,int k){
	int x=++cnt;
	t[x]=t[now];
	if(l==r){
		v(x)+=k;
		return x;
	}
	int mid=l+r>>1;
	if(pos<=mid) lc(x)=modify(lc(now),l,mid,pos,k);
	else rc(x)=modify(rc(now),mid+1,r,pos,k);
	v(x)=v(lc(x))+v(rc(x));
	return x;
}
int query(int x,int y,int l,int r,int k){
	if(l==r) return l;
	int mid=l+r>>1;
	int lcnt=v(lc(x))-v(lc(y));
	if(k>lcnt) return query(rc(x),rc(y),mid+1,r,k-lcnt);
	else return query(lc(x),lc(y),l,mid,k);
}
int a[N],b[N];
map<int,int>mp;
int main(){
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i],b[i]=a[i];
	sort(b+1,b+n+1);
	int m=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=m;i++) mp[b[i]]=i;
	root[0]=build(1,m);
	for(int i=1;i<=n;i++) root[i]=modify(root[i-1],1,m,mp[a[i]],1);
	while(q--){
		int l,r,k;
		cin>>l>>r>>k;
		cout<<b[query(root[r],root[l-1],1,m,k)]<<endl;
	}
	return 0;
}