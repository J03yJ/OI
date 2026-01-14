#include<bits/stdc++.h>

using namespace std;

using ll=long long;
using ull=unsigned ll;
const int N=2e7+128;
const int LEN=6;
const int lgN=2e1;
const int M=N>>LEN;

namespace GenHelper{
    unsigned z1,z2,z3,z4,b;
    inline unsigned rand_(){
		b=((z1<<6)^z1)>>13;
		z1=((z1&4294967294U)<<18)^b;
		b=((z2<<2)^z2)>>27;
		z2=((z2&4294967288U)<<2)^b;
		b=((z3<<13)^z3)>>21;
		z3=((z3&4294967280U)<<7)^b;
		b=((z4<<3)^z4)>>12;
		z4=((z4&4294967168U)<<13)^b;
		return (z1^z2^z3^z4);
    }
}
inline void srand(unsigned x){
	using namespace GenHelper;
	z1=x;
	z2=(~x)^0x233333333U;
	z3=x^0x1234598766U;
	z4=(~x)+51;
}
inline int read(){
    using namespace GenHelper;
    int a=rand_()&32767;
    int b=rand_()&32767;
    return a*32768+b;
}

#define blk(x) (((x)-1>>LEN)+1)
#define id(x) ((x)-1&((1<<LEN)-1))
#define R(x) ((x)<<LEN)
#define L(x) (R((x)-1)+1)
int a[N],st[lgN][M+9],pre[N],suf[N],n,m,s;
ull pos[N];
inline int BrMax(int l,int r){
	int ans=0;
	for(int i=l;i<=r;i++) ans=max(ans,a[i]);
	return ans;
}
inline void Init(){
	for(int i=1;i<=R(blk(n));i++) pre[i]=(i==L(blk(i))?a[i]:max(a[i],pre[i-1]));
	for(int i=R(blk(n));i>=1;i--) suf[i]=(i==R(blk(i))?a[i]:max(a[i],suf[i+1]));
	for(int i=1;i<=blk(n);i++) for(int j=L(i);j<=R(i);j++) st[0][i]=max(st[0][i],a[j]);
	for(int k=1;k<=__lg(blk(n));k++){
		for(int i=1;i<=blk(n)-(1<<k)+1;i++){
			st[k][i]=max(st[k-1][i],st[k-1][i+(1<<k-1)]);
		}
	}
	for(int i=1;i<=blk(n);i++){
		ull sta=0;
		vector<int> stk;
		for(int j=0;j<(1<<LEN);j++){
			while(stk.size()&&a[L(i)+stk.back()]<=a[L(i)+j]){
				sta^=1ull<<stk.back();
				stk.pop_back();
			}
			stk.push_back(j);
			pos[L(i)+j]=sta|=1ull<<j;
		}
	}
}
inline int BMax(int l,int r){
	if(l>r) return INT_MIN;
	int k=__lg(r-l+1);
	return max(st[k][l],st[k][r-(1<<k)+1]);
}
inline int PMax(int l,int r){
	ull sta=(pos[r]>>id(l))<<id(l);
	return a[L(blk(l))+__lg(sta&-sta)];
}
inline int Max(int l,int r){
	if(blk(l)==blk(r)) return PMax(l,r);
	else return max(BMax(blk(l)+1,blk(r)-1),max(suf[l],pre[r]));
}

signed main(){
	cin>>n>>m>>s;
	srand(s);
	
	for(int i=1;i<=n;i++) a[i]=read();
	Init();

	ull ans=0;
	while(m--){
		int l=read()%n+1,r=read()%n+1;
		if(l>r) swap(l,r);
		ans+=Max(l,r);
	}
	cout<<ans<<endl;

	return 0;
}