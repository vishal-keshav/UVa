#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

bool is_subsequence(string s1, string s2){
	int nr_s1 = s1.size();
	int nr_s2 = s2.size();
	//cout << nr_s1 << " " << nr_s2 << endl;
	bool ret = false;
	//Initial checks
	if(nr_s1>nr_s2){
		return ret;
	}
	int index_s1 = 0, index_s2;
	for(index_s2=0;index_s2<nr_s2;index_s2++){
		if(s1[index_s1] == s2[index_s2]){
            //cout << "Equal " << s1[index_s1] << " " << s2[index_s2]<< endl;
			index_s1++;
		}
        if(index_s1>=nr_s1){
			ret = true;
			break;
		}
	}
	return ret;
}

int main(){
	string sub,seq;
	while(cin >> sub >> seq){
		if(is_subsequence(sub,seq)){
			cout << "Yes" << endl;
		}
		else{
			cout << "No" << endl;
		}
	}
	return 0;
}
