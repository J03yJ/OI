#include<bits/stdc++.h>

using namespace std;

const int N=1e6+9;
const int p=1e9+7;

int a[N],f[N],lst[3];

int main(){
    string s;
    cin>>s;
    int n=s.size();
    s=" "+s;

    for(int i=1;i<=n;i++) a[i]=s[i]-'a'+1;

    bool err=1;
    for(int i=1;i<n;i++) if(a[i]==a[i+1]) err=0;
    if(err){
        cout<<1<<endl;
        return 0;
    }

    int cur=0;
    for(int i=1;i<=n;i++){
        cur=(cur+a[i])%3;
        if(cur) f[i]=1;
        for(int k:{(cur+1)%3,(cur+2)%3}) f[i]=(f[i]+f[lst[k]])%p;
        lst[cur]=i;
    }

    cout<<f[n]<<endl;
    
    return 0;
}