#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;
const int inf=1e9;

struct Node{
    int lc,rc,siz,dep;
    int val;
}tr[N<<2];
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc
#define siz(x) tr[x].siz
#define dep(x) tr[x].dep
#define val(x) tr[x].val

void PushUp(int x){
    if(!lc(x)){
        dep(x)=siz(x)=1;
        return ;
    }
    siz(x)=siz(lc(x))+siz(rc(x));
    dep(x)=max(dep(lc(x)),dep(rc(x)))+1;
    val(x)=max(val(lc(x)),val(rc(x)));
}
void Maintain(int x){
    if(dep(lc(x))>dep(rc(x))+1){
        int y=lc(x);
        if(dep(lc(lc(x)))==dep(rc(x))){
            int z=rc(y);
            rc(y)=lc(z);
            lc(z)=rc(z);
            rc(z)=rc(x);
            rc(x)=z;
            PushUp(z);
        }else{
            lc(x)=lc(y);
            lc(y)=rc(y);
            rc(y)=rc(x);
            rc(x)=y;
        }
        PushUp(y);
    }else if(dep(rc(x))>dep(lc(x))+1){
        int y=rc(x);
        if(dep(rc(rc(x)))==dep(lc(x))){
            int z=lc(y);
            lc(y)=rc(z);
            rc(z)=lc(z);
            lc(z)=lc(x);
            lc(x)=z;
            PushUp(z);
        }else{
            rc(x)=rc(y);
            rc(y)=lc(y);
            lc(y)=lc(x);
            lc(x)=y;
        }
        PushUp(y);
    }
    PushUp(x);
}

int cnt;
int NewNode(int k){
    val(++cnt)=k;
    siz(cnt)=dep(cnt)=1;
    return cnt;
}
void Insert(int x,int k){
    if(!lc(x)){
        lc(x)=NewNode(min(val(x),k));
        rc(x)=NewNode(max(val(x),k));
        PushUp(x);
        return ;
    }
    if(k<=val(lc(x))) Insert(lc(x),k);
    else Insert(rc(x),k);
    Maintain(x);
}
void Erase(int x,int k,int fa){
    if(!lc(x)){
        int x=lc(fa),y=rc(fa);
        if(val(x)==k) tr[fa]=tr[y];
        else if(val(y)==k) tr[fa]=tr[x];
        return ;
    }
    if(k<=val(lc(x))) Erase(lc(x),k,x);
    else Erase(rc(x),k,x);
    Maintain(x);
}
int Rank(int x,int k){
    if(!lc(x)) return 1;
    if(k>val(lc(x))) return Rank(rc(x),k)+siz(lc(x));
    else return Rank(lc(x),k);
}
int Kth(int x,int k){
    if(siz(x)==k) return val(x);
    if(k>siz(lc(x))) return Kth(rc(x),k-siz(lc(x)));
    else return Kth(lc(x),k);
}
int Pre(int x,int k){
    return Kth(x,Rank(x,k)-1);
}
int Suc(int x,int k){
    return Kth(x,Rank(x,k+1));
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #define endl '\n'

    int root=NewNode(inf);

    int q;
    cin>>q;
    while(q--){
        int op,k;
        cin>>op>>k;
        if(op==1) Insert(root,k);
        else if(op==2) Erase(root,k,-1);
        else if(op==3) cout<<Rank(root,k)<<endl;
        else if(op==4) cout<<Kth(root,k)<<endl;
        else if(op==5) cout<<Pre(root,k)<<endl;
        else if(op==6) cout<<Suc(root,k)<<endl;
    }

    return 0;
}