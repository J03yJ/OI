#include<bits/stdc++.h>

using namespace std;

#define ssiz(x) (signed)x.size()
#define allc(x) x.begin(),x.end()
#define In(x,l,r) ((l)<=(x)&&(x)<=(r))
const int N=1e5+9;
const int M=5e5+9;
const int lgN=2e1;
using lint=long long;
// #define int lint

int a[N],n,m;
void Discr(){
    vector<int> val;
    for(int i=1;i<=n;i++) val.push_back(a[i]);
    sort(allc(val));
    val.erase(unique(allc(val)),val.end());
    for(int i=1;i<=n;i++) a[i]=lower_bound(allc(val),a[i])-val.begin()+1;
}

int fi[N],ne[N<<1],to[N<<1],adj;
inline void AdEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}
int fa[N][lgN],dfn[N],idfn[N],dep[N],siz[N],dcnt,crt;
void DFS(int x){
    dfn[x]=++dcnt;
    idfn[dcnt]=x;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x][0]) continue ;
        fa[y][0]=x;
        dep[y]=dep[x]+1;
        DFS(y);
    }
    siz[x]=dcnt-dfn[x]+1;
}
void InitTr(){
    crt=1,dep[crt]=1,DFS(crt);
    for(int k=1;k<lgN;k++){
        for(int i=1;i<=n;i++) fa[i][k]=fa[fa[i][k-1]][k-1];
    }
}
inline int Appr(int x,int tar){
    int tmp=dep[x]-dep[tar]-1;
    for(int k=lgN-1;~k;k--) if(tmp>>k&1) x=fa[x][k];
    return x;
}
inline void Split(int root,int x,vector<pair<int,int>> &sx){
    if(x==root) sx.push_back({n,1});
    else if(In(dfn[root],dfn[x],dfn[x]+siz[x]-1)){
        int pos=Appr(root,x);
        sx.push_back({n,1});
        sx.push_back({dfn[pos]-1,1});
        sx.push_back({dfn[pos]+siz[pos]-1,-1});
    }else{
        sx.push_back({dfn[x]-1,-1});
        sx.push_back({dfn[x]+siz[x]-1,1});
    }
}

int op[M],blk[N],cnt1[N],cnt2[N],c[N],B,tot;
array<int,3> q[M*9];
lint ans[M];
void InitB(){
    B=ceil(n/sqrt(tot));
    for(int i=1;i<=n;i++) blk[i]=(i-1)/B+1;
    sort(q+1,q+tot+1,[](auto &x,auto &y)->int{
        return blk[x[1]]^blk[y[1]]?blk[x[1]]<blk[y[1]]:(x[2]<y[2])^(blk[x[1]]&1);
    });
}
void MoAlgo(){
    register lint res=0;
    register int i=0,j=0;
    for(int p=1;p<=tot;p++){
        while(i<q[p][1]) res+=cnt2[c[++i]],++cnt1[c[i]];
        while(j<q[p][2]) res+=cnt1[c[++j]],++cnt2[c[j]];
        while(i>q[p][1]) --cnt1[c[i]],res-=cnt2[c[i--]];
        while(j>q[p][2]) --cnt2[c[j]],res-=cnt1[c[j--]];
        if(q[p][0]>0) ans[q[p][0]]+=res;
        else ans[-q[p][0]]-=res;
    }
}

void Read(int &x){
    char ch;while(ch=getchar(),ch<'!');x=ch-48;
    while(ch=getchar(),ch>'!') x=(x<<3)+(x<<1)+ch-48;
}
void Write(lint x){
    if(x>9) Write(x/10);
    putchar(x%10+48);
}

lint f[N];

signed main(){
    Read(n),Read(m);
    for(int i=1;i<=n;i++) Read(a[i]);
    for(int i=1,u,v;i<n;i++) Read(u),Read(v),AdEg(u,v),AdEg(v,u);
    
    Discr();
    InitTr();
    for(int i=1;i<=n;i++) c[i]=a[idfn[i]];
    for(int i=1;i<=n;i++) cnt1[c[i]]++;
    for(int i=1;i<=n;i++) f[i]=f[i-1]+cnt1[c[i]];
    for(int i=1;i<=n;i++) cnt1[i]=cnt2[i]=0;
    for(int i=1,root=1,x,y;i<=m;i++){
        Read(op[i]);
        if(op[i]==1) Read(root);
        else{
            Read(x),Read(y);
            vector<pair<int,int>> sx,sy;
            sx.reserve(3),sy.reserve(3);
            Split(root,x,sx),Split(root,y,sy);
            for(auto px:sx){
                if(!px.first) continue ;
                for(auto py:sy){
                    if(!py.first) continue ;
                    if(px.first==n) ans[i]+=px.second*py.second*f[py.first];
                    else if(py.first==n) ans[i]+=px.second*py.second*f[px.first];
                    else q[++tot]={i*px.second*py.second,px.first,py.first};
                }
            }
        }
    }

    InitB();
    MoAlgo();
    
    for(int i=1;i<=m;i++) if(op[i]==2) cout<<ans[i],putchar('\n');

    return 0;
}