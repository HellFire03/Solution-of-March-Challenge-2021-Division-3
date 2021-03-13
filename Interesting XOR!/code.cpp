#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int test;
    cin>>test;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while(test--){
        unsigned long int C,A,B,multiply,base,ans=0;
        cin>>C;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        base = pow(2,(int)(log2(C)+1));
        A = (base-2)/2;
        B = C^A;
        multiply = A*B;
        if(multiply>ans)
            ans = multiply;
        cout<<ans<<"\n";
    }
    return 0;
}
