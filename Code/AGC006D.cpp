#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;

int a[N<<1],b[N<<1],n;
bool Check(int k){
    for(int i=1;i<=n*2-1;i++) b[i]=a[i]>=k;
    for(int d=0;d<n-1;d++){
        if(b[n-d]&&b[n-d-1]) return 1;
        if(b[n+d]&&b[n+d+1]) return 1;
        if(!b[n-d]&&!b[n-d-1]) return 0;
        if(!b[n+d]&&!b[n+d+1]) return 0;
    }
    return b[1];
}

int main(){
    cin>>n;
    for(int i=1;i<n*2;i++) cin>>a[i];

    int l=0,r=n*2;
    while(l+1<r){
        int mid=l+r>>1;
        if(Check(mid)) l=mid;
        else r=mid;
    }

    cout<<l<<endl;

    return 0;
}