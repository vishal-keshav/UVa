#include <iostream>
#include <map>
#include <stdio.h>
#include <vector>
#include <sstream>

using namespace std;

//Union find quick implementation
vector<int> uf_set_vec(201);
void init_set(int _size){
	uf_set_vec.resize(_size);
	for(int i=0;i<_size;i++){
		uf_set_vec[i] = i;
	}
}
int find_set(int node){
	if(uf_set_vec[node]==node){
        return node;
	}
	else{
        uf_set_vec[node] = find_set(uf_set_vec[node]);
        return uf_set_vec[node];
	}
}
void union_set(int node1, int node2){
	uf_set_vec[find_set(node1)] = find_set(node2);
	return;
}

bool is_same_set(int i, int j){
	return (find_set(i)==find_set(j));
}

int get_mut_elem(string input){
	int ret;
	stringstream ss(input);
	ss >> ret;
	return ret;
}

bool is_common(string input){
	if(input[0] <= 'Z' && input[0] >= 'A'){
		return true;
	}
	else{
		return false;
	}
}

int main(){
    //freopen("output.txt","w",stdout);
	int T;
	while(!cin.eof() && cin >> T){
		vector<string> dna1,dna2;
		string input;
		for(int i=0;i<T;i++){
			cin >> input;
			dna1.push_back(input);
		}
		for(int i=0;i<T;i++){
			cin >> input;
			dna2.push_back(input);
		}
		bool possible = true;
		init_set(200);
		map<int,char> mut;
		for(int i=0;i<T;i++){
			//Case 1: both common dna
			if(is_common(dna1[i]) && is_common(dna2[i])){
				//cout << "both common: "<<dna1[i] << " " << dna2[i] << endl;
				if(dna1[i]!=dna2[i]){
					possible = false;
					break;
				}
				else{
					continue;
				}
			}
			//Both of them are mutation element
			else if(!is_common(dna1[i]) && !is_common(dna2[i])){

				int dna1_mut = get_mut_elem(dna1[i]);
				int dna2_mut = get_mut_elem(dna2[i]);
				char id;
				//cout << "both uncommon: "<<dna1_mut << " " << dna2_mut << endl;
				//cout << "to check " << find_set(dna1_mut) << " " << find_set(dna2_mut) << endl;
				//If both have not been assigned a common element
				if(mut.count(find_set(dna1_mut))==0 && mut.count(find_set(dna2_mut))==0){
					//Just put them together in set
					//cout << "Case 1" << endl;
					if(!is_same_set(dna1_mut,dna2_mut)){
						union_set(dna1_mut,dna2_mut);
					}
				}
				else if(mut.count(find_set(dna1_mut))==0){
					//cout << "Case 2" << endl;
					if(!is_same_set(dna1_mut,dna2_mut)){
                        id = mut[find_set(dna2_mut)];
						union_set(dna1_mut,dna2_mut);
						mut[find_set(dna1_mut)] = id;
                        mut[find_set(dna2_mut)] = id;
					}

				}
				else if(mut.count(find_set(dna2_mut))==0){
					//cout << "Case 3" << endl;
					if(!is_same_set(dna1_mut,dna2_mut)){
                        id = mut[find_set(dna1_mut)];
						union_set(dna1_mut,dna2_mut);
						mut[find_set(dna1_mut)] = id;
						mut[find_set(dna2_mut)] = id;
					}

				}
				else{
					//cout << "Case 4" << endl;
					if(mut[find_set(dna1_mut)]!=mut[find_set(dna2_mut)]){
						possible = false;
						break;
					}
					else{
						if(!is_same_set(dna1_mut,dna2_mut)){
                            id = mut[find_set(dna1_mut)];
							union_set(dna1_mut,dna2_mut);
                            mut[find_set(dna1_mut)] = id;
						}
					}
				}
			}
			//One of them is mutation and other is not
			else{
				//cout << "alternate: "<<dna1[i][0] << " " << dna2[i][0] << endl;
				if(is_common(dna1[i])){
					int dna2_mut = get_mut_elem(dna2[i]);
					//cout << "Subcase1 " << dna2_mut << endl;
					if(mut.count(find_set(dna2_mut))==0){
						//Assign
						mut[find_set(dna2_mut)] = dna1[i][0];
						//cout << mut[find_set(dna2_mut)] << " at " << find_set(dna2_mut) << " " << find_set(dna2_mut)<< endl;
					}
					else{
						if(mut[find_set(dna2_mut)] != dna1[i][0]){
							possible = false;
							break;
						}
						else{
							continue;
						}
					}
				}
				else{
					int dna1_mut = get_mut_elem(dna1[i]);
					//cout << "Subcase2 " << dna1_mut << endl;
					if(mut.count(find_set(dna1_mut))==0){
						//Assign
						mut[find_set(dna1_mut)] = dna2[i][0];
						//cout << mut[find_set(dna1_mut)] << " at " << find_set(dna1_mut)<< endl;
					}
					else{
						if(mut[find_set(dna1_mut)] != dna2[i][0]){
							possible = false;
							break;
						}
						else{
							continue;
						}
					}
				}
			}
		}
		if(possible){
			cout << "YES" << endl;
			//Print minimal mutation
			for(int i=0;i<=200;i++){
				if(mut.count(find_set(i))!=0){
					cout << i << " " << mut[find_set(i)] << endl;
				}
			}
		}
		else{
			cout << "NO" << endl;
		}
		cout << endl;
	}
	return 0;
}
