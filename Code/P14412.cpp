#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=3e3+9;

int a[N],cnt[N],o[N],n,v;
vector<array<int,2>> q[N];
inline void Work(int &ans){
	for(int i=1;i<=n;i++){
		int p=0;
		while(i+p<=n&&i-p>=1&&a[i+p]==a[i-p]) p++;
		ans=max(ans,p-1<<1|1);
		if(i+p>n||i-p<1) continue ;
		bool err=0;
		int j=i-p,k=i+p,lst=0;
		while(j>=1){
			cnt[a[j]]--;
			for(int t=lst;t<a[j];t++) err|=cnt[t];
			if(err) break ;
			if(a[j]<lst){
				if(i-j+1!=k-i+1) break ;
				while(j>=1&&k<=n&&a[j]==a[k]) j--,k++;
				ans=max(ans,k-j-1);
				break ;
			}
			lst=a[j];
			while(k<=n&&cnt[a[j]]<0){
				cnt[a[k]]++;
				err|=(a[k]<a[j]);
				k++;
			}
			err|=(cnt[a[j]]<0);
			if(err) break ;
			ans=max(ans,i-j<<1|1);
			j--;
		}
		for(int t=0;t<=v;t++) cnt[t]=0;
	}
	for(int i=1;i<=n;i++){
		int p=0;
		while(i+1+p<=n&&i-p>=1&&a[i+1+p]==a[i-p]) p++;
		ans=max(ans,p<<1);
		if(i+1+p>n||i-p<1) continue ;
		bool err=0;
		int j=i-p,k=i+p+1,lst=0;
		while(j>=1){
			cnt[a[j]]--;
			for(int t=lst;t<a[j];t++) err|=cnt[t];
			if(err) break ;
			if(a[j]<lst){
				if(i-j+1!=k-i) break ;
				while(j>=1&&k<=n&&a[j]==a[k]) j--,k++;
				ans=max(ans,k-j-1);
				break ;
			}
			lst=a[j];
			while(k<=n&&cnt[a[j]]<0){
				cnt[a[k]]++;
				err|=(a[k]<a[j]);
				k++;
			}
			err|=(cnt[a[j]]<0);
			if(err) break ;
			ans=max(ans,i-j+1<<1);
			j--;
		}
		for(int t=0;t<=v;t++) cnt[t]=0;
	}
	for(int i=1;i<=n;i++){
		int j=i-1,k=i;
		if(j<1) continue ;
		while(k<=n&&a[k]>=a[j]) cnt[a[k++]]++;
		if(k<=n){
			bool err=0;
			int mn=a[k],lst=mn+1;
			cnt[a[k++]]++;
			while(j>=1){
				cnt[a[j]]--;
				for(int t=lst;t<a[j];t++) err|=cnt[t];
				if(err) break ;
				if(a[j]<lst){
					if(k-j+1!=(i-j)*2+cnt[mn]) break ;
					while(k<=n&&a[k]==mn) k++;
					while(j>=1&&k<=n){
						if(a[j]==a[k]) j--,k++;
						else break ;
					}
					ans=max(ans,k-j-1);
					break ;
				}
				lst=a[j];
				while(k<=n&&cnt[a[j]]<0){
					cnt[a[k]]++;
					err|=(a[k]<a[j]&&a[k]!=mn);
					k++;
				}
				err|=(cnt[a[j]]<0);
				if(err) break ;
				// int cc=0;
				// for(int t=k;t<=n;t++){
				// 	if(a[t]<a[j]&&a[t]!=mn) break ;
				// 	cc+=(a[t]==mn);
				// }
				// ans=max(ans,(i-j<<1)+cnt[mn]+cc);
				q[k].push_back({(i-j<<1)+cnt[mn],a[j]});
				j--;
			}
			for(int t=i;t<=n;t++) o[t]=o[t-1]+(a[t]==mn);
			vector<int> stk,w;
			for(int t=n;t>=i;t--){
				if(a[t]!=mn){
					while(stk.size()&&w.back()>=a[t]) stk.pop_back(),w.pop_back();
					stk.push_back(t),w.push_back(a[t]);
				}
				for(auto d:q[t]){
					int p=lower_bound(w.begin(),w.end(),d[1])-w.begin()-1;
					ans=max(ans,d[0]+o[p<0?n:stk[p]-1]-o[t-1]);
				}
				q[t].clear();
			}
		}
		for(int t=0;t<=v;t++) cnt[t]=o[t]=0;
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

	cin>>n>>v;
	for(int i=1;i<=n;i++) cin>>a[i];

	int ans=0;
	Work(ans);
	reverse(a+1,a+n+1);
	for(int i=1;i<=n;i++) a[i]=v-a[i]+1;
	Work(ans);
	for(int i=1;i<=v;i++) ans=max(ans,(int)count(a+1,a+n+1,i));

	cout<<ans<<endl;

	return 0;
}