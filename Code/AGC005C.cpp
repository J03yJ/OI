#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;

int a[N],c[N],up[N],low[N],n;

int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];

    int mx=0;
    for(int i=1;i<=n;i++) mx=max(mx,a[i]);
    up[(mx+1)/2]=low[(mx+1)/2]=mx%2+1;
    for(int i=(mx+1)/2+1;i<=mx;i++) low[i]=2,up[i]=1e9;
    for(int i=1;i<=n;i++) c[a[i]]++;
    for(int i=0;i<mx;i++){
        if(c[i]>up[i]||c[i]<low[i]) return cout<<"Impossible"<<endl,0;
    }
    return cout<<"Possible"<<endl,0;
}