#include <iostream>
#include <stack>
#include <stdio.h>

using namespace std;

int main(){
    //freopen("output.txt","w",stdout);
	int N,e,index;
	cin >> N;
	while(N){
		cin >> e;
		while(e){
			stack<int> B_reverse,B,A;
			B_reverse.push(e);
			for(int i=0;i<N-1;i++){
				cin >> e;
				B_reverse.push(e);
			}
			while(!B_reverse.empty()){
                B.push(B_reverse.top());
                B_reverse.pop();
			}
			for(int i=1;i<=N;i++){
				A.push(i);
				while(!A.empty() && A.top()==B.top()){
					A.pop();
					B.pop();
					//cout << "popped" << endl;
				}
			}
			if(B.empty()){
				cout << "Yes" << endl;
			}
			else{
				cout << "No" << endl;
			}
			cin >> e;
		}
		cout << endl;
		cin >> N;
	}
	return 0;
}
