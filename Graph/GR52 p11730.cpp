#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int S,T;
vector<int> seive;
vector<int> prime_factors;
vector<bool> visited;

void compute_prime_factors(int n){
    seive.clear();
    seive.resize(n+1,-1);
    prime_factors.clear();
    for(int i=2;i<n;i++){
        if(seive[i]==-1){
            if(n%i == 0){
                seive[i] = 1;
                prime_factors.push_back(i);
            }
            for(int j=2;j<S;j++){
                if(i*j>=S){
                    break;
                }
                else{
                    seive[i*j] = 0;
                }
            }
        }
    }
}

void sieve() {
    int mark[1005] = {}, i, j;
    for(i = 2; i < 1000; i++) {
        if(mark[i] == 0) {
            for(j = i+i; j < 1000; j += i)
                mark[j] = 1;
            prime_factors.push_back(i);
        }
    }
}

int compute_dist(void){
    int ret = 0;
    queue<int> bfs_queue;
    bfs_queue.push(S);
    bfs_queue.push(-1);
	visited.clear();
	visited.resize(1001, false);
    while(!bfs_queue.empty()){
        int temp = bfs_queue.front();
        bfs_queue.pop();
        if(temp==-1){
            if(bfs_queue.empty()){
                ret = -1;
                break;
            }
            bfs_queue.push(-1);
            ret++;
        }
        else{
            if(temp == T){
                break;
            }
            else{
                //compute_prime_factors(temp);
                for(int i=0;i<prime_factors.size() && prime_factors[i]<temp;i++){
                    if(temp+prime_factors[i] <=T && temp%prime_factors[i] == 0 && !visited[temp+prime_factors[i]]){
                        bfs_queue.push(temp+prime_factors[i]);
						visited[temp+prime_factors[i]] = true;
                    }
                }
            }
        }
    }
    return ret;
}

int main(){
    //freopen("output.txt","w",stdout);
	int nr_case = 1;
	//compute_prime_factors(1005);
	sieve();
	cin >> S >> T;
	while(S+T){

		/*for(int i=0;i<prime_factors.size();i++){
            cout << prime_factors[i] << " ";

		}*/
		if(prime_factors.size() == 0 || T<S){
            cout << "Case " << nr_case << ": " << -1 << endl;
		}
		else{
            cout << "Case " << nr_case << ": " << compute_dist() << endl;
		}
		nr_case++;
		cin >> S >> T;
	}
	return 0;
}
