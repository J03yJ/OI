#include<bits/stdc++.h>

using namespace std;

int main(){
    int T;
    cin>>T;
    while(T--){
        int n,k;
        cin>>n>>k;
        vector<int> a(n),b(n);
        for(int &x:a) cin>>x;
        for(int &x:b) cin>>x;

        if(k>1){
            vector<int> cnta(n+1,0),cntb(n+1,0),lst(n+1,-n);
            for(int x:a) cnta[x]++;
            for(int x:b) cntb[x]++;

            int err=1,err_=0;
            for(int i=0;i<n;i++){
                if(lst[b[i]]+k>=i) err=0;
                lst[b[i]]=i;
            }
            for(int i=1;i<=n;i++) if(cntb[i]&&!cnta[i]) err=1;
            for(int i=0;i<n;i++) if(a[i]!=b[i]) err_=1;

            if(err&&err_) cout<<"No"<<endl;
            else cout<<"Yes"<<endl;
        }else{
            vector<int> ua,ub;
            for(int x:a) if(!ua.size()||x!=ua.back()) ua.push_back(x);
            for(int x:b) if(!ub.size()||x!=ub.back()) ub.push_back(x);
            int i=0,j=0;
            for(;i<ua.size()&&j<ub.size();i++) if(ua[i]==ub[j]) j++;
            if(j<ub.size()) cout<<"No"<<endl;
            else cout<<"Yes"<<endl;
        }
    }

    return 0;
}