#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdio.h>

using namespace std;

int main(){
    //freopen("output.txt","w",stdout);
	int T,N,iter=0;
	string input,word;
	cin >> T;

	cin.ignore();
	while(T--){
        getline(cin,input);
		iter = 0;
		vector<int> permutation;
		vector<string> output;

		getline(cin,input);
		stringstream ss(input);
		while(ss >> word){
			permutation.push_back(word[0] - '0');
			iter++;
		}
		/*Converting permutaion in linear format*/
		vector<int> new_permu(iter);
		for(int i=0;i<iter;i++){
            new_permu[permutation[i]-1] = i;
		}

		getline(cin,input);
		stringstream sss(input);
		while(sss >> word){
			output.push_back(word);
		}

		for(vector<int>::iterator iter = new_permu.begin(); iter!=new_permu.end();iter++){
			cout << output[(*iter)] << endl;
		}
		if(T!=0){
            cout << endl;
		}
		/*else{
            cout << endl;
		}*/
	}
	return 0;
}
