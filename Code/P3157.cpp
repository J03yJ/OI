#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

const int N=1e5+9;
#define endl '\n'

cc_hash_table<int,gp_hash_table<int,int>> tr;
int Max,Mbx;
void insert(tuple<int,int,int> t,int k){
    int x=get<1>(t);
    while(x<=Max){
        int y=get<2>(t);
        while(y<=Mbx){
            tr[x][y]+=k;
            y+=y&-y;
        }
        x+=x&-x;
    }
}
int ask(tuple<int,int,int> t){
    int x=get<1>(t),ans=0;
    while(x){
        int y=get<2>(t);
        while(y){
            ans+=tr[x][y];
            y&=y-1;
        }
        x&=x-1;
    }
    return ans;
}
int ask(int l,int r,int L,int R){
    if(l>r||L>R) return 0;
    return ask(make_tuple(0,r,R))-ask(make_tuple(0,l-1,R))-ask(make_tuple(0,r,L-1))+ask(make_tuple(0,l-1,L-1));
}

int a[N],ra[N];

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n,m;
    cin>>n>>m;

    Max=Mbx=n;
    
    long long ans=0;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        ra[a[i]]=i;
        insert(make_tuple(0,i,a[i]),1);
        ans+=ask(1,i-1,a[i]+1,n);
    }

    while(m--){
        cout<<ans<<endl;
        int pos;
        cin>>pos;
        pos=ra[pos];

        insert(make_tuple(0,pos,a[pos]),-1);
        ans-=ask(1,pos-1,a[pos]+1,n);
        ans-=ask(pos+1,n,1,a[pos]-1);
    }

    return 0;
}