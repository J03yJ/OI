#include<bits/stdc++.h>

using namespace std;

#define fir(x) (x).first
#define sec(x) (x).second
#define ssiz(x) (signed)x.size()
using pii=pair<int,int>;
template<class T1,class T2> using umap=unordered_map<T1,T2>;

const int N=2e6+9;
const int lgN=2e1;
const int mod=998244353;
inline void AddAs(int &x,int y){x+=y;if(x>=mod) x-=mod;}
inline void SubAs(int &x,int y){x-=y;if(x<0) x+=mod;}
inline int Add(int x,int y){x+=y;if(x>=mod) x-=mod;return x;}
inline int Sub(int x,int y){x-=y;if(x<0) x+=mod;return x;}
inline int QPow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=1ll*res*x%mod;
        x=1ll*x*x%mod;
        y>>=1;
    }
    return res;
}
#define Inv(x) QPow(x,mod-2)

struct Data{
    int cnt,sum;
    Data(){}
    Data(int x,int y){cnt=x,sum=y;}
    inline Data operator *(Data x){
        return Data(1ll*cnt*x.cnt%mod,Add(1ll*cnt*x.sum%mod,1ll*x.cnt*sum%mod));
    }
    inline Data operator /(Data x){
        Data y;
        y.cnt=1ll*cnt*Inv(x.cnt)%mod;
        y.sum=1ll*Sub(sum,1ll*x.sum*y.cnt%mod)*Inv(x.cnt)%mod;
        return y;
    }
};

int fi[N],ne[N<<1],to[N<<1],w[N<<1],adj,n,m,q;
inline void AddEdge(int x,int y,int z){
    ne[++adj]=fi[x];
    fi[x]=adj;
    to[adj]=y;
    w[adj]=z;
}

struct Almond{
    umap<int,vector<pii>> e;
    umap<int,int> d,adis,bdis,id,tick;
    Almond(){
        e.reserve(2),d.reserve(2);
        adis.reserve(2),bdis.reserve(2);
        id.reserve(2),tick.reserve(2);
    }
    vector<int> ver;
    int topa=0,topb=0,esum=0,pcnt=0,dcnt=0,scnt=0;
    inline bool Find(int x){return d[x];}
    inline void Insert(int x){ver.push_back(x),d[x]=1;}
    inline void Insert(int x,int y,int z){
        e[x].push_back({y,z}),d[y]++;
        e[y].push_back({x,z}),d[x]++;
        AddAs(esum,z);
    }
    inline void Count(int x,int fa){
        if(x==topb) return pcnt++,void();
        tick[x]=++dcnt;
        if(x!=topa){
            if(!id[fa]) id[x]=++scnt;
            else id[x]=id[fa];
        }
        for(pii p:e[x]) if(fir(p)!=fa) Count(fir(p),x);
    }
    inline void GetTop(){
        for(pii p:d) if(!topa||sec(p)>d[topa]) topa=fir(p);
        for(pii p:d) if(fir(p)!=topa&&(!topb||sec(p)>d[topb])) topb=fir(p);
        if(topa>topb) swap(topa,topb);
        Count(topa,-1);
    }
    inline void InitDistA(int x,int fa){
        if(x==topb) return ;
        for(pii p:e[x]) if(fir(p)!=fa) adis[fir(p)]=Add(adis[x],sec(p)),InitDistA(fir(p),x);
    }
    inline void InitDistB(int x,int fa){
        if(x==topa) return ;
        for(pii p:e[x]) if(fir(p)!=fa) bdis[fir(p)]=Add(bdis[x],sec(p)),InitDistB(fir(p),x);
    } 
    inline void InitDist(){InitDistA(topa,-1),InitDistB(topb,-1);}
    inline Data Calc(int x,int y){
        assert(Find(x)&&Find(y));
        if(!id[x]&&!id[y]) return Data(pcnt,esum);
        else if(!id[x]){
            if(x==topa) return Data(pcnt,Add(esum,1ll*Sub(pcnt,2)*bdis[y]%mod));
            else if(x==topb) return Data(pcnt,Add(esum,1ll*Sub(pcnt,2)*adis[y]%mod));
            else assert(0);
        }else if(!id[y]){
            if(y==topa) return Data(pcnt,Add(esum,1ll*Sub(pcnt,2)*bdis[x]%mod));
            else if(y==topb) return Data(pcnt,Add(esum,1ll*Sub(pcnt,2)*adis[x]%mod));
            else assert(0);
        }else if(id[x]==id[y]){
            if(tick[x]>tick[y]) swap(x,y);
            int tmp=Add(adis[x],bdis[y]);
            return Data(pcnt,Add(esum,1ll*Sub(pcnt,2)*tmp%mod));
        }else{
            int tmp=Add(Add(adis[x],bdis[x]),Add(adis[y],bdis[y]));
            return Data(2ll*(pcnt-1)%mod,Add(2ll*esum%mod,1ll*Sub(pcnt,3)*tmp%mod));
        }
    }
};
vector<int> stk;
vector<Almond> vdcc;
int dfn[N],low[N],dcnt,tot;
inline void Tarjan(int x,int fa){
    dfn[x]=low[x]=++dcnt,stk.push_back(x);
    for(int i=fi[x];i;i=ne[i]){
        int y=to[i];
        if(!dfn[y]){
            Tarjan(y,x);
            low[x]=min(low[x],low[y]);
            if(low[y]>=dfn[x]){
                vdcc.push_back(Almond());
                while(ssiz(stk)){
                    int p=stk.back();
                    stk.pop_back();
                    vdcc.back().Insert(p);
                    if(p==y) break ;
                }
                vdcc.back().Insert(x);
                tot++;
            }
        }else if(y!=fa) low[x]=min(low[x],dfn[y]);
    }
}

vector<int> e[N<<1];
int fa[N][lgN],dep[N];
Data f[N];
inline void DFS(int x){
    for(int y:e[x]){
        if(y==fa[x][0]) continue ;
        fa[y][0]=x,dep[y]=dep[x]+1;
        DFS(y);
    }
}
inline void Build(int x){
    if(x<=n&&dep[x]>1){
        int y=fa[fa[x][0]][0],id=fa[x][0]-n-1;
        f[x]=f[y]*vdcc[id].Calc(x,y);
    }
    for(int y:e[x]){
        if(y==fa[x][0]) continue ;
        Build(y);
    }
}
inline void Init(){
    f[1]=Data(1,0),dep[1]=1,Build(1);
    for(int k=1;k<=__lg(tot);k++){
        for(int i=1;i<=tot;i++) fa[i][k]=fa[fa[i][k-1]][k-1];
    }
}
inline int LCA(int x,int y){
    if(dep[x]<dep[y]) swap(x,y);
    for(int k=__lg(tot);~k;k--) if(dep[fa[x][k]]>=dep[y]) x=fa[x][k];
    if(x==y) return x;
    for(int k=__lg(tot);~k;k--) if(fa[x][k]!=fa[y][k]) x=fa[x][k],y=fa[y][k];
    return fa[x][0];
}
inline int Approx(int x,int y){
    for(int k=__lg(tot);~k;k--) if(dep[fa[x][k]]>dep[y]) x=fa[x][k];
    return x;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n>>m>>q;
    for(int i=1,u,v,w;i<=m;i++) cin>>u>>v>>w,AddEdge(u,v,w),AddEdge(v,u,w);
    tot=n;

    Tarjan(1,-1);
    for(int i=n+1;i<=n+ssiz(vdcc);i++){
        for(int x:vdcc[i-n-1].ver){
            e[x].push_back(i);
            e[i].push_back(x);
        }
    }
    DFS(1);
    for(int x=1;x<=n;x++){
        for(int i=fi[x];i;i=ne[i]){
            int y=to[i];
            if(x<y) continue ;
            vdcc[(dep[x]<dep[y]?fa[y][0]:fa[x][0])-n-1].Insert(x,y,w[i]);
        }
    }
    for(int i=0;i<ssiz(vdcc);i++){
        vdcc[i].GetTop();
        vdcc[i].InitDist();
    }
    Init();

    while(q--){
        int x,y;
        cin>>x>>y;
        int lca=LCA(x,y);
        if(lca<=n) cout<<((f[x]/f[lca])*(f[y]/f[lca])).sum<<endl;
        else{
            int p=Approx(x,lca),q=Approx(y,lca),id=lca-n-1;
            cout<<((f[x]/f[p])*(f[y]/f[q])*vdcc[id].Calc(p,q)).sum<<endl;
        }
    }

    return 0;
}