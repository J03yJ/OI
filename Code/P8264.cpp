#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
#define fir(x) (x).first
#define sec(x) (x).second
using pii=pair<int,int>;
const int N=1e5+9;
const int SQ=4e2+9;
const int V=1e5;

struct Node{
    int lc,rc,siz;
    int mx,mn,add,rev;
}tr[N<<5];
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc
#define siz(x) tr[x].siz
#define mx(x) tr[x].mx
#define mn(x) tr[x].mn
#define add(x) tr[x].add
#define rev(x) tr[x].rev

int cnt;
inline int Allc(){return ++cnt;}
inline void Clear(){while(cnt) memset(&tr[cnt],0,sizeof(tr[cnt])),cnt--;}
inline void PushRev(int x){
    rev(x)^=1;
    swap(mx(x),mn(x));
    swap(lc(x),rc(x));
    add(x)=-add(x),mx(x)=-mx(x),mn(x)=-mn(x);
}
inline void PushAdd(int x,int k){
    add(x)+=k;
    mx(x)+=k,mn(x)+=k;
}
inline void PushDown(int x){
    if(rev(x)) PushRev(lc(x)),PushRev(rc(x)),rev(x)=0;
    if(add(x)) PushAdd(lc(x),add(x)),PushAdd(rc(x),add(x)),add(x)=0;
}
inline void PushUp(int x){
    if(!lc(x)) siz(x)=1;
    else{
        siz(x)=siz(lc(x))+siz(rc(x));
        mn(x)=mn(lc(x));
        mx(x)=mx(rc(x));
    }
}
inline int Bind(int x,int y){
    int z=Allc();
    lc(z)=x,rc(z)=y;
    return PushUp(z),z;
}

inline int Merge(int x,int y){
    if(!x||!y) return x|y;
    // if(4*min(siz(x),siz(y))>=siz(x)+siz(y)) return Bind(x,y);
    if(4*min(siz(x),siz(y))>=siz(x)+siz(y)){
        int z=Bind(x,y);
        // cout<<"Merge "<<x<<' '<<y<<" -> "<<z<<endl;
        // cout<<" - "<<siz(x)<<' '<<mn(x)<<' '<<mx(x)<<endl;
        // cout<<" - "<<siz(y)<<' '<<mn(y)<<' '<<mx(y)<<endl;
        // cout<<" - "<<siz(z)<<' '<<mn(z)<<' '<<mx(z)<<endl;
        return z;
    }
    if(siz(x)>=siz(y)){
        PushDown(x);
        if(5*siz(lc(x))>=siz(x)+siz(y)) return Merge(lc(x),Merge(rc(x),y));
        else return PushDown(rc(x)),Merge(Merge(lc(x),lc(rc(x))),Merge(rc(rc(x)),y));
    }else{
        PushDown(y);
        if(5*siz(rc(y))>=siz(x)+siz(y)) return Merge(Merge(x,lc(y)),rc(y));
        else return PushDown(lc(y)),Merge(Merge(x,lc(lc(y))),Merge(rc(lc(y)),rc(y)));
    }
}
inline pii Split(int x,int k){
    if(!x) return {0,0};
    if(!lc(x)&&mx(x)<=k) return {x,0};
    if(!lc(x)&&mx(x)>k) return {0,x};
    PushDown(x);
    if(mx(lc(x))<=k){
        pii tmp=Split(rc(x),k);
        // cout<<"Split "<<x<<" | "<<k<<" : "<<siz(x)<<' '<<mn(x)<<' '<<mx(x)<<endl;
        // cout<<" -> LsM "<<x<<' '<<fir(tmp)<<endl;
        return {Merge(lc(x),fir(tmp)),sec(tmp)};
    }else{
        pii tmp=Split(lc(x),k);
        // cout<<"Split "<<x<<" | "<<k<<" : "<<siz(x)<<' '<<mn(x)<<' '<<mx(x)<<endl;
        // cout<<" -> RsM "<<sec(tmp)<<' '<<x<<endl;
        return {fir(tmp),Merge(sec(tmp),rc(x))};
    }
}
inline int Join(int x,int y){
    if(!x||!y) return x|y;
    if(mx(x)<=mn(y)) return Merge(x,y);
    if(mx(y)<=mn(x)) return Merge(y,x);
    if(siz(x)<siz(y)) swap(x,y);
    int k=mx(lc(x));
    pii xrt=Split(x,k),yrt=Split(y,k);
    return Merge(Join(fir(xrt),fir(yrt)),Join(sec(xrt),fir(yrt)));
}
inline void PushAll(int x){
    if(!lc(x)) return ;
    PushDown(x);
    PushAll(lc(x));
    PushAll(rc(x));
}

inline int Make(int l,int r){
    if(l==r) return l;
    int mid=l+r>>1;
    return Bind(Make(l,mid),Make(mid+1,r));
}
inline int Init(){
    cnt=V;
    for(int j=1;j<=V;j++){
        mx(j)=mn(j)=j;
        siz(j)=1;
    }
    return Make(1,V);
}

int a[N],n,q;
int blk[N],L[N],R[N],to[SQ][N],B;
inline int Brute(int l,int r,int k){
    for(int i=l;i<=r;i++) k=abs(k-a[i]);
    return k;
}
inline int Trans(int l,int r,int k){
    if(blk[l]==blk[r]) return Brute(l,r,k);
    k=Brute(l,R[blk[l]],k);
    for(int i=blk[l]+1;i<blk[r];i++) k=to[i][k];
    k=Brute(L[blk[r]],r,k);
    return k;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i];

    B=sqrt(n);
    for(int i=1;i<=n;i++) blk[i]=(i-1)/B+1;
    for(int i=n;i>=1;i--) L[blk[i]]=i;
    for(int i=1;i<=n;i++) R[blk[i]]=i;
    for(int i=1;i<=blk[n];i++){
        int root=Init();
        cout<<"# "<<i<<' '<<root<<' '<<siz(root)<<endl;
        for(int j=L[i];j<=R[i];j++){
            int t=clock();
            pii tmp=Split(root,a[j]);
            int lt=fir(tmp),rt=sec(tmp);
            cout<<j<<" : "<<a[j]<<' '<<lt<<' '<<rt<<endl;
            cout<<" : "<<siz(lt)<<' '<<mn(lt)<<' '<<mx(lt)<<endl;
            cout<<" : "<<siz(rt)<<' '<<mn(rt)<<' '<<mx(rt)<<endl;
            // PushRev(lt),PushAdd(lt,a[j]);
            // PushAdd(rt,a[j]);
            // root=Join(lt,rt);
            root=Merge(lt,rt);
            cout<<"T = "<<clock()<<' '<<t<<endl;
        }
        PushAll(root);
        for(int j=1;j<=V;j++) to[i][j]=mx(j);
        Clear();
    }

    // int ans=0;
    // while(q--){
    //     int l,r,k;
    //     cin>>l>>r>>k;
    //     l^=ans,r^=ans,k^=ans;
    //     ans=Trans(l,r,k);
    //     cout<<ans<<endl;
    // }
    
    return 0;
}