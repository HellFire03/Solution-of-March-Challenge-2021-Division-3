#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
	int n,h,x,flag=0;
	cin>>n>>h>>x;
	int want = abs(h-x);
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	int t[n];
	for(int i=0;i<n;i++){
	    cin>> t[i];
	    if(want==t[i]){
	        cout<<"YES";
	        flag++;
	        break;
     	}
	}
	if(flag==0)cout<<"NO";
	return 0;
}
