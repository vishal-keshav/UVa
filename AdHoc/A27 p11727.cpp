#include <iostream>

using namespace std;
void swap(int *a, int *b){
	int temp = (*a);
	(*a) = (*b);
	(*b) = temp;
}
int main(){
	int T,test_case=1,S1,S2,S3;
	cin >> T;
	while(T--){
		cin >> S1 >> S2 >> S3;
		if(S1>S2){
			swap(&S1,&S2);
		}
		if(S2>S3){
			swap(&S2,&S3);
		}
		if(S1>S2){
			swap(&S1,&S2);
		}
		cout << "Case " << test_case <<": " << S2 << endl;
		test_case++;
	}
	return 0;
}
