#include<bits/stdc++.h>

using namespace std;

const int N=1e6+9;

int sa[N<<1],rk[N<<1],lsa[N],lrk[N],cnt[N],n;
char s[N];

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #define endl '\n'

    while(cin>>s[++n]);
    n--;

    for(int i=1;i<=n;i++) cnt[s[i]]++;
    for(int i=1;i<128;i++) cnt[i]+=cnt[i-1];
    for(int i=n;i>=1;i--) sa[cnt[s[i]]--]=i;
    for(int i=0;i<128;i++) cnt[i]=0;
    
    int tot=0;
    for(int i=1;i<=n;i++) lrk[i]=s[i];
    for(int i=1;i<=n;i++){
        if(lrk[sa[i]]!=lrk[sa[i-1]]) tot++;
        rk[sa[i]]=tot;
    }

    for(int k=1;k<=n&&tot<n;k<<=1){
        for(int i=1;i<=n;i++) cnt[rk[sa[i]+k]]++;
        for(int i=1;i<=tot;i++) cnt[i]+=cnt[i-1];
        for(int i=n;i>=1;i--) lsa[cnt[rk[sa[i]+k]]--]=sa[i];
        for(int i=0;i<=tot;i++) cnt[i]=0;

        for(int i=1;i<=n;i++) cnt[rk[lsa[i]]]++;
        for(int i=1;i<=tot;i++) cnt[i]+=cnt[i-1];
        for(int i=n;i>=1;i--) sa[cnt[rk[lsa[i]]]--]=lsa[i];
        for(int i=0;i<=tot;i++) cnt[i]=0;
        
        tot=0;
        for(int i=1;i<=n;i++) lrk[i]=rk[i];
        for(int i=1;i<=n;i++){
            if(lrk[sa[i]]!=lrk[sa[i-1]]||lrk[sa[i]+k]!=lrk[sa[i-1]+k]) tot++;
            rk[sa[i]]=tot;
        }
    }

    for(int i=1;i<=n;i++) cout<<sa[i]<<' ';cout<<endl;

    return 0;
}