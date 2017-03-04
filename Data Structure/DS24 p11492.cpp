#include <iostream>
#include <stdio.h>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <algorithm>

using namespace std;

//#define DEBUG 1

struct queue_node{
	int dist;
	int graph_node;
};

struct set_node{
	int graph_node;
	char reach_letter;
};

struct graph_node{
	int graph_node;
	string word;
};

class compare_queue{
	public:
	bool operator()(const struct queue_node& lhs, const queue_node& rhs){
		return lhs.dist < rhs.dist;
	}
};

inline bool operator<(const struct set_node& lhs, const struct set_node& rhs){
    if(lhs.graph_node == rhs.graph_node){
        return (lhs.reach_letter < rhs.reach_letter);
    }
    return (lhs.graph_node < rhs.graph_node);
}

int main(){
	//Part 1: Graph construction
	string start_lang, end_lang, node1, node2, connector;
	int edges,index;
	cin >> edges;
	while(edges){
		//Input start and end
		cin >> start_lang >> end_lang;
		//Setup map
		map<string,int> get_node;
		//Graph setup (vector of vector)
		vector<vector<struct graph_node> > graph;

		index = 0;
		for(int i=0;i<edges;i++){
			cin >> node1 >> node2 >> connector;
			//Index the graph nodes in umerical form
			if(get_node.count(node1) == 0){
				get_node[node1] = index;
				//Add in the graph
				vector<struct graph_node> temp_list;
				graph.push_back(temp_list);

				index++;
			}
			if(get_node.count(node2) == 0){
				get_node[node2] = index;
				//Add in the graph
				vector<struct graph_node> temp_list;
				graph.push_back(temp_list);

				index++;
			}
			//Extend the graph with current edge
			struct graph_node temp_node;
			//Add straight connection
			temp_node.graph_node = get_node[node2];
			temp_node.word = connector;
			graph[get_node[node1]].push_back(temp_node);
			//Add the reverse link
			temp_node.graph_node = get_node[node1];
			temp_node.word = connector;
			graph[get_node[node2]].push_back(temp_node);

		}
		//Graph has been contructed (through adjency list)
		//Part 2: Initialization to run algorithm
		set<struct set_node> visit_info;
		priority_queue<struct queue_node, vector<struct queue_node>, compare_queue> pq;
		//Make starting node visited from possibly every letter
		for(char visit_letter = 'a'; visit_letter<='z'; visit_letter++){
			struct set_node visited;
			visited.graph_node = get_node[start_lang];
			visited.reach_letter = visit_letter;
			visit_info.insert(visited);
		}
		//Put the starting node in queue
		struct queue_node temp_pq;
		temp_pq.dist = 0;
		temp_pq. graph_node = get_node[start_lang];
		pq.push(temp_pq);
#ifdef DEBUG
        //Check for map
        cout << "Checking map...." << endl;
        for(map<string, int>::iterator iter = get_node.begin();iter!=get_node.end();iter++){
            cout << iter->first << " " << iter->second << endl;
        }
        //Check for queue
        cout << "Checking priority queue...." << endl;
        while(!pq.empty()){
            cout << pq.top().graph_node << " " << pq.top().dist << endl;
            pq.pop();
        }
        //Check for set
        cout << "Checking set...." << endl;
		for (set<struct set_node, vector<struct set_node>>::iterator iter=visit_info.begin(); iter!=visit_info.end(); ++iter){
			cout << (*iter).graph_node << " " <<(*iter).reach_letter << endl;
		}
        //Check for graph connections
		cout << "Checking graph...." << endl;
		for(vector<vector<struct graph_node> >::iterator iter = graph.begin(); iter!=graph.end(); iter++){
			for(vector<struct graph_node>::iterator it = (*iter).begin(); it!=(*iter).end(); it++){
				cout << (*it).graph_node << " " << (*it).word << "::";
			}
			cout << endl;
		}

#endif // DEBUG
        //Part 3: Run the f*****g algorithm
		//While queue is empty or end node is reached (whichever first), break

		cin >> edges;
	}

	return 0;
}
