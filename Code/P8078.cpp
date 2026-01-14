#include<bits/stdc++.h>

using namespace std;

const int N=5e5+9;
using ll=long long;

int a[N],n,m;
int ql[N],qr[N],blk[N],L[N],R[N],B;
vector<int> q[N];
ll ans[N];

int pre[N],suc[N],pos[N];
vector<pair<int&,int>> rb;
pair<int,int> prb[N],srb[N];
int ptop,stop;
inline void Rollback(){
    // while(rb.size()) rb.back().first=rb.back().second,rb.pop_back();
    while(ptop) pre[prb[ptop].first]=prb[ptop].second,ptop--;
    while(stop) suc[srb[stop].first]=srb[stop].second,stop--;
}
inline void Erase(int x,ll &ans,int flag){
    if(pre[x]) ans-=abs(x-pre[x]);
    if(suc[x]) ans-=abs(x-suc[x]);
    if(pre[x]&&suc[x]) ans+=abs(pre[x]-suc[x]);
    if(pre[x]&&flag) srb[++stop]={pre[x],x};
    suc[pre[x]]=suc[x];
    if(suc[x]&&flag) prb[++ptop]={suc[x],x};
    pre[suc[x]]=pre[x];
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=m;i++) cin>>ql[i]>>qr[i];

    B=sqrt(n);
    for(int i=1;i<=n;i++) blk[i]=(i-1)/B+1;
    for(int i=1;i<=n;i++) R[blk[i]]=i;
    for(int i=n;i>=1;i--) L[blk[i]]=i;
    for(int i=1;i<=m;i++) q[blk[ql[i]]].push_back(i);

    for(int o=1;o<=blk[n];o++){
        int l=L[o],r=n;
        sort(q[o].begin(),q[o].end(),[](int x,int y){return qr[x]>qr[y];});
        for(int i=L[o];i<=n;i++) pos[a[i]]=i;
        ll res=0;
        for(int i=1,lst=0;i<=n;i++){
            if(!pos[i]) continue ;
            if(lst) res+=abs(lst-pos[i]);
            suc[lst]=pos[i];
            pre[pos[i]]=lst;
            lst=pos[i];
        }
        for(int i:q[o]){
            while(r>qr[i]) Erase(r--,res,0);
            ll tmp=res;
            while(l<ql[i]) Erase(l++,res,1);
            ans[i]=res;
            Rollback();
            res=tmp,l=L[o];
        }
        for(int i=L[o];i<=n;i++) pos[a[i]]=0,pre[i]=suc[i]=0;
    }

    for(int i=1;i<=m;i++) cout<<ans[i]<<endl;

    return 0;
}