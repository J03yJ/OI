#include<bits/stdc++.h>

using namespace std;

const int N=1e5+9;
const int sN=4e2+9;

int a[N];
vector<int> q[N];

set<int> val;
map<int,int> mp,rmp;

int blk[N],vlk[N<<1];
int bpre[sN][sN<<1],vpre[sN][N<<1];
int buc[sN<<1],vuc[N<<1];

int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i],val.insert(a[i]);
    for(int i=1;i<=m;i++){
        char op;
        cin>>op;
        if(op=='Q'){
            int l,r,k;
            cin>>l>>r>>k;
            q[i].push_back(0);
            q[i].push_back(l);
            q[i].push_back(r);
            q[i].push_back(k);
            val.insert(k);
        }else{
            int pos,k;
            cin>>pos>>k;
            q[i].push_back(1);
            q[i].push_back(pos);
            q[i].push_back(k);
            val.insert(k);
        }
    }

    int cnt=0;
    for(int x:val) mp[x]=++cnt,rmp[cnt]=x;

    const int B=sqrt(n);
    for(int i=1;i<=n;i++) blk[i]=min((i-1)/B+1,B);
    const int vB=sqrt(cnt);
    for(int i=1;i<=cnt;i++) vlk[i]=min((i-1)/vB+1,vB);
    for(int i=1;i<=n;i++) a[i]=mp[a[i]];
    for(int i=1;i<=m;i++) if(q[i].front()) q[i].back()=mp[q[i].back()];

    for(int i=1;i<=n;i++) bpre[blk[i]][vlk[a[i]]]++,vpre[blk[i]][a[i]]++;
    for(int i=1;i<=B;i++){
        for(int j=1;j<=vB;j++) bpre[i][j]+=bpre[i-1][j];
        for(int j=1;j<=cnt;j++) vpre[i][j]+=vpre[i-1][j];
    }

    // for(int i=1;i<=n;i++) cout<<a[i]<<'/'<<vlk[a[i]]<<' ';cout<<endl;
    // for(int i=1;i<=B;i++){
    //     for(int j=1;j<=cnt;j++) cout<<vpre[i][j]<<' ';cout<<endl;
    // }
    // cout<<endl;
    // for(int i=1;i<=B;i++){
    //     for(int j=1;j<=vB;j++) cout<<bpre[i][j]<<' ';cout<<endl;
    // }
    // cout<<endl;

    for(int o=1;o<=m;o++){
        if(q[o][0]){
            int pos=q[o][1],k=q[o][2];
            for(int i=blk[pos];i<=B;i++){
                vpre[i][k]++;vpre[i][a[pos]]--;
                bpre[i][vlk[k]]++;bpre[i][vlk[a[pos]]]--;
            }
            a[pos]=k;

            // for(int i=1;i<=n;i++) cout<<a[i]<<'/'<<vlk[a[i]]<<' ';cout<<endl;
            // for(int i=1;i<=B;i++){
            //     for(int j=1;j<=cnt;j++) cout<<vpre[i][j]<<' ';cout<<endl;
            // }
            // cout<<endl;
            // for(int i=1;i<=B;i++){
            //     for(int j=1;j<=vB;j++) cout<<bpre[i][j]<<' ';cout<<endl;
            // }
            // cout<<endl;
        }else{
            int l=q[o][1],r=q[o][2],k=q[o][3];
            // cout<<blk[l]<<' '<<blk[r]<<endl;
            if(blk[l]!=blk[r]){
                for(int i=l;i<=min(blk[l]*B,n);i++) vuc[a[i]]++,buc[vlk[a[i]]]++;
                for(int i=(blk[r]-1)*B+1;i<=r;i++) vuc[a[i]]++,buc[vlk[a[i]]]++;
            }else for(int i=l;i<=r;i++) vuc[a[i]]++,buc[vlk[a[i]]]++;

            for(int i=1,cur=0;i<=vB;i++){
                int itmp=buc[i];
                if(blk[l]!=blk[r]) itmp+=bpre[blk[r]-1][i]-bpre[blk[l]][i];
                // int cnt=0;
                // cout<<i<<" : "<<endl;
                // for(int j=l;j<=r;j++) if(vlk[a[j]]==i) cnt++,cout<<blk[j]<<' ';
                // cout<<cnt<<endl;
                // cout<<cur<<' '<<l<<' '<<r<<' '<<bpre[blk[r]-1][i]<<' '<<bpre[blk[l]][i]<<' '<<buc[i]<<endl;
                if(cur+itmp>=k){
                    for(int j=(i-1)*vB+1;vlk[j]==i;j++){
                        int jtmp=vuc[j];
                        if(blk[l]!=blk[r]) jtmp+=vpre[blk[r]-1][j]-vpre[blk[l]][j];
                        // cout<<cur<<' '<<l<<' '<<r<<' '<<vpre[blk[r]-1][j]<<' '<<vpre[blk[l]][j]<<' '<<vuc[j]<<' '<<jtmp<<' '<<k<<' '<<rmp[j]<<endl;
                        if(cur+jtmp>=k){
                            cout<<rmp[j]<<endl;
                            break ;
                        }
                        cur+=jtmp;
                    }
                    break ;
                }
                cur+=itmp;
            }
            // cout<<endl;

            if(blk[l]!=blk[r]){
                for(int i=l;i<=min(blk[l]*B,n);i++) vuc[a[i]]--,buc[vlk[a[i]]]--;
                for(int i=(blk[r]-1)*B+1;i<=r;i++) vuc[a[i]]--,buc[vlk[a[i]]]--;
            }else for(int i=l;i<=r;i++) vuc[a[i]]--,buc[vlk[a[i]]]--;
        }
    }

    return 0;
}