#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll=long long;
const int N=1.2e1+9;
const int S=1.2e6+9;

int b[N],n,m;
bool a[N][N];

map<int,int> mp;
int cnt[2],s[2][S],now;
ll f[2][S];
inline void Add(int sta,ll k){
    if(!mp[sta]){
        mp[sta]=++cnt[now];
        f[now][cnt[now]]=0;
        s[now][cnt[now]]=sta;
    }
    f[now][mp[sta]]+=k;
}
inline void Next(){
    mp.clear();
    cnt[now^=1]=0;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n>>m;
    memset(a,1,sizeof a);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char c;
            cin>>c;
            a[i][j]=(c=='*');
        }
    }

    int edi=0,edj=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(a[i][j]) continue ;
            edi=i,edj=j;
        }
    }

    ll ans=0;
    Add(0,1);
    for(int i=0;i<=m;i++) b[i]=1<<(i<<1);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=cnt[now];j++) s[now][j]<<=2;
        for(int j=1;j<=m;j++){
            Next();
            for(int k=1;k<=cnt[now^1];k++){
                ll val=f[now^1][k];
                int sta=s[now^1][k];
                int pr=sta>>(j-1<<1)&3,pd=sta>>(j<<1)&3;
                if(a[i][j]){ // Case 0 : Block
                    if(pr==0&&pd==0) Add(sta,val);
                }else if(pr==0&&pd==0){ // Case 1 : New LR-Bracket
                    if(!a[i][j+1]&&!a[i+1][j]) Add(sta+1*b[j-1]+2*b[j],val); // .. -> ()
                }else if(pr==0&&pd!=0){ // Case 2 : D-Plug
                    if(!a[i+1][j]) Add(sta-pd*b[j]+pd*b[j-1],val); // D -> D
                    if(!a[i][j+1]) Add(sta-pd*b[j]+pd*b[j],val); // D -> R
                }else if(pr!=0&&pd==0){ // Case 3 : R-Plug
                    if(!a[i][j+1]) Add(sta-pr*b[j-1]+pr*b[j],val); // R -> R
                    if(!a[i+1][j]) Add(sta-pr*b[j-1]+pr*b[j-1],val); // R -> D
                }else if(pr==1&&pd==1){ // Case 4 : LL-Bracket
                    for(int t=j,sum=0;t<=m;t++){
                        int p=sta>>(t<<1)&3;
                        if(p==1) sum++;
                        if(p==2) sum--;
                        if(sum==0){
                            Add(sta-1*b[j-1]-1*b[j]-2*b[t]+1*b[t],val); // (()) -> ..()
                            break ;
                        }
                    }
                }else if(pr==2&&pd==2){ // Case 5 : RR-Bracket
                    for(int t=j-1,sum=0;~t;t--){
                        int p=sta>>(t<<1)&3;
                        if(p==1) sum++;
                        if(p==2) sum--;
                        if(sum==0){
                            Add(sta-2*b[j-1]-2*b[j]-1*b[t]+2*b[t],val); // (()) -> ()..
                            break ;
                        }
                    }
                }else if(pr==2&&pd==1){ // Case 6 : RL-Bracket
                    Add(sta-2*b[j-1]-b[j],val); // ()() -> (..)
                }else if(pr==1&&pd==2){ // Case 7 : Closing LR-Bracket
                    if(i!=edi||j!=edj) continue ;
                    ans+=val; // () -> ..
                }
            }
        }
    }

    cout<<ans<<endl;

    return 0;
}