#include<bits/stdc++.h>

using namespace std;

#define int long long
#define ssiz(x) (signed)x.size()
const int N=4e2+9;
const int M=N*N;
const int K=1e3;
const int mod=998244353;

int a[N][N],c[K+9][K+9],f[N][N],n,ans;
vector<pair<int,int>> d[M];
#define F(x,y,z,w) c[(z)-(x)+(w)-(y)][(z)-(x)]
#define G(x,y) F(x.first,x.second,y.first,y.second)
void Solve1(int x){
    for(int i=0;i<ssiz(d[x]);i++){
        for(int j=0;j<ssiz(d[x]);j++){
            if(d[x][i].first>d[x][j].first) continue ;
            if(d[x][i].second>d[x][j].second) continue ;
            ans=(ans+G(d[x][i],d[x][j]))%mod;
        }
    }
}
void Solve2(int x){
    memset(f,0,sizeof f);
    for(auto p:d[x]) f[p.first][p.second]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            f[i][j]=(f[i][j]+f[i-1][j])%mod;
            f[i][j]=(f[i][j]+f[i][j-1])%mod;
        }
    }
    for(auto p:d[x]) ans=(ans+f[p.first][p.second])%mod;
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>a[i][j];
            d[a[i][j]].push_back({i,j});
        }
    }
    for(int i=0;i<=K;i++){
        c[i][0]=1;
        for(int j=1;j<=i;j++) c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
    }
    for(int i=1;i<=n*n;i++){
        if(ssiz(d[i])>n) Solve2(i);
        else Solve1(i);
    }

    cout<<ans<<endl;

    return 0;
}