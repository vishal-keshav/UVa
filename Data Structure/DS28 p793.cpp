#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>

using namespace std;

class uf{
	public:
		uf(long int initial_set_size){
			set_array = new long int[initial_set_size];
			rank_array = new long int[initial_set_size];
			size_array = new long int[initial_set_size];
			for(long int i = 0;i<initial_set_size;i++){
				set_array[i] = i;
				rank_array[i] = 1;
				size_array[i] = 1;
			}
			nr_sets = initial_set_size;
			nr_elements = initial_set_size;
		}

		long int find_set(long int node){
			if(set_array[node]!=set_array[set_array[node]]){
				set_array[node] = find_set(set_array[node]);
			}
			return set_array[node];
		}

		bool union_set(long int node1, long int node2){
			long int parent1 = find_set(node1);
			long int set_size1 = size_array[find_set(node1)];

			long int parent2 = find_set(node2);
			long int set_size2 = size_array[find_set(node2)];

			if(parent1==parent2){
				return false;
			}
			int temp;
			if(rank_array[parent1] > rank_array[parent2]){
				temp = parent1;
				parent1 = parent2;
				parent2 = temp;
			}
			if(rank_array[parent1] == rank_array[parent2]){
				rank_array[parent2]++;
			}
			set_array[parent1] = parent2;
			size_array[find_set(parent1)] = set_size1 + set_size2;
			nr_sets--;
			return true;
		}

		bool is_same_set(long int node1, long int node2){
			if(find_set(node1)==find_set(node2)){
				return true;
			}
			else{
				return false;
			}
		}
		long int number_of_sets(void){
			return nr_sets;
		}
		long int size_of_set(long int node){
			return size_array[find_set(node)];
		}

	private:
		long int nr_sets;
		long int nr_elements;
		long int *set_array;
		long int *rank_array;
		long int *size_array;

};

int main(){
	int T,nr_computers,success, not_success;
	string line;
	bool ret;
	cin >> T;

	while(T--){
		cin >> nr_computers;
		uf connections(nr_computers);
		success = 0;
		not_success = 0;
		cin.ignore();

		while(getline(cin,line) && line.length()!=0){
            stringstream ss(line);
            string word;
            int node1,node2;
            ss >> word >> node1 >> node2;
            //ss >> node1;
            //ss >> node2;
            //cout << word << node1 << node2;
			if(word=="c"){
				//ret = connections.union_set(line[2]-'1', line[4]-'1');
				ret = connections.union_set(node1-1,node2-1);
			}
			else{
				if(connections.is_same_set(node1-1,node2-1)){
					success++;
				}
				else{
					not_success++;
				}
			}
		}
		cout << success << "," << not_success << endl;
		if(T!=0){
			cout << endl;
		}
	}
	return 0;
}