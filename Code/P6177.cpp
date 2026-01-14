#include<bits/stdc++.h>

using namespace std;

const int N=4e4+9;
const int sqN=2e2+9;
const int lgN=16;

int a[N],n,m;
int fi[N],ne[N<<1],to[N<<1],adj;
inline void AdEg(int x,int y){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
}

int fa[N][lgN],imp[N],anc[N],dep[N],p[N];
bitset<N> s[sqN][sqN];
inline void DFS(int x,int t){
    anc[x]=t;
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(y==fa[x][0]) continue ;
        fa[y][0]=x,dep[y]=dep[x]+1;
        DFS(y,imp[x]?x:t);
    }
}
inline void Init(){
    for(int k=1;k<lgN;k++){
        for(int i=1;i<=n;i++) fa[i][k]=fa[fa[i][k-1]][k-1];
    }
}
inline int LCA(int x,int y){
    if(dep[x]<dep[y]) swap(x,y);
    for(int k=lgN-1;~k;k--) if(dep[fa[x][k]]>=dep[y]) x=fa[x][k];
    if(x==y) return x;
    for(int k=lgN-1;~k;k--) if(fa[x][k]!=fa[y][k]) x=fa[x][k],y=fa[y][k];
    return fa[x][0];
}

inline void Insert(int x,int y,bitset<N> &b){
    while(x!=y) b.set(a[x],1),x=fa[x][0];
    b.set(a[y],1);
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;
        AdEg(u,v),AdEg(v,u);
    }

    int B=sqrt(n);
    for(int i=1;i<=B;i++) imp[i]=i;
    mt19937 rng(4649);
    shuffle(imp+1,imp+n+1,rng);
    for(int i=1;i<=n;i++) if(imp[i]) p[imp[i]]=i;
    dep[1]=1,DFS(1,0);

    vector<int> val({-1});
    for(int i=1;i<=n;i++) val.push_back(a[i]);
    sort(val.begin(),val.end());
    val.erase(unique(val.begin(),val.end()),val.end());
    for(int i=1;i<=n;i++) a[i]=lower_bound(val.begin(),val.end(),a[i])-val.begin();

    for(int i=1;i<=B;i++){
        int x=p[i];
        if(!anc[x]) continue ;
        int j=imp[anc[x]];
        while(true){
            s[i][j].set(a[x],1);
            x=fa[x][0];
            if(imp[x]) break ;
        }
    }
    for(int i=1;i<=B;i++){
        int x=anc[p[i]];
        while(anc[x]){
            int j=imp[x],k=imp[anc[x]];
            s[i][k]=s[i][j]|s[j][k];
            x=anc[x];
        }
    }

    Init();
    int ans=0;
    while(m--){
        int x,y;
        cin>>x>>y;
        x^=ans;
        int lc=LCA(x,y);
        bitset<N> res;
        res.reset();
        
        if(dep[anc[x]]>=dep[lc]){
            Insert(x,anc[x],res);
            int i=imp[anc[x]],cur=anc[x];
            while(dep[anc[cur]]>=dep[lc]) cur=anc[cur];
            int j=imp[cur];
            res|=s[i][j];
            Insert(cur,lc,res);
        }else Insert(x,lc,res);

        if(dep[anc[y]]>=dep[lc]){
            Insert(y,anc[y],res);
            int i=imp[anc[y]],cur=anc[y];
            while(dep[anc[cur]]>=dep[lc]) cur=anc[cur];
            int j=imp[cur];
            res|=s[i][j];
            Insert(cur,lc,res);
        }else Insert(y,lc,res);

        cout<<(ans=res.count())<<endl;
    }

    return 0;
}