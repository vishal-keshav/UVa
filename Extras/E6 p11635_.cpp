#include <iostream>
#include <queue>

using namespace std;

struct node{
	int city;
	int dist;
	struct node *next;
};

struct q_node_new{
	int city;
	int dist_covered;
};

bool new_graph[102][102];
int hotel_city[10001];
int hotel_index[101];
bool visited[102];

int N,h;

bool hotel[10001];
struct node **adj_list;

void construct_new_graph(int new_graph_index, int old_graph_index){
	//make true new_graph[0][i] = true wherever applicable
	queue<struct q_node_new> visits;
	struct q_node_new push_node;
	struct q_node_new pop_node;

	push_node.city = old_graph_index;
	push_node.dist_covered = 0;
	visits.push(push_node);
	while(!visits.empty()){
		pop_node = visits.front();
		visits.pop();
		struct node *iter_node = adj_list[pop_node.city];
		while(iter_node){
			if(pop_node.dist_covered + iter_node->dist <=600){
				push_node.city = iter_node->city;
				push_node.dist_covered = pop_node.dist_covered + iter_node->dist;
				visits.push(push_node);
				//connect if node is any of the h+2 nodes
				if(hotel[iter_node->city]){
					new_graph[new_graph_index][hotel_city[iter_node->city]] = true;
					new_graph[hotel_city[iter_node->city]][new_graph_index] = true;
				}
				else if(iter_node->city == 1){
					new_graph[new_graph_index][0] = true;
					new_graph[0][new_graph_index] = true;
				}
				else if(iter_node->city == N){
					new_graph[new_graph_index][h+1] = true;
					new_graph[h+1][new_graph_index] = true;
				}
				else{
					//do nothing
				}
			}
			iter_node = iter_node->next;
		}
	}
}

int BFS(int start_index, int stop_index){
    int ret = -1;
    int counter = 0;
    int popped;
    queue<int> visits;
    //setting visited
    for(int i=0;i<h+2;i++){
        visited[i] = false;
    }
    visits.push(start_index);
    visits.push(-1);
    visited[0] = true;
    while(1){
        popped = visits.front();
        visits.pop();
        if(popped == -1){
            if(visits.empty()){
                break;
            }
            else{
                visits.push(-1);
                counter++;
            }
        }
        else{
            if(popped == stop_index){
                ret = counter-1;
                break;
            }
            else{
                //iterate through all neighbour
                for(int i=0;i<h+2;i++){
                    if(new_graph[popped][i] && !visited[i]){
                        visits.push(i);
                        visited[i] = true;
                    }
                }
            }
        }
    }
    return ret;
}

int main(){
	int temp_h,m;
	int src, dest, dist;
	struct node *temp_node;
	cin >> N;
	while(N){
		//memory setting
		for(int i=0;i<=N;i++){
			hotel[i] = false;
		}
		cin >> h;
		for(int i=1;i<=h;i++){
			cin >> temp_h;
			hotel_city[temp_h] = i;
			hotel[temp_h] = true;
			hotel_index[i] = temp_h;
		}
		//setting graph memory
		adj_list = new struct node*[N+1];
		for(int i=1;i<=N;i++){
			adj_list[i] = NULL;
		}
		//setting new_graph memory
		for(int i=0;i<h+2;i++){
			for(int j=0;j<h+2;j++){
				new_graph[i][j] = false;
			}
		}
		cin >> m;
		for(int i=0;i<m;i++){
			cin >> src >> dest >> dist;
			temp_node = new struct node;
			temp_node->city = dest;
			temp_node->dist = dist;
			temp_node->next = adj_list[src];
			adj_list[src] = temp_node;
			//reverse connection as well
			temp_node = new struct node;
			temp_node->city = src;
			temp_node->dist = dist;
			temp_node->next = adj_list[dest];
			adj_list[dest] = temp_node;
		}
		/***********************************************************************************/
		//index 0 is starting point, city 1
		//index h+1 is ending point, city NULL
		//rest are ordered hotel city
		construct_new_graph(0,1);
		for(int i=1;i<=h;i++){
			construct_new_graph(i,hotel_index[i]);
		}
		construct_new_graph(h+1,N);
        //removing self links
        for(int i=0;i<h+2;i++){
            new_graph[i][i] = false;
        }
		//Apply BFS to new_graph and find smallest number of edges to reach h+1 from 0
		int nr_steps = BFS(0,h+1);
		cout << nr_steps << endl;
		cin >> N;
	}


	return(0);
}
