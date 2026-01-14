#include<bits/stdc++.h>

using namespace std;

#define int long long
const int mod=998244353;
const int INV2=(mod+1)>>1;
    
int n;
void And(vector<int> &a,int flag){
    for(int i=0;i<n;i++){
        for(int j=0,k=1<<i;j<(1<<n);j++){
            if(j&k) continue ;
            a[j]=(a[j]+flag*a[j+k]%mod)%mod;
        }
    }
}
void Or(vector<int> &a,int flag){
    for(int i=0;i<n;i++){
        for(int j=0,k=1<<i;j<(1<<n);j++){
            if(j&k) continue ;
            a[j+k]=(a[j+k]+flag*a[j]%mod)%mod;
        }
    }
}
void Xor(vector<int> &a,int flag){
    for(int i=0;i<n;i++){
        for(int j=0,k=1<<i;j<(1<<n);j++){
            if(j&k) continue ;
            int x=a[j],y=a[j+k];
            a[j]=(x+y)%mod*flag%mod;
            a[j+k]=(x-y+mod)%mod*flag%mod;
        }
    }
}

signed main(){
    cin>>n;
    vector<int> a(1<<n,0),b(1<<n,0),c(1<<n,0);
    for(int i=0;i<(1<<n);i++) cin>>a[i];
    for(int i=0;i<(1<<n);i++) cin>>b[i];

    Or(a,1),Or(b,1);
    for(int i=0;i<(1<<n);i++) c[i]=a[i]*b[i]%mod;
    Or(a,mod-1),Or(b,mod-1),Or(c,mod-1);
    for(int i=0;i<(1<<n);i++) cout<<c[i]<<' ';cout<<endl;

    And(a,1),And(b,1);
    for(int i=0;i<(1<<n);i++) c[i]=a[i]*b[i]%mod;
    And(a,mod-1),And(b,mod-1),And(c,mod-1);
    for(int i=0;i<(1<<n);i++) cout<<c[i]<<' ';cout<<endl;

    Xor(a,1),Xor(b,1);
    for(int i=0;i<(1<<n);i++) c[i]=a[i]*b[i]%mod;
    Xor(a,INV2),Xor(b,INV2),Xor(c,INV2);
    for(int i=0;i<(1<<n);i++) cout<<c[i]<<' ';cout<<endl;

    return 0;
}