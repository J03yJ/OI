#include<bits/stdc++.h>

using namespace std;

using ll=long long;
const int N=1e5+9;
const int sqN=3.2e2+9;

const int n=1e5;
int blk[N],L[N],R[N],m,B;
int cnt[N],bcnt[N],fa[sqN][N+sqN],nxt[N],tag[N];
ll sum[N],bsum[N];
void InitBlk(){
    B=sqrt(n);
    for(int i=1;i<=n;i++) blk[i]=i/B+1;
    for(int i=1;i<=n;i++) R[blk[i]]=i;
    for(int i=n;i>=1;i--) L[blk[i]]=i;
    for(int d=1;d<=B;d++) iota(fa[d]+1,fa[d]+n+B+1,1);
    for(int i=1;i<=n;i++) nxt[i]=n+1;
    for(int i=1;i<=blk[n];i++) tag[i]=n+1;
}

int Find(int x,int *fa){return x==fa[x]?x:fa[x]=Find(fa[x],fa);}
#define Merge(x,y,fa) fa[Find(y,fa)]=Find(x,fa)

ll GetSum(int l,int r){
    r=min(r,n);
    if(l>r) return 0;
    if(blk[l]==blk[r]) return l==L[blk[l]]?sum[r]:sum[r]-sum[l-1];
    else{
        ll ans=bsum[blk[r]-1]-bsum[blk[l]];
        ans+=sum[r];
        ans+=l==L[blk[l]]?sum[R[blk[l]]]:sum[R[blk[l]]]-sum[l-1];
        return ans;
    }
}
int GetCount(int l,int r){
    r=min(r,n);
    if(l>r) return 0;
    if(blk[l]==blk[r]) return l==L[blk[l]]?cnt[r]:cnt[r]-cnt[l-1];
    else{
        ll ans=bcnt[blk[r]-1]-bcnt[blk[l]];
        ans+=cnt[r];
        ans+=l==L[blk[l]]?cnt[R[blk[l]]]:cnt[R[blk[l]]]-cnt[l-1];
        return ans;
    }
}
void Insert(int pos,int k){
    int t=pos;
    while(t<pos+B&&!GetCount(t,t)) t++;
    for(int d=1;d<B;d++){
        for(int i=min(pos-1,t-d);i>=0&&i>=pos-d&&fa[d][i]==i;i--){
            fa[d][i]=i+d;
        }
    }
    if(k){
        for(int i=pos;i>=L[blk[pos]];i--) nxt[i]=min(nxt[i],pos);
        for(int i=blk[pos]-1;i>=1;i--) tag[i]=min(tag[i],pos);
    }
    for(int i=pos;i<=R[blk[pos]];i++) cnt[i]++,sum[i]+=k;
    for(int i=blk[pos];i<=blk[n];i++) bcnt[i]++,bsum[i]+=k;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    InitBlk();
    cin>>m;
    while(m--){
        int op;
        cin>>op;
        if(op==1){
            int a,b;
            cin>>a>>b;
            Insert(a,b);
        }else if(op==2){
            int d,cur=0,ans=0;
            cin>>d;
            while(d>0){
                ans++;
                if(cur>=n) break ;
                if(!GetCount(cur+1,cur+d)) break ;
                if(d<B){
                    int pos=min(min(nxt[cur+1],tag[blk[cur+1]]),Find(cur,fa[d]));
                    assert(Find(cur,fa[d])>=cur);
                    int tmp=(pos-cur-1)/d;
                    ans+=tmp,cur+=d*tmp;
                }
                cur+=d;
                d-=GetSum(cur-d+1,cur);
            }
            cout<<ans<<endl;
        }
    }

    return 0;
}