#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;
const int mod=1e9+7;
inline void AddAs(int &x,int y){x+=y;if(x>=mod) x-=mod;}
inline void SubAs(int &x,int y){x-=y;if(x<0) x+=mod;}
inline int Add(int x,int y){x+=y;return x>=mod?x-mod:x;}
inline int Sub(int x,int y){x-=y;return x<0?x+mod:x;}

int a[N],n,m;

int blk[N],L[N],R[N],sumt[N],t[N],B;
inline void Modify(int pos,int k){AddAs(t[pos],k),AddAs(sumt[blk[pos]],k);}
inline int Query(int l,int r){
    int sum=0;
    if(blk[l]==blk[r]){
        for(int i=l;i<=r;i++) AddAs(sum,t[i]);
        return sum;
    }
    if(l!=L[blk[l]]) for(int i=l;i<=R[blk[l]];i++) AddAs(sum,t[i]);
    if(r!=R[blk[r]]) for(int i=L[blk[r]];i<=r;i++) AddAs(sum,t[i]);
    int itl=l==L[blk[l]]?blk[l]:blk[l]+1;
    int itr=r==R[blk[r]]?blk[r]:blk[r]-1;
    for(int i=itl;i<=itr;i++) AddAs(sum,sumt[i]);
    return sum;
}

const int sqN=5e2+9;
int msum[sqN],mpre[sqN][sqN],msuf[sqN][sqN];

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) AddAs(a[i],a[i-1]);

    B=sqrt(n);
    for(int i=1;i<=n;i++) blk[i]=(i-1)/B+1;
    for(int i=1;i<=n;i++) R[blk[i]]=i;
    for(int i=n;i>=1;i--) L[blk[i]]=i;

    while(m--){
        int op;
        cin>>op;
        if(op==2){
            int l,r;
            cin>>l>>r;
            long long ans=Query(l,r);
            ans+=Sub(a[r],a[l-1]);
            for(int x=1;x<=B;x++){
                int lpos=l/x+1,rpos=r/x-1;
                if(lpos-1==rpos+1){
                    ans+=l%x==0?mpre[x][r%x]:Sub(mpre[x][r%x],mpre[x][(l-1)%x]);
                    continue ;
                }
                if(rpos>=lpos) ans+=1ll*(rpos-lpos+1)*msum[x]%mod;
                ans+=mpre[x][r%x];
                ans+=msuf[x][l%x];
            }
            cout<<ans%mod<<endl;
        }else{
            int x,y,z;
            cin>>x>>y>>z;
            if(z>=mod) z-=mod;
            if(x>B) for(int cur=y;cur<=n;cur+=x) Modify(cur,z);
            else{
                if(y==x) y=0;
                AddAs(msum[x],z);
                for(int i=0;i<=y;i++) AddAs(msuf[x][i],z);
                for(int i=x-1;i>=y;i--) AddAs(mpre[x][i],z);
            }
        }
    }

    return 0;
}