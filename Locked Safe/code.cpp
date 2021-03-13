#include <bits/stdc++.h>
#define ll long long int
#define ul long long unsigned int
using namespace std;

int main() {
    ll t;
    cin>>t;
    while(t--){
        ll n,i,j;
        cin>>n;
        ul arr[n];
        for(ll i=0;i<n;i++)
            cin>>arr[i];
        vector<ul>v,v2,maxx;
        ul nd = arr[0];
        ul aor = arr[0];
        v.push_back(nd);
        v2.push_back(aor);
        maxx.push_back(arr[0]);
        ul maxx2=arr[0];
        for(i=1;i<n;i++){
            v.push_back(arr[i]);
            v2.push_back(arr[i]);
            maxx.push_back(arr[i]);
            maxx2 = max(maxx2,arr[i]);
            nd&=arr[i];
            aor|=arr[i];
            v.push_back(nd);
            v2.push_back(aor);
            maxx.push_back(maxx2);
        }
        for(i=n-1;i>0;i--){
            nd&=arr[i];
            aor|=arr[i];
            maxx2=arr[i];
            for(j=i-1;j>0;j--){
                nd&=arr[j];
                aor|=arr[j];
                maxx2=max(arr[j],maxx2);
                maxx.push_back(maxx2);
                v.push_back(nd);
                v2.push_back(aor);
            }
            
        }
        int count =0;
        for(i=0;i<v.size();i++){
            if((v[i]^v2[i])>=maxx[i])
                count++;
        }
        cout<<count<<"\n";
    }
	return 0;
}
