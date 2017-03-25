#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

int prime[40];
void init_prime_finder(void){
	for(int i=0;i<40;i++){
		prime[i] = 1;
	}
	for(int i=2;i<40;i++){
		int j=2;
		while(j*i<40){
			prime[i*j] = 0;
			j++;
		}
	}
}

bool is_prime(int num){
	return (prime[num]==1);
}

vector<int> done;
vector<int> ring;
int N;

void create_ring(int total){
	if(total>=N){
		if(is_prime(ring[N-1]+1)){
			for(int i=0;i<N-1;i++){
				cout << ring[i] << " ";
			}
			cout << ring[N-1] << endl;
		}
	}
	else{
		for(int i=1;i<=N;i++){
			if(done[i]==0 && is_prime(i+ring[ring.size()-1])){
				done[i] = 1;
				ring.push_back(i);
				create_ring(total+1);
				ring.pop_back();
				done[i] = 0;
			}
		}
	}
}

int main(){
	init_prime_finder();
	int nr_case=1;
	bool new_line=false;
	while(cin>>N){
        if(!new_line){
            new_line = true;
        }
        else{
            cout << endl;
        }
		ring.clear();
		done.clear();
		done.resize(N+1,0);
		done[1] = 1;
		ring.push_back(1);
		cout << "Case " << nr_case << ":" << endl;
		create_ring(1);
		nr_case++;
	}
	return 0;
}
