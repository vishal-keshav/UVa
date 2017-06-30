//Correction: All sticks has to be used for creating a square

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <math.h>

//#define DEBUG 1

using namespace std;

int T,N;
vector<int> input;
vector<int> length;

void fill_length(int index, int bitmask){
	if(index>=N){
		return;
	}
	else{
		//Dont take this
		fill_length(index+1, bitmask);
		//Take this
		length[bitmask | 1<<index] = length[bitmask]+input[index];
		fill_length(index+1,bitmask | 1<<index);
	}
}

int main(){
	cin >> T;
	while(T--){
		cin >> N;
		input.clear();
		input.resize(N);
		for(int i=0;i<N;i++){
			cin >> input[i];
		}
		length.clear();
		length.resize(pow(2,N),0);
		fill_length(0,0);
#ifdef DEBUG
        for(int i=0;i<pow(2,N);i++){
            cout << i << " " << length[i] << endl;
        }
#endif // DEBUG
        int M = pow(2,N);
        bool answer = false;
        for(int i=0;i<M;i++){
            for(int j=0;j<M;j++){
                if(i!=j && length[i]==length[j] && (i&j)==0){
                    for(int k=0;k<M;k++){
                        if(j!=k && length[j]==length[k] && (i&k)==0 && (j&k)==0){
                            for(int l=0;l<M;l++){
                                if(l!=k && length[k]==length[l] && (i&l)==0 && (j&l)==0 && (k&l)==0){
									if((i | j | k | l)==M-1){
										answer = true;
									}
                                }
                                if(answer){
                                    break;
                                }
                            }
                        }
                        if(answer){
                            break;
                        }
                    }
                }
                if(answer){
                    break;
                }
            }
            if(answer){
                break;
            }
        }
        if(answer){
            cout << "yes" << endl;
        }
        else{
            cout << "no" << endl;
        }
	}

	return 0;
}
