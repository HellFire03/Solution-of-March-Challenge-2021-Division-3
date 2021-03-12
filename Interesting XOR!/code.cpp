#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
	int test;
	cin>>test;
	while(test--){
	    unsigned long long int c,d=0,r,result,ans=0;
	    cin>>c;
        r = pow(2,(int)(log2(c)+1));
        for(int i=1;i<r-1;i++){
            for(int j=i+1;j<r;j++){
                if((i^j)==c){
                    result = i*j;
                    result = max(result,result);
                }
            }
        }
        cout<<result<<"\n";
	}
	return 0;
}
