#include <iostream>
#include <stdio.h>
#include <queue>
#include <map>

//#define DEBUG 1

using namespace std;

bool graph[30][30];
bool visited[30];

void init_graph(void){
	for(int i=0;i<30;i++){
		for(int j=0;j<30;j++){
			graph[i][j] = false;
		}
	}
}

void init_visit(void){
    for(int i=0;i<30;i++){
        visited[i] = false;
    }
}

int out_of_reach(int starting_node, int hops_left, int N){
    int ret = 0,current;
    queue<int> my_queue;
    my_queue.push(-1);
    my_queue.push(starting_node);
    visited[starting_node] = true;
    while(!my_queue.empty() && hops_left!=0){
        //Decrement ttl condition
        if(my_queue.front() == -1){
            my_queue.pop();
            //Starting new level
            my_queue.push(-1);
            hops_left--;
        }
        else{
            current = my_queue.front();
            my_queue.pop();
            for(int i=0;i<N;i++){
                if(!visited[i] && graph[current][i]){
                    visited[i] = true;
                    my_queue.push(i);
                }
            }
        }
    }

    for(int i=0;i<N;i++){
        if(!visited[i]){
            ret++;
        }
    }
    return ret;
}

#ifdef DEBUG
void print_graph(int N){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }
}
#endif // DEBUG


int main(){

	int NC, node_a, node_b, node, ttl, case_nr=1;
	int graph_node_index;

	cin >> NC;
	while(NC){
		init_graph();

		map<int,int> graph_node;
		graph_node_index = 0;

		for(int i=0;i<NC;i++){
			cin >> node_a >> node_b;
			if(graph_node.count(node_a)==0){
				graph_node[node_a] = graph_node_index++;
			}
			if(graph_node.count(node_b)==0){
				graph_node[node_b] = graph_node_index++;
			}
			graph[graph_node[node_a]][graph_node[node_b]] = true;
			graph[graph_node[node_b]][graph_node[node_a]] = true;
		}
#ifdef DEBUG
		print_graph(graph_node_index);
#endif

		cin >> node >> ttl;
		while(node+ttl){
            init_visit();
			cout << "Case " << case_nr << ": " << out_of_reach(graph_node[node], ttl+1, graph_node_index)\
			<< " nodes not reachable from node " << node << " with TTL = " << ttl << "." << endl;
			case_nr++;
			cin >> node >> ttl;
		}

		cin >> NC;
	}


	return 0;
}
