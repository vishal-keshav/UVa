#include <iostream>

using namespace std;

int main(){
	int N,s,d;
	cin >> N;
	for(int i=0;i<N;i++){
		cin >> s >> d;
		if(s<d){
			cout << "impossible" << endl;
		}
		else{
			if((s+d)%2!=0){
				cout << "impossible" << endl;
			}
			else{
				cout << (s+d)/2 << " " << (s-d)/2 << endl;
			}
		}
	}
	return 0;
}
