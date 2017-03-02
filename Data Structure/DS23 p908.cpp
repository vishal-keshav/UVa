#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int uf_find(int *set_array,int node){
    if(set_array[node]!=set_array[set_array[node]]){
        set_array[node] = uf_find(set_array,set_array[node]);
    }
    return set_array[node];
}

bool uf_union(int *set_array,int *rank_array,int node1,int node2){
    int parent1 = uf_find(set_array,node1);
    int parent2 = uf_find(set_array,node2);
    int temp;
    if(parent1==parent2){
        return false;
    }
    if(rank_array[parent1]>rank_array[parent2]){
        temp = parent1;
        parent1 = parent2;
        parent2 = temp;
    }
    if(rank_array[parent1]==rank_array[parent2]){
        rank_array[parent2]++;
    }
    set_array[parent1]=parent2;
    return true;
}

struct connection{
	long int node_a;
	long int node_b;
	long int link_cost;
};

//Operator overloading
class comp{
	public:
		bool operator() (struct connection &lhs, struct connection &rhs){
			return (lhs.link_cost >= rhs.link_cost);
		}
};

int main(){
    //freopen("output.txt","w",stdout);
    long int N;
    bool new_line = false;
	while(scanf("%ld",&N)!=EOF){
        if(new_line){
            printf("\n");
        }
        long int M,K,cost,temp_node1,temp_node2,links;
        struct connection temp_connection;
		int total_cost = 0;
		for(long int i=0;i<N-1;i++){
			scanf("%ld %ld %ld",&temp_node1, &temp_node2, &cost);
			total_cost+=cost;
		}
		printf("%ld\n",total_cost);
		priority_queue<struct connection, vector<struct connection>, comp> my_q;
		scanf("%ld",&K);

		for(long int i=0;i<K;i++){
			scanf("%ld %ld %ld",&temp_node1, &temp_node2, &cost);
			temp_connection.node_a = temp_node1;
			temp_connection.node_b = temp_node2;
			temp_connection.link_cost = cost;
			my_q.push(temp_connection);
		}
		scanf("%ld",&M);
		for(long int i=0;i<M;i++){
			scanf("%ld %ld %ld",&temp_node1, &temp_node2, &cost);
			temp_connection.node_a = temp_node1;
			temp_connection.node_b = temp_node2;
			temp_connection.link_cost = cost;
			my_q.push(temp_connection);
		}
		int *set_array = new int[N];
		int *rank_array = new int[N];
		for(long int i=0;i<N;i++){
			set_array[i] = i;
			rank_array[i] = 1;
		}
		links = 0;
		total_cost = 0;
		while(links<N-1){
            //cout << "What" << endl;
			temp_connection = my_q.top();
			if(uf_union(set_array,rank_array,temp_connection.node_a-1,temp_connection.node_b-1)){
				//cout << temp_connection.node_a << " " << temp_connection.node_b << endl;
				total_cost+=temp_connection.link_cost;
				links++;
			}
			my_q.pop();
		}
		printf("%ld\n",total_cost);
		new_line = true;
	}
	return 0;
}
