#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;
const int lgN=2e1;

int a[N],b[N],c[N],p[N],tr[N],n;
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
int Ask(int l,int r){
    if(l>r) return 0;
    else return Ask(r)-Ask(l-1);
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i],p[a[i]]=i;
    for(int i=1;i<=n;i++) cin>>b[i],b[i]=p[b[i]];

    long long sum=0;
    for(int i=1;i<=n;i++){
        sum+=c[i]=Ask(b[i],n);
        Add(b[i],1);
    }
    if(sum&1){
        cout<<-1<<endl;
        return 0;
    }

    sum>>=1;
    for(int i=1;i<=n;i++){
        if(sum<c[i]){
            sort(b+1,b+i);
            while(sum--) swap(b[i-1],b[i]),i--;
            break ;
        }
        sum-=c[i];
    }
    for(int i=1;i<=n;i++) cout<<a[b[i]]<<' ';cout<<endl;

    return 0;
}