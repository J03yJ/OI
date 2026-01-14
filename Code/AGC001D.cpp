#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;

int a[N];
bool Cmp(int x,int y){
    return x%2>y%2;
}

int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=m;i++) cin>>a[i];
    if(m==1){
        if(a[1]==1) cout<<1<<endl<<1<<endl<<1<<endl;
        else cout<<a[1]<<endl<<2<<endl<<1<<' '<<a[1]-1<<endl;
        return 0;
    }
    sort(a+1,a+m+1,Cmp);
    swap(a[2],a[m]);
    if(a[3]%2==1){
        cout<<"Impossible"<<endl;
        return 0;
    }
    for(int i=1;i<=m;i++) cout<<a[i]<<' ';
    cout<<endl;
    a[1]++;a[m]--;
    if(!a[m]) m--;
    cout<<m<<endl;
    for(int i=1;i<=m;i++) cout<<a[i]<<' ';
    cout<<endl;
    return 0;
}