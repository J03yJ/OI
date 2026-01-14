#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ull=unsigned int;
using ubint=unsigned long long;
constexpr ull mod=998244353u;
const int N=1e6+9;
inline ull QPow(ull x,ull y){
	ull res=1;
    while(y){
		if(y&1) res=ubint(res)*x%mod;
        x=ubint(x)*x%mod;
        y>>=1;
    }
    return res;
}
constexpr ull base=1145141u;
const ull ibase=QPow(base,mod-2);

int n;
string s;

ull b[N],ib[N],ph[N];
inline void InitHash(){
	b[0]=ib[0]=1;
	for(int i=1;i<=n;i++){
		b[i]=ubint(b[i-1])*base%mod;
		ib[i]=ubint(ib[i-1])*ibase%mod;
		ph[i]=(ph[i-1]+ubint(s[i])*b[i-1])%mod;
	}
}
inline ull H(int l,int r){return ubint(ph[r]-ph[l-1]+mod)*ib[l-1]%mod;}
inline int LCP(int l,int r){
	if(s[l]!=s[r]) return 0;
	if(l>r) swap(l,r);
	int il=0,ir=n-r+2;
	while(il+1<ir){
		int im=il+ir>>1;
		if(H(l,l+im-1)==H(r,r+im-1)) il=im;
		else ir=im;
	}
	return il;
}
inline int LCS(int l,int r){
	if(s[l]!=s[r]) return 0;
	if(l>r) swap(l,r);
	int il=0,ir=l+1;
	while(il+1<ir){
		int im=il+ir>>1;
		if(H(l-im+1,l)==H(r-im+1,r)) il=im;
		else ir=im;
	}
	return il;
}
inline bool Lt(int i,int j){
	int k=LCP(i,j);
	return s[i+k]<s[j+k];
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>s;
	n=s.size();
	s=" "+s+char(0);
	InitHash();

	vector<int> stk;
	vector<array<int,3>> ans;
	for(int c:{0,1}){
		for(int i=n;i>=1;i--){
			while(stk.size()&&(Lt(i,stk.back())^c)) stk.pop_back();
			if(stk.size()){
				int j=stk.back(),p=j-i;
				if(s[i]==s[j]){
					int l=i-LCS(i,j)+1,r=j+LCP(i,j)-1;
					if(r-l+1>=2*p&&H(l,r-p)==H(l+p,r)) ans.push_back({l,r,p});
				}
			}
			stk.push_back(i);
		}
		stk.clear();
	}
	sort(ans.begin(),ans.end());
	ans.erase(unique(ans.begin(),ans.end()),ans.end());

	cout<<ans.size()<<endl;
	for(auto t:ans) cout<<t[0]<<' '<<t[1]<<' '<<t[2]<<endl;

	return 0;
}