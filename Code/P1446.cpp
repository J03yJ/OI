#include<bits/stdc++.h>

using namespace std;

#define For(i,l,r) for(int i=(l);i<=(r);++i)
#define Rof(i,r,l) for(int i=(r);i>=(l);i--)
#define Rep(i,n) for(int i=0;i<(n);i++)
#define ssiz(x) (signed)x.size()
#define allc(x) x.begin(),x.end()
#define fir(x) x.first
#define sec(x) x.second
using ll=long long;
using ull=unsigned long long;
using pii=pair<int,int>;
template<class S,class T>void ChMin(S &x,T y){if(y<x) x=y;}
template<class S,class T>void ChMax(S &x,T y){if(y>x) x=y;}
template<class T>using svector=vector<vector<T>>;
template<class T>using cvector=vector<vector<vector<T>>>;

int mod;
void AddAs(int &x,int y){x+=y;if(x>=mod) x-=mod;}
int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=1ll*res*x%mod;
        x=1ll*x*x%mod;
        y>>=1;
    }
    return res;
}
#define Inv(x) QPow(x,mod-2)

int RCount(int cr,int cg,int cb,vector<int> &r){
    for(int &x:r) x--;
    cvector<int> f(cr+1,svector<int>(cg+1,vector<int>(cb+1,0)));
    vector<int> vis(r.size(),0),ri;
    Rep(i,ssiz(r)){
        if(vis[i]) continue ;
        int cur=i,cnt=0;
        while(!vis[cur]){
            vis[cur]=1;
            cur=r[cur];
            cnt++;
        }
        ri.push_back(cnt);
    }
    f[0][0][0]=1;
    for(int x:ri){
        Rof(i,cr,0) Rof(j,cg,0) Rof(k,cb,0){
            if(i>=x) AddAs(f[i][j][k],f[i-x][j][k]);
            if(j>=x) AddAs(f[i][j][k],f[i][j-x][k]);
            if(k>=x) AddAs(f[i][j][k],f[i][j][k-x]);
        }
    }
    return f[cr][cg][cb];
}

int main(){
    int cr,cg,cb,m;
    cin>>cr>>cg>>cb>>m>>mod;

    int sum=0;
    Rep(i,m){
        vector<int> r(cr+cb+cg);
        for(int &x:r) cin>>x;
        AddAs(sum,RCount(cr,cg,cb,r));
    }
    vector<int> r(cr+cb+cg);
    iota(allc(r),1);
    AddAs(sum,RCount(cr,cg,cb,r));

    cout<<Inv(m+1)*sum%mod<<endl;

    return 0;
}