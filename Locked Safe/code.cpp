#include <bits/stdc++.h>
#define ll long long unsigned int
using namespace std;

int main() {
    ll t,n,ans;
    cin>>t;
    while(t--){
        cin>>n;
        ll number,counter=0;
        vector<ll>vis;
        for(ll i=0;i<n;i++){
            cin>>number;
            vis.push_back(number);
        }
        ans=(n*(n-1))>>1;
        for(ll i=1;i<n;i++){
            if(vis[i]==vis[i-1]){
                counter++;
            }
            else{
                if(counter !=1){
                    ans -= (counter*(counter-1))>>1;
                }
                counter = 1;
            }
        }
        if(counter != 1){
            ans-= (counter*(counter-1))>>1;
        }
        cout<<ans<<endl;
    }
	return 0;
}
