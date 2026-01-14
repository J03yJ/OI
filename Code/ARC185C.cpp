#include<bits/stdc++.h>

using namespace std;

#define int long long
const int mod=998244353;
const int gmod=3;

int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}
void NTT(vector<int> &a,int flag){
    int lim=a.size();
    vector<int> r(lim,0);
    for(int i=0;i<lim;i++) r[i]=(r[i>>1]>>1)+(lim>>1)*(i&1);
    for(int i=0;i<lim;i++) if(i<r[i]) swap(a[i],a[r[i]]);
    for(int k=1;k<lim;k<<=1){
        int wn=QPow(gmod,(mod-1)/(k<<1));
        if(!flag) wn=QPow(wn,mod-2);
        for(int i=0;i<lim;i+=(k<<1)){
            int w=1;
            for(int j=0;j<k;j++,w=w*wn%mod){
                int tmp=a[i+j+k]*w%mod;
                a[i+j+k]=(a[i+j]-tmp+mod)%mod;
                a[i+j]=(a[i+j]+tmp)%mod;
            }
        }
    }
    if(!flag){
        int inv=QPow(lim,mod-2);
        for(int &x:a) x=x*inv%mod;
    }
}
void Convo(vector<int> a,vector<int> b,vector<int> &c){
    NTT(a,1),NTT(b,1);
    for(int i=0;i<a.size();i++) c[i]=a[i]*b[i]%mod;
    NTT(c,0);
}

mt19937 rng(random_device{}());

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'
    
    int n,m,lim=1;
    cin>>n>>m;
    vector<pair<int,int>> a(n);
    for(int i=0;i<n;i++) cin>>a[i].first,a[i].second=i;
    
    while(lim<=m) lim<<=1;
    while(clock()<=2*CLOCKS_PER_SEC){
        shuffle(a.begin(),a.end(),rng);
        vector<int> o(lim,0),p(lim,0),q(lim,0);
        int x=n/3,y=n*2/3;
        for(int i=0;i<x;i++) o[a[i].first]++;
        for(int i=x;i<y;i++) p[a[i].first]++;
        for(int i=y;i<n;i++) q[a[i].first]++;
        auto t=vector<int>(lim);
        Convo(o,p,t);
        for(int i=0;i<=m;i++){
            if(!q[m-i]||!t[i]) continue ;
            vector<int> res;
            for(int j=y;j<n;j++){
                if(a[j].first==m-i){
                    res.push_back(a[j].second);
                    break ;
                }
            }
            for(int j=0;j<=i;j++){
                if(!o[j]||!p[i-j]) continue ;
                for(int k=0;k<x;k++){
                    if(a[k].first==j){
                        res.push_back(a[k].second);
                        break ;
                    }
                }
                for(int k=x;k<y;k++){
                    if(a[k].first==i-j){
                        res.push_back(a[k].second);
                        break ;
                    }
                }
                sort(res.begin(),res.end());
                for(int r:res) cout<<r+1<<' ';cout<<endl;
                return 0;
            }
        }
    }
    cout<<-1<<endl;

    return 0;
}