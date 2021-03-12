#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
	int test;
	cin>>test;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	while(test>0){
	    string str;
	    cin>>str;
	    cin.ignore(numeric_limits<streamsize>::max(), '\n');
	    int count=0,result=0,flag=0;
	    for(int i=0;i<str.length();i++){
	        if(str[i]=='0'){
	            flag=0;
	        }
	        else{
	            flag++;
	            if(flag==1){
	                count++;
	            }
	        }
	    }
	    cout<<count<<"\n";
	    test--;
	};
	return 0;
}
