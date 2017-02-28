#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

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
    /*for(int i=0;i<len;i++){
        cout << new_input[i];
	}
	cout << endl;*/
	return sz;
}

bool comp(string a, string b){
	int a_inversions = nr_inversion(a);
	int b_inversions = nr_inversion(b);
	return (a_inversions < b_inversions);
}

int main(){
	int T,n,m;
	string dna;
	cin >> T;
	while(T--){
		cin >> n >> m;
		vector<string> vec;
		for(int i=0;i<m;i++){
			cin >> dna;
			vec.push_back(dna);
		}
		stable_sort(vec.begin(), vec.end(),comp);
		for(int i=0;i<m;i++){
			cout << vec[i] << endl;
		}
		cout << endl;
	}
	return 0;
}
