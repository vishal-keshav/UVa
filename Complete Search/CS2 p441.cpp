#include <iostream>
#include <vector>

using namespace std;

int main(){
	int S;
	cin >> S;
	while(S){
		vector<int> vec(S);
		for(int i=0;i<S;i++){
			cin >> vec[i];
		}
		for(int i=0;i<S;i++){
			for(int j=i+1;j<S;j++){
				for(int k=j+1;k<S;k++){
					for(int l=k+1;l<S;l++){
						for(int m=l+1;m<S;m++){
							for(int n=m+1;n<S;n++){
								cout << vec[i] << " " << vec[j] << " " << vec[k] << " " << vec[l] << " " << vec[m] << " " << vec[n] << endl;
							}
						}
					}
				}
			}
		}

		cin >> S;
		if(S){
			cout << endl;
		}
	}
	return 0;
}
