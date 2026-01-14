#include<bits/stdc++.h>

using namespace std;

#define ssiz(x) (signed)x.size()
const int N=4e5+9;
const int sqN=1e3+9;

int fi[N],ne[N<<1],to[N<<1],adj;
void AdEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

long long ans[N];
int ql[N],qr[N],qx[N],n,m,rt,sonB,sizB;
int fa[N],son[N],siz[N],dfn[N],idfn[N],dcnt;
void DFS1(int x){
    siz[x]=1;
    dfn[x]=++dcnt;
    idfn[dcnt]=x;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        fa[y]=x;
        DFS1(y);
        siz[x]+=siz[y];
        son[x]++;
    }
}

int blk[N],L[N],R[N],bpre[sqN],pre[N],B;
inline void Init(){
    B=sqrt(n);
    for(int i=1;i<=n;i++) blk[i]=(i-1)/B+1;
    for(int i=1;i<=n;i++) R[blk[i]]=i;
    for(int i=n;i>=1;i--) L[blk[i]]=i;
}
inline void Add(int x,int k){
    for(int i=x;i<=R[blk[x]];i++) pre[i]+=k;
    for(int i=blk[x];i<=blk[n];i++) bpre[i]+=k;
}
inline int Ask(int x){return bpre[blk[x]-1]+pre[x];}
inline int Ask(int l,int r){return Ask(r)-Ask(l-1);}
long long sum[N];
vector<int> q[N];
void DFS2(int x){
    vector<pair<int,int>> qry;
    if(fa[x]){
        if(son[fa[x]]<=sonB) for(int i:q[fa[x]]) qry.push_back({i,-Ask(ql[i],qr[i])});
        else if(siz[x]>sizB) for(int i:q[fa[x]]) qry.push_back({i,-Ask(ql[i],qr[i])});
    }
    for(int i:q[x]){
        if(ql[i]<=x&&x<=qr[i]){
            if(son[x]<=sonB) sum[i]++;
            else ans[i]--;
        }
    }
    if(son[x]>sonB) for(int i:q[x]) sum[i]-=Ask(ql[i],qr[i]);
    Add(x,1);
    for(int i=fi[x];i;i=ne[i]) if(to[i]!=fa[x]) DFS2(to[i]);
    for(auto &p:qry){
        int i=p.first;
        p.second+=Ask(ql[i],qr[i]);
        if(son[fa[x]]<=sonB){
            ans[i]+=1ll*p.second*sum[i];
            sum[i]+=p.second;
        }else ans[i]-=1ll*p.second*p.second;
    }
    if(son[x]>sonB) for(int i:q[x]) sum[i]+=Ask(ql[i],qr[i]),ans[i]+=1ll*sum[i]*sum[i];
    qry.clear();
}

vector<int> p;
int cnt[N],c[N],scnt;
void Push(int x){
    p.clear();
    while(scnt) cnt[scnt--]=0;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x]) continue ;
        if(siz[y]>sizB) continue ;
        scnt++;
        for(int j=dfn[y];j<dfn[y]+siz[y];j++){
            p.push_back(idfn[j]);
            c[idfn[j]]=scnt;
        }
    }
    sort(p.begin(),p.end());
}
void Modify(long long &res,int pos,int k){
    res-=1ll*cnt[c[pos]]*cnt[c[pos]];
    cnt[c[pos]]+=k;
    res+=1ll*cnt[c[pos]]*cnt[c[pos]];
}
void MoAlgo(int x){
    int sq=sqrt(ssiz(p));
    vector<int> b(ssiz(p),0);
    for(int i=0;i<ssiz(p);i++) b[i]=(i-1)/sq+1;
    vector<array<int,3>> qry;
    for(int i:q[x]){
        int l=lower_bound(p.begin(),p.end(),ql[i])-p.begin();
        int r=upper_bound(p.begin(),p.end(),qr[i])-p.begin()-1;
        if(l>r) continue ;
        qry.push_back({i,l,r});
    }
    sort(qry.begin(),qry.end(),[&b](auto x,auto y){
        if(b[x[1]]^b[y[1]]) return b[x[1]]<b[y[1]];
        else return x[2]<y[2];
    });

    long long res=0;int l=0,r=-1;
    for(auto t:qry){
        while(r<t[2]) Modify(res,p[++r],1);
        while(l>t[1]) Modify(res,p[--l],1);
        while(r>t[2]) Modify(res,p[r--],-1);
        while(l<t[1]) Modify(res,p[l++],-1);
        ans[t[0]]-=res;
    }
}
void DFS3(int x){
    for(int i=fi[x];i;i=ne[i]) if(to[i]!=fa[x]) DFS3(to[i]);
    if(son[x]<=sonB) return ;
    Push(x),MoAlgo(x);
    for(int i:q[x]) ans[i]/=2;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'

    cin>>n>>m>>rt;
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;
        AdEg(u,v),AdEg(v,u);
    }
    for(int i=1;i<=m;i++) cin>>ql[i]>>qr[i]>>qx[i],q[qx[i]].push_back(i);

    sizB=sonB=sqrt(n),DFS1(rt);
    Init(),DFS2(rt);
    DFS3(rt);
    
    for(int i=1;i<=m;i++) cout<<ans[i]<<endl;

    return 0;
}