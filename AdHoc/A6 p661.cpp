#include <iostream>

using namespace std;

bool switched[20];
int ampere[20];

int main(){
	int n,m,c,sequence=0;
	
	cin >> n >> m >> c;
	while(n){
		sequence++;
		for(int i=0;i<n;i++){
			cin >> ampere[i];
			switched[i] = false;
		}
		int maximum_ampere=0, total_ampere=0, temp_switch;
		for(int i=0;i<m;i++){
			cin >> temp_switch;
			temp_switch--;
			if(switched[temp_switch]){
				total_ampere-=ampere[temp_switch];
				switched[temp_switch] = false;
			}
			else{
				total_ampere+=ampere[temp_switch];
				switched[temp_switch] = true;
				maximum_ampere = max(maximum_ampere,total_ampere);
			}
		}
		if(maximum_ampere > c){
			cout << "Sequence " << sequence << endl;
			cout << "Fuse was blown." << endl;
		}
		else{
			cout << "Sequence " << sequence << endl;
			cout << "Fuse was not blown." << endl;
			cout << "Maximal power consumption was " << maximum_ampere << " amperes."<< endl;
		}
		cout << endl;
		
		
		cin >> n >> m >> c;
	}
	
	
	return 0;
}