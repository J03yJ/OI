#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;

int a[N],n,k;

int main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];

    for(int i=1;i<n;i++){
        if(a[i]+a[i+1]>=k){
            cout<<"Possible"<<endl;
            for(int j=1;j<i;j++) cout<<j<<endl;
            for(int j=n-1;j>i;j--) cout<<j<<endl;
            cout<<i<<endl;
            return 0;
        }
    }

    cout<<"Impossible"<<endl;

    return 0;
}