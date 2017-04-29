#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <sstream>

using namespace std;

int main(){
    //freopen("output.txt","w",stdout);
	int N,temp;
	cin >> N;
    vector<int> correct_ordering(N+1);
    for(int i=1; i<=N; i++){
        cin >> temp;
        correct_ordering[i] = temp;
    }
    vector<int> response(N+1);
    while(cin >> temp){
        //cin >> input;
        response[temp] = 1;
        for(int i=2;i<=N;i++){
            cin >> temp;
            response[temp] = i;
        }
        vector<int> lis(N+1,1);
        int best_response = 1;
        for(int i=2; i<=N; i++){
            for(int j=1;j<i;j++){
                if(correct_ordering[response[j]] < correct_ordering[response[i]]){
                    if(lis[i]<1+lis[j]){
                        lis[i] = 1 + lis[j];
                        if(best_response < lis[i]){
                            best_response = lis[i];
                        }
                    }
                }
            }
        }
        cout << best_response << endl;
    }

	return 0;
}
