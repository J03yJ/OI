#include<bits/stdc++.h>

using namespace std;

const int N=3e5+9;

int a[N],tmp[N],n,m;
int op[N],ql[N],qr[N],qpos[N],qx[N];
int w[N<<1],ans[N];

int tr[N];
inline void Add(int x,int k){
    while(x<=n){
        tr[x]+=k;
        x+=x&-x;
    }
}
inline int Ask(int x){
    int sum=0;
    while(x){
        sum+=tr[x];
        x&=x-1;
    }
    return sum;
}
inline int Ask(int l,int r){return Ask(r)-Ask(l-1);}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=m;i++){
        cin>>op[i];
        if(op[i]==1) cin>>qpos[i]>>qx[i];
        else cin>>ql[i]>>qr[i]>>qx[i];
    }

    vector<int> val({-1});
    for(int i=1;i<=n;i++) val.push_back(a[i]);
    for(int i=1;i<=m;i++) if(op[i]==1) val.push_back(qx[i]);
    sort(val.begin(),val.end());
    val.erase(unique(val.begin(),val.end()),val.end());
    for(int i=1;i<=n;i++) a[i]=lower_bound(val.begin(),val.end(),a[i])-val.begin();
    for(int i=1;i<=m;i++) if(op[i]==1) qx[i]=lower_bound(val.begin(),val.end(),qx[i])-val.begin();
    int tot=val.size()-1;

    int T=40;
    mt19937 rng(4649);
    for(int i=1;i<=m;i++) if(op[i]==2) ans[i]=1;
    while(T--){
        for(int i=1;i<=tot;i++) w[i]=rng()&1;
        for(int i=1;i<=n;i++) tr[i]=0;
        for(int i=1;i<=n;i++) Add(i,w[tmp[i]=a[i]]);
        for(int i=1;i<=m;i++){
            if(op[i]==1){
                Add(qpos[i],-w[tmp[qpos[i]]]);
                tmp[qpos[i]]=qx[i];
                Add(qpos[i],w[tmp[qpos[i]]]);
            }else if(Ask(ql[i],qr[i])%qx[i]) ans[i]=0;
        }
    }
    for(int i=1;i<=m;i++) if(op[i]==2) cout<<(ans[i]?"YES":"NO")<<endl;

    return 0;
}