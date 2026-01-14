#include<bits/stdc++.h>

using namespace std;

#define ssiz(x) (signed)x.size()

int main(){
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        vector<int> a,b;
        while(n--){
            int x;
            cin>>x;
            if(x&1) a.push_back(x);
            else b.push_back(x);
        }
        sort(a.begin(),a.end());
        sort(b.begin(),b.end());

        if(ssiz(b)&&b.back()>ssiz(a)){
            cout<<"Yes"<<endl;
            continue ;
        }
        int flag=0;
        for(int i=0;i<ssiz(a);i++){
            int tot=ssiz(a)-i;
            if(tot&1){
                if(a[i]>i){
                    cout<<"Yes"<<endl;
                    flag=1;
                    break ;
                }
            }
        }
        if(!flag) cout<<"No"<<endl;
    }

    return 0;
}