#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N=5e5+9;
const int mod=1e9+7;

int a[N],b[N],now,n,q;
int tr[N];
void Add(int x,int k){
    while(x<=n){
        tr[x]+=k;
        x+=x&-x;
    }
}
int Ask(int x){
    int sum=0;
    while(x){
        sum+=tr[x];
        x&=x-1;
    }
    return sum;
}
int Ask(int l,int r){return Ask(r)-Ask(l-1);}

set<pair<int,int>> s,t;
long long ans,ant;
long long F(int l,int r){
    int len=r-l+1;
    return 1ll*len*(len+1)/2*(r+1)-1ll*len*(len+1)*(len*2+1)/6;
}
void Join(set<pair<int,int>> &s,int l,int r,long long &ans){
    ans+=F(l,r);
    s.insert({l,r});
}
void Kick(set<pair<int,int>> &s,auto it,long long &ans){
    ans-=F(it->first,it->second);
    s.erase(it);
}
void Insert(set<pair<int,int>> &s,int pos,long long &ans){
    auto rit=s.upper_bound({pos,n+1});
    int l=pos,r=pos;
    if(rit!=s.end()&&rit->first==pos+1){
        r=rit->second;
        Kick(s,rit,ans);
    }
    rit=s.upper_bound({pos,n+1});
    if(rit!=s.begin()){
        auto lit=--rit;
        if(lit->second==pos-1){
            l=lit->first;
            Kick(s,lit,ans);
        }
    }
    Join(s,l,r,ans);
}
void Erase(set<pair<int,int>> &s,int pos,long long &ans){
    auto it=--s.upper_bound({pos,n+1});
    if(it->first==pos&&it->second==pos) Kick(s,it,ans);
    else{
        int l=it->first,r=it->second;
        Kick(s,it,ans);
        if(l<pos) Join(s,l,pos-1,ans);
        if(r>pos) Join(s,pos+1,r,ans);
    }
}
void Modify(int pos,int k){
    if(a[pos]==5){
        if(k!=5){
            Erase(s,pos,ans);
            Erase(t,n-pos+1,ant);
        }
    }else{
        if(k==5){
            Insert(s,pos,ans);
            Insert(t,n-pos+1,ant);
        }
    }
    Add(pos,k-a[pos]);
    a[pos]=k;
    b[n-pos+1]=k;
}

signed main(){
    cin>>n>>q;
    for(int i=1,x;i<=n;i++){
        cin>>x;
        Modify(i,x);
    }
    while(q--){
        int op;
        cin>>op;
        if(op==1){
            int x,y;
            cin>>x>>y;
            if(now) x=n-x+1;
            Modify(x,y);
        }else if(op==2) now^=1;
        else if(op==3) cout<<(now?ant:ans)%mod<<endl;
        else if(op==4){
            int x,y;
            cin>>x>>y;
            cout<<(now?Ask(n-y+1,n-x+1):Ask(x,y))<<endl;
        }
        // for(auto p:s) cout<<p.first<<' '<<p.second<<endl;
        // cout<<endl;
    }

    return 0;
}