#include <iostream>
#include <stdio.h>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <algorithm>

using namespace std;

#define MAXIMUM_INT 1000000
//#define DEBUG 1
//#define DEBUG2 2

struct queue_node{
	int dist;
	int graph_node;
	char initial_letter;
};

struct set_node{
	int graph_node;
	string reach_word;
};

struct graph_node{
	int graph_node;
	string word;
};

class compare_queue{
	public:
        bool operator()(const struct queue_node& lhs, const queue_node& rhs){
            return lhs.dist > rhs.dist;
        }
};

inline bool operator<(const struct set_node& lhs, const struct set_node& rhs){
    if(lhs.graph_node == rhs.graph_node){
        return (lhs.reach_word < rhs.reach_word);
    }
    return (lhs.graph_node < rhs.graph_node);
}

//Global varibale for faster access
set<struct set_node> visit_info;

int word_length(string input){
	return (input.length());
}

bool not_visited(int g_node, string init_word){
	struct set_node temp;
	temp.graph_node = g_node;
	temp.reach_word = init_word;
	set<struct set_node>::iterator it = visit_info.find(temp);
	if(it!=visit_info.end()){
		return false;
	}
	else{
		return true;
	}
}

/*bool sort_comp(struct graph_node elem1, struct graph_node elem2){
    return (elem1.word.length() < elem2.word.length());
}*/


int main(){
    //freopen("output.txt","w",stdout);
	//Part 1: Graph construction
	string start_lang, end_lang, node1, node2, connector;
	int edges,index;
	cin >> edges;
	vector<string> generic_connector;
	//struct graph_node generic_elem;
	//Initialize generic connection for initializing graph
	for(char i='a';i<='z';i++){
        generic_connector.push_back("?");
	}

	while(edges){
		//Setup map
		map<string,int> get_node;
		//Graph setup (vector of vector)
		vector<map<int, vector<string> > > graph;

		index = 0;
        //Input start and end
		cin >> start_lang >> end_lang;
		if(get_node.count(start_lang) == 0){
            get_node[start_lang] = index;
            //Add in the graph
            //vector<struct graph_node> temp_list;
            //graph.push_back(generic_connector);

            map<int,vector<string> > graph_map;
            graph.push_back(graph_map);
            index++;
		}
        if(get_node.count(end_lang) == 0){
            get_node[end_lang] = index;
            //Add in the graph
            //vector<struct graph_node> temp_list;
            //graph.push_back(generic_connector);
            map<int,vector<string> > graph_map;
            graph.push_back(graph_map);
            index++;
		}
		for(int i=0;i<edges;i++){
			cin >> node1 >> node2 >> connector;
			//Index the graph nodes in umerical form
			if(get_node.count(node1) == 0){
				get_node[node1] = index;
				//Add in the graph
				//vector<struct graph_node> temp_list;
				//graph.push_back(generic_connector);
                map<int,vector<string> > graph_map;
                graph.push_back(graph_map);
				index++;
			}
			if(get_node.count(node2) == 0){
				get_node[node2] = index;
				//Add in the graph
				//vector<struct graph_node> temp_list;
				//graph.push_back(generic_connector);
                map<int,vector<string> > graph_map;
                graph.push_back(graph_map);
				index++;
			}
			//Extend the graph with current edge
			//struct graph_node temp_node;
			//Add straight connection
			//temp_node.graph_node = get_node[node2];
			//temp_node.word = connector;
			/*if(graph[get_node[node1]][connector[0]-'a'].graph_node>=0){
                if(word_length(graph[get_node[node1]][connector[0]-'a'].word)>word_length(connector)){
                    graph[get_node[node1]][connector[0]-'a'] = temp_node;
                }
			}
			else{
                graph[get_node[node1]][connector[0]-'a'] = temp_node;
			}*/
			//Check is already a connection
			if(graph[get_node[node1]].count(get_node[node2])==0){
                graph[get_node[node1]][get_node[node2]] = generic_connector;
                graph[get_node[node1]][get_node[node2]][connector[0]-'a'] = connector;
			}
			else{
                if(graph[get_node[node1]][get_node[node2]][connector[0]-'a']!="?"){
                    if(word_length(connector) < word_length(graph[get_node[node1]][get_node[node2]][connector[0]-'a'])){
                        graph[get_node[node1]][get_node[node2]][connector[0]-'a'] = connector;
                    }
                }
                else{
                    graph[get_node[node1]][get_node[node2]][connector[0]-'a'] = connector;
                }
			}
			//graph[get_node[node1]].push_back(temp_node);
			//Add the reverse link
			//temp_node.graph_node = get_node[node1];
			//temp_node.word = connector;
			/*if(graph[get_node[node2]][connector[0]-'a'].graph_node>=0){
                if(word_length(graph[get_node[node2]][connector[0]-'a'].word)>word_length(connector)){
                    graph[get_node[node2]][connector[0]-'a'] = temp_node;
                }
			}
			else{
                graph[get_node[node2]][connector[0]-'a'] = temp_node;
			}*/
						//Check is already a connection
			if(graph[get_node[node2]].count(get_node[node1])==0){
                graph[get_node[node2]][get_node[node1]] = generic_connector;
                graph[get_node[node2]][get_node[node1]][connector[0]-'a'] = connector;
			}
			else{
                if(graph[get_node[node2]][get_node[node1]][connector[0]-'a']!="?"){
                    if(word_length(connector) < word_length(graph[get_node[node2]][get_node[node1]][connector[0]-'a'])){
                        graph[get_node[node2]][get_node[node1]][connector[0]-'a'] = connector;
                    }
                }
                else{
                    graph[get_node[node2]][get_node[node1]][connector[0]-'a'] = connector;
                }
			}
			//graph[get_node[node2]].push_back(temp_node);

		}
		//Sort the connections w.r.t. word lenght
		/*for(vector<vector<struct graph_node> >::iterator iter=graph.begin(); iter!=graph.end(); iter++){
            sort((*iter).begin(),(*iter).end(),sort_comp);
		}*/
		//Graph has been contructed (through adjency list)
		//Part 2: Initialization to run algorithm
		/*set<struct set_node> visit_info;
		priority_queue<struct queue_node, vector<struct queue_node>, compare_queue> pq;*/
		visit_info.clear();
		priority_queue<struct queue_node, vector<struct queue_node>, compare_queue> pq;
		//Make starting node visited from possibly every letter
		for(char visit_letter = 'a'; visit_letter<='z'; visit_letter++){
			struct set_node visited;
			visited.graph_node = get_node[start_lang];
			visited.reach_word = string(1,visit_letter);
			visit_info.insert(visited);
		}
		//Put the starting node in queue
		struct queue_node temp_pq;
		temp_pq.dist = 0;
		temp_pq.graph_node = get_node[start_lang];
		temp_pq.initial_letter = '?';
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
			cout << (*iter).graph_node << " " <<(*iter).reach_word << endl;
		}
        //Check for graph connections
		cout << "Checking graph...." << endl;
		for(vector<map<int,vector<string> > >::iterator iter = graph.begin(); iter!=graph.end(); iter++){
			for(map<int,vector<string> >::iterator it = (*iter).begin(); it!=(*iter).end(); it++){
				//cout << it->first << " " << it->second << "::";
				cout << it->first << " ";
				for(vector<string>::iterator i = (it->second).begin(); i!=(it->second).end();i++){
                    if((*i)!="?"){
                        cout << (*i) << ":";
                    }
				}
				cout << "::";
			}
			cout << endl;
		}

#endif // DEBUG
#ifndef DEBUG
        //Part 3: Run the f*****g algorithm
		//While queue is empty or end node is reached (whichever first), break
		bool found = false, cannot_be_found = false;
		int best_ans = MAXIMUM_INT;
		if(get_node[start_lang] == get_node[end_lang]){
            cannot_be_found = true;
		}

		while(!pq.empty()){
            if(cannot_be_found){
                cout << "impossivel" << endl;
                found = true;
                break;
            }

			temp_pq = pq.top();
#ifdef DEBUG2
            cout << "popped: " << temp_pq.graph_node << " with dist: " << temp_pq.dist << " " << temp_pq.initial_letter << endl;
#endif // DEBUG2
			pq.pop();
			//Check if we have reached the final language
			if(temp_pq.graph_node == get_node[end_lang]){
				//cout << temp_pq.dist << endl;
				best_ans = min(best_ans,temp_pq.dist);
				found = true;
				//break;
			}
			//Otherwise insert neighbours unvisited
			/*for(vector<struct graph_node>::iterator iter = graph[temp_pq.graph_node].begin(); iter!=graph[temp_pq.graph_node].end();iter++){
				if((*iter).graph_node>=0 && temp_pq.initial_letter!=(*iter).word[0] && not_visited((*iter).graph_node,(*iter).word[0])){
					//Put the element in set, to represent visited
					struct set_node set_push;
					set_push.graph_node = (*iter).graph_node;
					set_push.reach_letter = (*iter).word[0];
					visit_info.insert(set_push);
					//Put the element in queue, with distance updated
					struct queue_node push_elem;
					push_elem.graph_node = (*iter).graph_node;
					push_elem.dist = temp_pq.dist + word_length((*iter).word);
					push_elem.initial_letter = (*iter).word[0];

					pq.push(push_elem);
				}
			}*/
			for(map<int, vector<string> >::iterator iter = graph[temp_pq.graph_node].begin(); iter!=graph[temp_pq.graph_node].end();iter++){
				/*if((*iter).graph_node>=0 && temp_pq.initial_letter!=(*iter).word[0] && not_visited((*iter).graph_node,(*iter).word[0])){
					//Put the element in set, to represent visited
					struct set_node set_push;
					set_push.graph_node = (*iter).graph_node;
					set_push.reach_letter = (*iter).word[0];
					visit_info.insert(set_push);
					//Put the element in queue, with distance updated
					struct queue_node push_elem;
					push_elem.graph_node = (*iter).graph_node;
					push_elem.dist = temp_pq.dist + word_length((*iter).word);
					push_elem.initial_letter = (*iter).word[0];
					pq.push(push_elem);
				}*/
				for(vector<string>::iterator it = (iter->second).begin(); it!=(iter->second).end(); it++){
                    //Put the element in set, to represent visited
#ifdef DEBUG2
                    if((*it)!="?"){
                    cout << "Checking for " << (*it) << " to push" << endl;
                    }
#endif
                    if((*it)!="?" && temp_pq.initial_letter!=(*it)[0] && not_visited(iter->first,(*it))){
                        struct set_node set_push;
                        set_push.graph_node = iter->first;
                        set_push.reach_word = (*it);
                        visit_info.insert(set_push);
                        //Put the element in queue, with distance updated
                        struct queue_node push_elem;
                        push_elem.graph_node = iter->first;
                        push_elem.dist = temp_pq.dist + word_length((*it));
                        push_elem.initial_letter = (*it)[0];
#ifdef DEBUG2
                        cout << "pushing " << push_elem.graph_node << " having dist " << push_elem.dist << " " << (*it) << endl;
#endif // DEBUG2
                        pq.push(push_elem);
                    }
				}
			}

		}
		if(!found){
			cout << "impossivel" << endl;
		}
		else if(!cannot_be_found){
            cout << best_ans << endl;
		}
#endif
		cin >> edges;
	}

	return 0;
}
