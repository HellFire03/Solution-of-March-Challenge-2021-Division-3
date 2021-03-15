#include <cstdio>
#include <iostream>
#include <algorithm>
typedef long long ll;
const int Maxn=1000000;
int n;
ll a[Maxn+5];
std::pair<ll,int> f_max[20][Maxn+5];
ll f_or[20][Maxn+5],f_and[20][Maxn+5];
int log_2[Maxn+5];
void init(){
	log_2[0]=-1;
	for(int i=1;i<=n;i++){
		log_2[i]=log_2[i>>1]+1;
	}
	for(int i=1;i<=n;i++){
		f_max[0][i]=std::make_pair(a[i],i);
		f_or[0][i]=f_and[0][i]=a[i];
	}
	for(int i=1;(1<<i)<=n;i++){
		for(int j=1;j+(1<<i)-1<=n;j++){
			f_max[i][j]=std::max(f_max[i-1][j],f_max[i-1][j+(1<<(i-1))]);
			f_or[i][j]=f_or[i-1][j]|f_or[i-1][j+(1<<(i-1))];
			f_and[i][j]=f_and[i-1][j]&f_and[i-1][j+(1<<(i-1))];
		}
	}
}
std::pair<ll,int> query_max(int l,int r){
	int k=log_2[r-l+1];
	return std::max(f_max[k][l],f_max[k][r-(1<<k)+1]);
}
ll query_or(int l,int r){
	int k=log_2[r-l+1];
	return f_or[k][l]|f_or[k][r-(1<<k)+1];
}
ll query_and(int l,int r){
	int k=log_2[r-l+1];
	return f_and[k][l]&f_and[k][r-(1<<k)+1];
}
ll ans;
void solve(int l,int r){
	if(l>r){
		return;
	}
	if(l==r&&a[l]==0){
		ans++;
		return;
	}
	int pos=query_max(l,r).second;
	if(pos-l+1<r-pos+1){
		for(int i=pos;i>=l;i--){
			if((query_or(i,r)^query_and(i,r))<a[pos]){
				continue;
			}
			int left=pos,right=r;
			while(left<right){
				int mid=(left+right)>>1;
				if((query_or(i,mid)^query_and(i,mid))>=a[pos]){
					right=mid;
				}
				else{
					left=mid+1;
				}
			}
			ans+=r-left+1;
		}
	}
	else{
		for(int i=pos;i<=r;i++){
			if((query_or(l,i)^query_and(l,i))<a[pos]){
				continue;
			}
			int left=l,right=pos;
			while(left<right){
				int mid=(left+right+1)>>1;
				if((query_or(mid,i)^query_and(mid,i))>=a[pos]){
					left=mid;
				}
				else{
					right=mid-1;
				}
			}
			ans+=left-l+1;
		}
	}
	solve(l,pos-1);
	solve(pos+1,r);
}
void work(){
	ans=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	init();
	solve(1,n);
	printf("%lld\n",ans);
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		work();
	}
	return 0;
}
