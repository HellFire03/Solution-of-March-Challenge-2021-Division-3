#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int test;
    cin>>test;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while(test--){
        int n;
        cin>>n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        int arr[n];
        for(int i=0;i<n;i++){
            cin>>arr[i];
        }
        
        sort(arr,arr+n);
        
        int value=0;
        int flag=0;
        
        for(int i=0;i<n;i++){
            if(i+1<arr[i]){
                flag=1;
                break;
            }
            value += (i+1-arr[i]);
        }
        if(flag==1) 
            cout<<"Second\n";
        else if(value%2==1)   
            cout<<"First\n";
        else    
            cout<<"Second\n";
    }
    return 0;
}
