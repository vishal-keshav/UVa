#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <sstream>

using namespace std;

int main(){
    //freopen("output.txt","w",stdout);
    string input;
	int N,temp;
	cin >> N;
	while(1){
		vector<int> correct_ordering(N+1);
		for(int i=1; i<=N; i++){
			cin >> temp;
			correct_ordering[i] = temp;
		}
		cin.ignore();
		while(1){
            //cin >> input;
            getline(cin,input);
            vector<int> response_temp(1);
            vector<int> response(N+1);
            istringstream ss(input);
            while (ss >> temp){
                response_temp.push_back(temp);
            }
            if(response_temp.size()==2){
                N = response_temp[1];
                break;
            }
            else{
                for(int i=1;i<=N;i++){
                    response[response_temp[i]] = i;
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
		}
	}

	return 0;
}
