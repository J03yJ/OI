#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>

using namespace std;

using ll=long long;
using ull=unsigned ll;
const int N=1e5+9;
const int M=1e6+9;

int a[N],ql[M],qr[M],blk[N],p[M],ans[M],n,m;
__gnu_pbds::gp_hash_table<int,int> mp;
int val[N],tot;

#define Bit(x) (1ull<<(x))
ull b[N],mask[65];
const int d=6,w=64,msk=63;
void InitMask(){for(int i=1;i<=64;i++) mask[i]=mask[i-1]<<1|1;}
void Insert(int x,int &cnt){
    int i=x>>d,p=x&msk,flag=0;
    if(b[i]>mask[w]-Bit(p)) flag=1;
    cnt-=__builtin_popcountll(b[i]);
    b[i]+=Bit(p);
    cnt+=__builtin_popcountll(b[i]);
    if(flag){
        while(b[++i]==mask[w]) b[i]=0,cnt-=w;
        cnt-=__builtin_popcountll(b[i]);
        b[i]++;
        cnt+=__builtin_popcountll(b[i]);
    }
}
void Erase(int x,int &cnt){
    int i=x>>d,p=x&msk,flag=0;
    if(b[i]<Bit(p)) flag=1;
    cnt-=__builtin_popcountll(b[i]);
    b[i]-=Bit(p);
    cnt+=__builtin_popcountll(b[i]);
    if(flag){
        while(!b[++i]) b[i]=mask[w],cnt+=w;
        cnt-=__builtin_popcountll(b[i]);
        b[i]--;
        cnt+=__builtin_popcountll(b[i]);
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=m;i++) cin>>ql[i]>>qr[i];

    for(int i=1,pos;i<=n;i++){
        pos=a[i];
        while(mp[pos]) mp[pos++]=0;
        mp[pos]=1;
    }
    for(auto p:mp) val[++tot]=p.first;
    sort(val+1,val+tot+1);
    for(int i=1;i<=n;i++) a[i]=lower_bound(val+1,val+tot+1,a[i])-val;

    InitMask();
    int B=ceil(n/sqrt(m));
    for(int i=1;i<=n;i++) blk[i]=(i-1)/B+1;
    iota(p+1,p+m+1,1);
    sort(p+1,p+m+1,[](int x,int y){
        return blk[ql[x]]^blk[ql[y]]?blk[ql[x]]<blk[ql[y]]:qr[x]<qr[y];
    });
    for(int i=1,l=1,r=0,cnt=0;i<=m;i++){
        while(r<qr[p[i]]) Insert(a[++r],cnt);
        while(l>ql[p[i]]) Insert(a[--l],cnt);
        while(r>qr[p[i]]) Erase(a[r--],cnt);
        while(l<ql[p[i]]) Erase(a[l++],cnt);
        ans[p[i]]=cnt;
    }

    for(int i=1;i<=m;i++) cout<<ans[i]<<endl;

    return 0;
}