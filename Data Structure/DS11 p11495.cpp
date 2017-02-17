#include <iostream>

using namespace std;

long long int arr[100000];

long long int merge_inversions(long long int s, long long int m, long long int e){
	long long int i=s,j=m,k=0,ret=0;
	long long int temp[e-s + 1];
	while(i<m && j<=e){
		if(arr[i] > arr[j]){
			temp[k] = arr[j];
			ret+=(m-i);
			j++;
		}
		else{
			temp[k] = arr[i];
			i++;
		}
		k++;
	}
	while(i<m){
		temp[k] = arr[i];
		i++;
		k++;
	}
	while(j<=e){
		temp[k] = arr[j];
		j++;
		k++;
	}
	k=0;
	for(long long int i=s;i<=e;i++){
        arr[i] = temp[k];
        k++;
	}
	return ret;
}

long long int merge_sort_inversion(long long int start, long long int ends){
	long long int mid = start + (ends-start)/2,left_sort,right_sort,middle;
	//Base case
	if(start==ends){
		return 0;
	}
	//Main case
	left_sort = merge_sort_inversion(start, mid);
	right_sort = merge_sort_inversion(mid+1,ends);
	middle = merge_inversions(start,mid+1,ends);
	return (left_sort+right_sort+middle);
}

long long int nr_inversion(long long int n){
	return merge_sort_inversion(0,n-1);
}

int main(){
	long long int N;
	cin >> N;
	while(N){
		for(long long int i=0;i<N;i++){
			cin >> arr[i];
		}
		if(nr_inversion(N)%2==0){
			cout << "Carlos" << endl;
		}
		else{
			cout << "Marcelo" << endl;
		}
		cin >> N;
	}
	return 0;
}
