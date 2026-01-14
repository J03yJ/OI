#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
const int N=(1<<20)+9;

int a[N],n;

signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);

	cin>>n;
	for(int i=0;i<(1<<n);i++) cin>>a[i];

	for(int sta=0;sta<(1<<n);sta++){
		for(int i=0;i<n;i++){
			for(int j=i+1;j<n;j++){
				int tta=sta^(1<<i)^(1<<j);
				if(a[sta]+a[tta]<a[sta&tta]+a[sta|tta]){
					cout<<sta<<' '<<tta<<endl;
					return 0;
				}
			}
		}
	}

	cout<<-1<<endl;

	return 0;
}