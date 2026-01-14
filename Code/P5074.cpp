#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=1.2e1+9;
const int S=1.2e6+9;

int n,m;
bool a[N][N];

ll f[2][S];
int cnt[2],s[2][S],now;
map<int,int> mp;
inline void Add(int sta,ll k){
    if(!mp[sta]){
        mp[sta]=++cnt[now];
        f[now][cnt[now]]=0;
        s[now][cnt[now]]=sta;
    }
    f[now][mp[sta]]+=k;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    int T;
    cin>>T;
    while(T--){
        memset(a,0,sizeof a);
        cin>>n>>m;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++) cin>>a[i][j];
        }

        now=0;
        mp.clear();
        memset(f,0,sizeof f);
        memset(s,0,sizeof s);
        memset(cnt,0,sizeof cnt);

        Add(0,1);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=cnt[now];j++) s[now][j]<<=1;
            for(int j=1;j<=m;j++){
                mp.clear();
                cnt[now^=1]=0;
                for(int k=1;k<=cnt[now^1];k++){
                    ll val=f[now^1][k];
                    int sta=s[now^1][k];
                    int pr=sta>>j-1&1,pd=sta>>j&1;
                    if(!a[i][j]){
                        if(!pr&&!pd) Add(sta,val);
                    }else if(!pr&&!pd){
                        if(a[i+1][j]&&a[i][j+1]) Add(sta+(1<<j)+(1<<j-1),val);
                    }else if(!pr&&pd){
                        if(a[i+1][j]) Add(sta-(1<<j)+(1<<j-1),val);
                        if(a[i][j+1]) Add(sta-(1<<j)+(1<<j),val);
                    }else if(pr&&!pd){
                        if(a[i][j+1]) Add(sta-(1<<j-1)+(1<<j),val);
                        if(a[i+1][j]) Add(sta-(1<<j-1)+(1<<j-1),val);
                    }else if(pr&&pd){
                        Add(sta-(1<<j-1)-(1<<j),val);
                    }
                }
            }
        }    

        ll ans=0;
        for(int i=1;i<=cnt[now];i++){
            if(s[now][i]==0) ans+=f[now][i];
        }

        cout<<ans<<endl;
    }

    return 0;
}