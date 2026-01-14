#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

tree<pair<int,int>,null_type,less<pair<int,int>>,rb_tree_tag,tree_order_statistics_node_update> tr;
gp_hash_table<int,int> mp;

int main(){
    int m,q;
    cin>>m>>q;
    for(int i=1;i<=m;i++){
        long long x;
        cin>>x;
        tr.insert({-x,++mp[x]});
    }
    while(q--){
        long long op,k;
        cin>>op>>k;
        if(op==1) cout<<-tr.find_by_order(k-1)->first<<endl;
        else tr.insert({-k,++mp[k]});
    }
}