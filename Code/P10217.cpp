#include<bits/stdc++.h>

using namespace std;

using ll=long long;
using bint=__int128;
const int N=1e5+9;
const int inf=1e9;
const ll lnf=1e18;
template<class T> inline T Abs(T x){return x<0?-x:x;}

int x[N],y[N],n,k,tx,ty;
ll sumx[N],sumy[N];
inline bint W(int i,ll d){return Abs(bint(d)*sumx[n]+sumx[i]-tx)+Abs(bint(d)*sumy[n]+sumy[i]-ty);}
inline bint F(int i,ll x){return bint(k)*(x*n+i);}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    int T;
    cin>>T;
    while(T--){
        cin>>n>>k>>tx>>ty;
        for(int i=1;i<=n;i++) cin>>x[i]>>y[i];
        if(tx==0&&ty==0){
            cout<<0<<endl;
            continue ;
        }

        ll ans=lnf;
        for(int i=1;i<=n;i++) sumx[i]=sumx[i-1]+x[i];
        for(int i=1;i<=n;i++) sumy[i]=sumy[i-1]+y[i];
        for(int i=1;i<=n;i++){
            ll l=-1,r=1e12;
            while(l+1<r){
                ll mid=l+r>>1,p1=mid,p2=mid+1;
                if(min(__int128(0),F(i,p1)-W(i,p1))>=min(__int128(0),F(i,p2)-W(i,p2))) r=mid;
                else l=mid;
            }
            ll res=r;
            if(W(i,res)>F(i,res)) continue ;
            res=res*n+i;
            ans=min(ans,res);
        }

        cout<<(ans==lnf?-1:ans)<<endl;
    }

    return 0;
}