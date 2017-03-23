#include <iostream>
#include <string>

using namespace std;

int checked[10] = {0,0,0,0,0,0,0,0,0,0};

void reset(void){
	for(int i=0;i<11;i++){
		checked[i] = 0;
	}
}

bool all_different(int num){
	for(int i=0;i<5;i++){
		if(checked[num%10]==1){
			return false;
		}
		else{
			checked[num%10] = 1;
			num = num/10;
		}
	}
	return true;
}

string get_string(int num){
	string temp = "00000";
	for(int i=4;i>=0;i--){
		temp[i] = (char)((int)('0') + num%10);
		num = num/10;
	}
	return temp;
}

int main(){
	int N;
	bool found;
	cin >> N;
	while(N){
		found = false;
		//Min num = 01234, max num = 98765
		for(int i=1234;i<=98765;i++){
			if(all_different(i)){
				if(i*N < 98765 && all_different(i*N)){
					cout << get_string(i*N) << " / " << get_string(i) << " = " << N << endl;
					found = true;
				}
				reset();
			}
			else{
				reset();
			}
		}
		if(!found){
			cout << "There are no solutions for " << N << "." << endl;
		}
		cin >> N;
		if(N){
			cout << endl;
		}
	}
}
