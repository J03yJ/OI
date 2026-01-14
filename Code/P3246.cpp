#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=1e5+9;
const int lgN=2e1;
const int inf=1e18;

int lg[N],st[N][lgN],a[N],n,q,typ;
int GetMin(int l,int r){
    int k=lg[r-l+1],x=st[l][k],y=st[r-(1<<k)+1][k];
    return a[x]<a[y]?x:y;
}

int f[N],ff[N],g[N],gg[N];

namespace Gen{
	typedef unsigned long long ull;
	ull s,a,b,c,lastans=0;
	ull rand(){
		return s^=(a+b*lastans)%c;
	}
};

signed main(){
    cin>>n>>q>>typ;
    for(int i=1;i<=n;i++) cin>>a[i];
    if(typ) cin>>Gen::s>>Gen::a>>Gen::b>>Gen::c;

    for(int i=1;i<=n;i++) st[i][0]=i;
    for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
    for(int k=1;k<=lg[n];k++){
        for(int i=1;i<=n-(1<<k)+1;i++){
            if(a[st[i][k-1]]<a[st[i+(1<<k-1)][k-1]]) st[i][k]=st[i][k-1];
            else st[i][k]=st[i+(1<<k-1)][k-1];
        }
    }

    vector<int> stk;
    a[0]=-inf;
    stk.push_back(0);
    for(int i=1;i<=n;i++){
        while(stk.size()&&a[i]<=a[stk.back()]) stk.pop_back();
        f[i]=f[stk.back()]+a[i]*(i-stk.back());
        ff[i]=ff[i-1]+f[i];
        stk.push_back(i);
    }
    stk.clear();
    a[n+1]=-inf;
    stk.push_back(n+1);
    for(int i=n;i>=1;i--){
        while(stk.size()&&a[i]<=a[stk.back()]) stk.pop_back();
        g[i]=g[stk.back()]+a[i]*(stk.back()-i);
        gg[i]=gg[i+1]+g[i];
        stk.push_back(i);
    }

    unsigned int res=0;
    while(q--){
        int l,r;
        if(!typ) cin>>l>>r;
        else{
            l=Gen::rand()%n+1;
            r=Gen::rand()%n+1;
            if(l>r) std::swap(l,r);
        }
        int pos=GetMin(l,r),ans=(pos-l+1)*(r-pos+1)*a[pos];
        ans+=gg[l]-gg[pos]-g[pos]*(pos-l);
        ans+=ff[r]-ff[pos]-f[pos]*(r-pos);
        res^=(unsigned int)ans;
        Gen::lastans=ans;
    }
    cout<<res<<endl;

    return 0;
}