#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

bool adj_mat[6][6];
bool allowed_connection[6][6];
vector<int> print_vector;

int init_graph(void){
	for(int i=0;i<=5;i++){
		for(int j=0;j<=5;j++){
			adj_mat[i][j] = false;
			allowed_connection[i][j] = false;
		}
	}
	int node1[] = {1,1,1,2,2,2,3,3,3,3,5,5,5,5,4,4};
	int node2[] = {2,3,5,1,5,3,1,2,5,4,1,2,3,4,5,3};
	int connections = sizeof(node1)/sizeof(node1[0]);
	for(int i=0;i<connections;i++){
		allowed_connection[node1[i]][node2[i]] = true;
	}
	return (connections/2);
}

void santa_visit(int current_node, int edges_to_cover){
	if(edges_to_cover==0){
		print_vector.push_back(current_node);
		for(int i=0;i<print_vector.size();i++){
			cout << print_vector[i];
		}
		cout << endl;
		print_vector.pop_back();
	}
	else{
		for(int i=1;i<=5;i++){
			if(allowed_connection[current_node][i] && !adj_mat[current_node][i]){
				adj_mat[current_node][i] = true;
				adj_mat[i][current_node] = true;
				print_vector.push_back(current_node);
				santa_visit(i,edges_to_cover-1);
				print_vector.pop_back();
				adj_mat[current_node][i] = false;
				adj_mat[i][current_node] = false;
			}
		}
	}
}

int main(){
	int connections = init_graph();
	santa_visit(1,connections);
	return 0;
}
