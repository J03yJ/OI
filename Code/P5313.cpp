#include<bits/stdc++.h>

using namespace std;

#define ssiz(x) (signed)x.size()
#define allc(x) x.begin(),x.end()
using lint=long long;
using ull=unsigned lint;
#define Bit(x) (__int128(1)<<(x))
#define Mask(x) (Bit(x)-1)
const int N=2e5+9;

const int V=1e5+1;
const int d=6,w=Bit(d),msk=Mask(d);
const int lim=64;
struct Bitset{
    int len;
    vector<ull> v;
    inline void Reset(){for(ull &x:v) x=0;}
    inline void Set(){for(ull &x:v) x=~0ull;}
    inline void Init(int x,int k){v.resize(2+(len=x>>d)),k?Set():Reset();}
    inline void Flip(){for(ull &x:v) x=~x;}
    inline void Set1(int pos){v[pos>>d]|=1ull<<(pos&msk);}
    inline void Set0(int pos){v[pos>>d]&=~(1ull<<(pos&msk));}
    inline int operator [](int pos){return v[pos>>d]&(1ull<<(pos%msk));}
    inline int All(){for(ull x:v) if(~x) return 0;return 1;}
    inline int Any(){for(ull x:v) if(x) return 1;return 0;}
    inline int Count(){
        int cnt=0;
        for(ull x:v) cnt+=__builtin_popcountll(x);
        return cnt;
    }
    inline int Mex(){
        for(int i=0;;i++) if(~v[i]) return (i<<d)|__builtin_ctzll(~v[i]);
    }
    inline int Low(){
        for(int i=0;;i++) if(v[i]) return (i<<d)|__builtin_ctzll(v[i]);
    }
    inline void operator &=(Bitset &x){for(int i=0;i<=len;i++) v[i]&=x.v[i];}
    inline Bitset operator ~(){Bitset x=*this;x.Flip();return x;}
    Bitset(){}
    Bitset(int x,int k){this->Init(x,k);}
};
ull mask[65];
void InitMask(){for(int i=0;i<=64;i++) mask[i]=Mask(i);}
#define Lsh(x,p) ((p)>63?0:(x)<<(p))
#define Rsh(x,p) ((p)>63?0:(x)>>(p))
inline void Cpy(Bitset &src,Bitset &dst,int x,int len){
    dst.v.clear(),dst.len=len>>d;
    int i,p;
    while(len>=w){
        i=x>>d,p=x&msk;
        dst.v.push_back(Rsh(src.v[i],p)|Lsh(src.v[i+1],w-p));
        len-=w,x+=w;
    }
    if(len){
        i=x>>d,p=x&msk;
        dst.v.push_back(len<=w-p?Rsh(src.v[i],p)&mask[len]:(Rsh(src.v[i],p)|Lsh(src.v[i+1],w-p))&mask[len]);
    }
    dst.v.push_back(0);
}

int a[N],ql[N],qr[N],qb[N],ans[N],n,m;
vector<int> c[65],q;

int blk[N],cnt[N];
void MoAlgo1(){
    if(!ssiz(q)) return ;
    for(int i=0;i<V;i++) cnt[i]=0;
    int B=ceil(n/sqrt(ssiz(q)));
    for(int i=1;i<=n;i++) blk[i]=(i-1)/B+1;
    sort(allc(q),[](int x,int y)->bool{
        if(blk[ql[x]]^blk[ql[y]]) return blk[ql[x]]<blk[ql[y]];
        else return qr[x]<qr[y];
    });
    
    Bitset vis(V<<1,0),cur,tmp;
    auto Insert=[&vis](int x)->void{if(!cnt[x]++) vis.Set1(x);};
    auto Erase=[&vis](int x)->void{if(!--cnt[x]) vis.Set0(x);};
    int l=1,r=0;
    for(int i:q){
        while(r<qr[i]) Insert(a[++r]);
        while(l>ql[i]) Insert(a[--l]);
        while(r>qr[i]) Erase(a[r--]);
        while(l<ql[i]) Erase(a[l++]);
        Cpy(vis,cur,0,qb[i]);
        while(cur.Any()){
            Cpy(vis,tmp,qb[i]*++ans[i],qb[i]);
            cur&=tmp;
        }
    }
}
int dvd[N],mod[N];
void MoAlgo2(int k){
    if(!ssiz(c[k])) return ;
    int B=ceil(n/sqrt(ssiz(c[k])));
    for(int i=1;i<=n;i++) blk[i]=(i-1)/B+1;
    sort(allc(c[k]),[](int x,int y)->int{
        if(blk[ql[x]]^blk[ql[y]]) return blk[ql[x]]<blk[ql[y]];
        else return qr[x]<qr[y];
    });
    for(int i=0,r=0,q=0;i<V;i++,r++){
        if(r==k) q++,r=0;
        dvd[i]=q,mod[i]=r;
    }

    for(int i=0;i<V;i++) cnt[i]=0;
    vector<Bitset> vis(k,Bitset((V-1)/k+1+1,0));
    int l=1,r=0;
    auto Insert=[&vis,&k](int x)->void{if(!cnt[x]++) vis[mod[x]].Set1(dvd[x]);};
    auto Erase=[&vis,&k](int x)->void{if(!--cnt[x]) vis[mod[x]].Set0(dvd[x]);};
    for(int i:c[k]){
        while(r<qr[i]) Insert(a[++r]);
        while(l>ql[i]) Insert(a[--l]);
        while(r>qr[i]) Erase(a[r--]);
        while(l<ql[i]) Erase(a[l++]);
        for(auto &b:vis) ans[i]=max(ans[i],b.Mex());
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    cin>>m;
    for(int i=1;i<=m;i++){
        cin>>ql[i]>>qr[i]>>qb[i];
        if(qb[i]<=w) c[qb[i]].push_back(i);
        else q.push_back(i);
    }

    InitMask();
    MoAlgo1();
    for(int k=1;k<=lim;k++) MoAlgo2(k);

    for(int i=1;i<=m;i++) cout<<ans[i]<<endl;

    return 0;
}