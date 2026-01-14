#include<bits/stdc++.h>

using namespace std;

#define ssiz(x) (signed)x.size()
const int N=1e6+9;

struct Node{
    int lc,rc,cnt,siz;
    void Init(){lc=rc=cnt=siz=0;}
}tr[N<<6];
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc
#define cnt(x) tr[x].cnt
#define siz(x) tr[x].siz

int trs[N<<6],cnt,ttop;
inline int Allc(){return ttop?trs[ttop--]:++cnt;}
inline void Erase(int x){tr[x].Init(),trs[++ttop]=x;}
inline void PushUp(int x){siz(x)=siz(lc(x))+siz(rc(x)),cnt(x)=cnt(lc(x))+cnt(rc(x));}
void Insert(int &x,int L,int R,int pos,int t){
    if(!x) x=Allc();
    if(L==R){
        siz(x)+=t;
        cnt(x)++;
        return ;
    }
    int mid=(L+R)>>1;
    if(pos<=mid) Insert(lc(x),L,mid,pos,t);
    else Insert(rc(x),mid+1,R,pos,t);
    PushUp(x);
}
void Merge(int &x,int &y,int L,int R){
    if(!x||!y) return x|=y,void();
    if(L==R){
        siz(x)+=siz(y);
        cnt(x)+=cnt(y);
        return Erase(y);
    }
    int mid=(L+R)>>1;
    Merge(lc(x),lc(y),L,mid);
    Merge(rc(x),rc(y),mid+1,R);
    PushUp(x),Erase(y);
}
void Split(int &x,int &y,int L,int R,int k,int op){
    if(!x||k==cnt(x)) return ;
    if(!k) return y=x,x=0,void();
    if(!y) y=Allc();
    if(L==R){
        cnt(y)=cnt(x)-k;
        cnt(x)=k;
        if(!cnt(x)) siz(y)=siz(x);
        return ;
    }
    int mid=(L+R)>>1;
    if(!op){
        Split(lc(x),lc(y),L,mid,min(k,cnt(lc(x))),op);
        Split(rc(x),rc(y),mid+1,R,max(k-cnt(lc(x)),0),op);
    }else{
        Split(rc(x),rc(y),mid+1,R,min(k,cnt(rc(x))),op);
        Split(lc(x),lc(y),L,mid,max(k-cnt(rc(x)),0),op);
    }
    PushUp(x),PushUp(y);
}
int Query(int x,int L,int R,int k,int op){
    if(!k||!x) return 0;
    if(k==cnt(x)) return siz(x);
    if(L==R) return siz(x);
    int mid=(L+R)>>1;
    if(!op){
        if(k<=cnt(lc(x))) return Query(lc(x),L,mid,k,op);
        else return siz(lc(x))+Query(rc(x),mid+1,R,k-cnt(lc(x)),op);
    }else{
        if(k<=cnt(rc(x))) return Query(rc(x),mid+1,R,k,op);
        else return siz(rc(x))+Query(lc(x),L,mid,k-cnt(rc(x)),op);
    }
}

int t[N],vis[N],a[N],n,q;
void Add(int x,int k){while(x<=n){t[x]+=k,x+=x&-x;}}
int Ask(int x){int sum=0;while(x){sum+=t[x],x&=x-1;}return sum;}

struct Seg{
    mutable int l,r,op,root;
    Seg(){}
    Seg(int _l,int _r,int _o,int _rt){l=_l,r=_r,op=_o,root=_rt;}
    bool operator <(Seg s)const{return l<s.l;}
};
set<Seg> s;
inline auto Locate(int pos){return pos&&pos<=n?--s.upper_bound(Seg(pos,0,0,0)):s.end();}
void SplitAt(int pos){
    auto it=Locate(pos);
    if(it==s.end()||it->l==pos) return ;
    Seg lt(it->l,pos-1,it->op,it->root),rt(pos,it->r,it->op,0);
    Add(it->r,-siz(it->root));
    s.erase(it);
    Split(lt.root,rt.root,1,n,lt.r-lt.l+1,lt.op);
    Add(lt.r,siz(lt.root));
    Add(rt.r,siz(rt.root));
    s.insert(lt);
    s.insert(rt);
}
void Sort(int l,int r,int op){
    SplitAt(l),SplitAt(r+1);
    auto lt=Locate(l),rt=Locate(r+1);
    Seg tmp(l,r,op,0);
    for(auto it=lt;it!=rt;it++){
        Add(it->r,-siz(it->root));
        Merge(tmp.root,it->root,1,n);
    }
    s.erase(lt,rt);
    Add(tmp.r,siz(tmp.root));
    s.insert(tmp);
}
int QueryAt(int pos){
    auto it=Locate(pos);
    return Ask(it->l-1)+Query(it->root,1,n,pos-it->l+1,it->op);
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'

    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++){
        int root=Allc();
        Insert(root,1,n,a[i],!vis[a[i]]);
        s.insert(Seg(i,i,0,root));
        if(!vis[a[i]]) Add(i,1),vis[a[i]]=1;
    }

    int lst=0;
    while(q--){
        int l,r,x;
        cin>>l>>r>>x;
        l^=lst,r^=lst,x^=lst;
        int op=l>r;
        if(op) swap(l,r);
        Sort(l,r,op);
        cout<<(lst=QueryAt(x))<<endl;
    }

    return 0;
}