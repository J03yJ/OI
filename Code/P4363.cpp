#include<bits/stdc++.h>

using namespace std;

#define fir(x) x.first
#define sec(x) x.second
using pii=pair<int,int>;
const int N=(1<<22)+9;
const int M=1e1+9;

int f[N],vis[N],a[M][M],b[M][M],c[N],n,m;
vector<pii> e[N];

inline int Encode(vector<int> v){
    int res=0;
    for(int i=n;i>1;i--) v[i]-=v[i-1];
    for(int i=n;i>=1;i--) res<<=1,res|=1,res<<=v[i];
    return res;
}
inline vector<int> Decode(int sta){
    vector<int> res(n+1,0);
    int i=1;
    while(sta){
        if(sta&1) i++;
        else res[i]++;
        sta>>=1;
    }
    for(int i=1;i<=n;i++) res[i]+=res[i-1];
    return res;
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++) cin>>a[n-i+1][j];
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++) cin>>b[n-i+1][j];
    }

    int s=Encode(vector<int>(n+1,0)),t=Encode(vector<int>(n+1,m));
    memset(f,-0x3f,sizeof f);
    queue<int> q;
    q.push(s),vis[s]=1;
    while(q.size()){
        int x=q.front();
        vector<int> t(Decode(x));
        q.pop();
        for(int i=1;i<=n;i++) c[x]^=t[i]&1;
        for(int i=1;i<=n;i++){
            if(t[i]>=m) continue ;
            if(i!=n&&t[i]==t[i+1]) continue ;
            t[i]++;
            int y=Encode(t);
            e[y].push_back({x,(c[x]?b[i][t[i]]:a[i][t[i]])});
            if(!vis[y]) vis[y]=1,q.push(y);
            t[i]--;
        }
    }

    f[t]=0;
    q.push(t),vis[t]=0;
    while(q.size()){
        int x=q.front();
        q.pop();
        vector<int> v=Decode(x);
        for(pii p:e[x]){
            f[fir(p)]=max(f[fir(p)],-f[x]+sec(p));
            if(vis[fir(p)]) q.push(fir(p)),vis[fir(p)]=0;
        }
    }
    cout<<f[s]<<endl;

    return 0;
}