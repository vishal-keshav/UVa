#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct elem{
    string dna;
    int inversions;
};

int merge_inversions(char *input, int s, int m, int e){
	int i=s,j=m,k=0,ret=0;
	char temp[e-s + 1];
	while(i<m && j<=e){
		if(input[i] > input[j]){
			temp[k] = input[j];
			ret+=(m-i);
			//cout << (m-i) << endl;
			j++;
		}
		else{
			temp[k] = input[i];
			i++;
		}
		k++;
	}
	while(i<m){
		temp[k] = input[i];
		i++;
		k++;
	}
	while(j<=e){
		temp[k] = input[j];
		j++;
		k++;
	}
	k=0;
	for(int i=s;i<=e;i++){
        input[i] = temp[k];
        k++;
	}
	return ret;
}

int merge_sort_inversions(char *input, int start, int ends){
	int mid = start + (ends-start)/2,left_sort,right_sort,middle;
	//Base case
	if(start==ends){
		return 0;
	}
	//Main case
	left_sort = merge_sort_inversions(input, start, mid);
	right_sort = merge_sort_inversions(input, mid+1,ends);
	middle = merge_inversions(input,start,mid+1,ends);
	return (left_sort+right_sort+middle);
}

int nr_inversion(string input){
	int len = input.length(),sz;
	char new_input[len];
	for(int i=0;i<len;i++){
        new_input[i] = input[i];
	}
	sz = merge_sort_inversions(new_input,0,len-1);
	return sz;
}

bool comp(struct elem a, struct elem b){
	return (a.inversions < b.inversions);
}

int main(){
	int T,n,m,inv;
	string dna;
	cin >> T;
	while(T--){
		cin >> n >> m;
		vector<struct elem> vec;
		for(int i=0;i<m;i++){
			cin >> dna;
			inv = nr_inversion(dna);
			struct elem e;
			e.dna = dna;
			e.inversions = inv;
			vec.push_back(e);
		}
		stable_sort(vec.begin(), vec.end(),comp);
		for(int i=0;i<m;i++){
			cout << vec[i].dna << endl;
		}
		if(T!=0){
            cout << endl;
		}
	}
	return 0;
}
