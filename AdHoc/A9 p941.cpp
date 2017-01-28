#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

long long int factorial[21];
vector<char> vec;


bool sort_func(char a, char b){
	return ((int)a < (int)b);
}

void resuffle_vector(long long int N){
	//cout << N << endl;
	if(N==1 || N==0){
		return;
	}
	else{
		//Determine what is the highest factorial casues this number
		int i,j,facto_index;
		char temp;
		for(i = 1;i<=vec.size();i++){
			if(N>factorial[i-1] && N<=factorial[i]){
				break;
			}
			continue;
		}
		facto_index = vec.size()-i;
		//Finding highest index multiple
		for(j=1;j<i;j++){
			if(N>factorial[i-1]*j && N<=factorial[i-1]*(j+1)){
				break;
			}
			continue;
		}
		//swpa facto_index and facto_index+j, then sort facto_index+1,end
		temp = vec[facto_index];
		vec[facto_index] = vec[facto_index+j];
		vec[facto_index+j] = temp;
		sort(vec.begin()+facto_index+1,vec.end(),sort_func);
		resuffle_vector(N-j*factorial[i-1]);
		return;
	}
}

int main(){
	//Factorial generation
	factorial[0] = 1;
	for(long long int i=1;i<=20;i++){
		factorial[i] = factorial[i-1]*i;
		//cout << factorial[i] << endl;
	}
	int T;
	long long int N;
	string in;
	cin >> T;
	while(T--){
		cin >> in;
		cin >> N;
		vec.clear();
		for(int i=0;i<in.length();i++){
			vec.push_back(in[i]);
		}
		sort(vec.begin(),vec.end(),sort_func);
		resuffle_vector(N+1);
		for(vector<char>::iterator it=vec.begin();it!=vec.end();++it){
			cout << (*it);
		}
		cout << endl;
	}
	return 0;
}
