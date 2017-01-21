#include<iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

//#define DEBUG 1

int main(){
	map<string, vector<int> > ref_map;
	int N,M;
	int B,C_D,D,L,U;
	string variable;
	cin >> N >> M;
	for(int i=0;i<N;i++){
		cin >> variable;
		vector<int> value;
		cin >> B >> C_D >> D;
		value.push_back(B);
		value.push_back(C_D);
		value.push_back(D);
		for(int i=0;i<D;i++){
			cin >> L >> U;
			value.push_back(L);
			value.push_back(U);
		}
		ref_map[variable] = value;
	}
#ifdef DEBUG
	map<string,vector<int> >::iterator iter_map;
	vector<int>::iterator iter_vec;
	for(iter_map = ref_map.begin();iter_map!=ref_map.end(); iter_map++){
		cout << iter_map->first << " : ";
		for(iter_vec = (iter_map->second).begin(); iter_vec!=(iter_map->second).end();iter_vec++){
			cout << *iter_vec << " ";
		}
		cout << endl;
	}
#endif


	for(int i=0;i<M;i++){
		cin >> variable;
		cout << variable << "[";
		vector<int> input;
		vector<int> process = ref_map[variable];
		D = process[2];
		for(int i=0;i<D;i++){
			cin >> B;
			input.push_back(B);
			cout << B;
			if(i!=D-1){
				cout << ", ";
			}
		}
		cout << "] = ";
		//Processing
		C_D = process[1];
		int ans = C_D*input[D-1];
		int C_0 = 0;
		
		//cout << D << " " << C_D << " " << ans << endl;
		for(int i=D-2,j=2*D + 2;i>=0;i--,j-=2){
			//cout << process[j] << " " << process[j-1] << endl;
			C_0+= process[j-1]*C_D;
			C_D = C_D*(process[j] - process[j-1] + 1);
			
			ans+=C_D*input[i];
		}
		C_0+=process[3]*C_D;
		ans+= (process[0] - C_0);
		//printing
		cout << ans << endl;
	}

	return 0;
}
