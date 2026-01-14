#include<bits/stdc++.h>

using namespace std;

using ll=long long;

namespace Barrett{
    ll mod,k,e;
    inline void Set(ll x){k=30,mod=x,e=((1ll<<k)+mod-1)/mod;}
    inline ll Div(ll x){return e*x>>k;}
}

signed main(){
    Barrett::Set(13);

    for(int i=1;i<=200;i++) cout<<i<<" : "<<i/Barrett::mod<<' '<<Barrett::Div(i)<<endl;

    return 0;
}