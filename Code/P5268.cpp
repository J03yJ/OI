#include<bits/stdc++.h>

using namespace std;

const int N=5e4+9;
using lint=long long;

int a[N],n,m;
lint ans[N];
vector<array<int,4>> q;

int blk[N],cnt1[N],cnt2[N],B;
void Init(){
    B=sqrt(n);
    for(int i=1;i<=n;i++) blk[i]=(i-1)/B+1;
    sort(q.begin(),q.end(),[](auto x,auto y){
        if(blk[x[1]]^blk[y[1]]) return blk[x[1]]<blk[y[1]];
        else return x[2]<y[2];
    });
}
void MoAlgo(){
    lint res=0;
    int i=0,j=0;
    for(auto t:q){
        while(i<t[1]) i++,res+=cnt2[a[i]],cnt1[a[i]]++;
        while(j<t[2]) j++,res+=cnt1[a[j]],cnt2[a[j]]++;
        while(i>t[1]) cnt1[a[i]]--,res-=cnt2[a[i]],i--;
        while(j>t[2]) cnt2[a[j]]--,res-=cnt1[a[j]],j--;
        ans[t[0]]+=t[3]*res;
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    cin>>m;
    for(int i=1,l1,l2,r1,r2;i<=m;i++){
        cin>>l1>>r1>>l2>>r2;
        q.push_back({i,r1,r2,1});
        if(l2>1) q.push_back({i,r1,l2-1,-1});
        if(l1>1) q.push_back({i,l1-1,r2,-1});
        if(l1>1&&l2>1) q.push_back({i,l1-1,l2-1,1});
    }

    Init();
    MoAlgo();
    for(int i=1;i<=m;i++) cout<<ans[i]<<endl;

    return 0;
}