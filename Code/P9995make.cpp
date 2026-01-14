#include<bits/stdc++.h>

using namespace std;

int main(){
    ofstream fin("P9995make.in");
    ofstream fout("P9995make.out");

    int n=1000,m=1000;
    fin<<n<<' '<<m<<endl;
    vector<int> a(n+1);
    mt19937 myrand(4649);
    for(int i=1;i<=n;i++){
        a[i]=myrand()%n+1;
        fin<<a[i]<<' ';
    }
    fin<<endl;

    int lst=0;
    while(m--){
        int l=myrand()%n+1,r=myrand()%n+1,x=myrand()%n+1;
        fin<<(l^lst)<<' '<<(r^lst)<<' '<<(x^lst)<<endl;
        if(l<=r) sort(a.begin()+l,a.begin()+r+1);
        else sort(a.begin()+r,a.begin()+l+1,greater<int>());
        vector<int> vis(n+1,1);
        int cnt=0;
        for(int i=1;i<=x;i++) cnt+=vis[a[i]],vis[a[i]]=0;
        for(int i=1;i<=n;i++) fout<<a[i]<<' ';fout<<endl;
        fout<<cnt<<endl;
        lst=cnt;
    }

    return 0;
}