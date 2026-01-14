#include<bits/stdc++.h>

using namespace std;

const int N=2e5+9;
const int V=1e9;

int main(){
    int n,ans=0;
    cin>>n;
    set<pair<int,int>> s;
    while(n--){
        int l,r;
        cin>>l>>r;
        int lft=r-l+1;
        set<pair<int,int>>::iterator it;
        while(lft&&(it=s.lower_bound({l,0}))!=s.end()){
            int x=it->second,y=it->first,z=y-x+1;
            if(x<l){
                s.erase(it);
                s.insert({l-1,x});
                s.insert({y,l});
                continue ;
            }else if(z<=lft){
                lft-=z;
                s.erase(it);
                ans-=z;
            }else{
                z-=lft;
                s.erase(it);
                s.insert({y,y-z+1});
                ans-=lft;
                lft=0;
            }
        }
        s.insert({r,l});
        ans+=r-l+1;
    }
    cout<<ans<<endl;

    return 0;
}