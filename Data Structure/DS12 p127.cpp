#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <malloc.h>

#define DEBUG 1

using namespace std;

struct element{
	char card[2];
	int nr_card;
};

struct dll_elem{
	struct element elem;
	struct dll_elem *next;
	struct dll_elem *prev;
};

void insert_in_stack(struct dll_elem **head, struct dll_elem **tail, struct element elem){
	if(*head == NULL){
		struct dll_elem *temp = (struct dll_elem *)malloc(sizeof(struct dll_elem));
		temp->elem = elem;
		temp->prev = NULL;
		temp->next = NULL;
		(*tail) = (*head) = temp;
	}
	else{
		struct dll_elem *temp = (struct dll_elem *)malloc(sizeof(struct dll_elem));
		temp->elem = elem;
		temp->prev = (*tail);
		temp->next = NULL;
		(*tail)->next = temp;
		(*tail) = temp;
	}
	return;
}

void delete_from_stack(struct dll_elem *elem, struct dll_elem **tail){
	if((*tail) == elem){
		cout << "DL" << endl;
		(*tail) = elem->prev;
	}
	
	if(elem->next!=NULL){
		cout << "Delete condition 1" << endl;
		elem->next->prev = elem->prev;
	}
	if(elem->prev!=NULL){
		cout << "Delete condition 2" << endl;
		elem->prev->next = elem->next;
	}
	//free(elem);
	free(elem);
}

struct dll_elem *prev_elem(struct dll_elem *elem, int nr){
    for(int i=0;i<nr;i++){
        elem = elem->prev;
        if(elem==NULL){
            return NULL;
        }
    }
    return elem;
}

bool can_be_piled(struct dll_elem *bottom, struct dll_elem *top){
    if(bottom == NULL){
        return false;
    }
    if((bottom->elem.card[0] == top->elem.card[0]) || (bottom->elem.card[1] == top->elem.card[1])){
        return true;
    }
    return false;
}

int main(){
	string line1,line2,card;
	getline(cin, line1);
	while(line1[0]!='#'){
		struct dll_elem *head = NULL;
		struct dll_elem *tail = NULL;
		struct element temp_elem;
		getline(cin, line2);
		stringstream ss(line1);
		while(ss >> card){
			temp_elem.card[0] = card[0];
			temp_elem.card[1] = card[1];
			temp_elem.nr_card = 1;
			insert_in_stack(&head,&tail,temp_elem);
		}
		stringstream sss(line2);
		while(sss >> card){
			temp_elem.card[0] = card[0];
			temp_elem.card[1] = card[1];
			temp_elem.nr_card = 1;
			insert_in_stack(&head,&tail,temp_elem);
		}
#ifdef DEBUG
		struct dll_elem *iter = tail;
		while(iter!=NULL){
			cout << iter->elem.card[0] << iter->elem.card[1] <<" ";
			iter = iter->prev;
		}
		cout << endl;
#endif
        bool incomplete = true;
        while(incomplete){
            cout << "loop" << endl;
            incomplete = false;
            struct dll_elem *temp_iter = tail;
            struct dll_elem *left_elem;
            while(temp_iter!=head){
                left_elem = prev_elem(temp_iter,3);
				if(left_elem == temp_iter){
					cout << "WTF" << endl;
				}
                if(left_elem && can_be_piled(left_elem,temp_iter)){
					cout << "What is 1" << endl;
                    left_elem->elem.card[0] = temp_iter->elem.card[0];
                    left_elem->elem.card[1] = temp_iter->elem.card[1];
                    left_elem->elem.nr_card+=temp_iter->elem.nr_card;
                    delete_from_stack(temp_iter,&tail);
#ifdef DEBUG
					iter = tail;
					while(iter!=NULL){
						cout << iter->elem.card[0] << iter->elem.card[1] <<" ";
						iter = iter->prev;
					}
					cout << endl;
#endif
                    incomplete = true;
                    break;
                }
                left_elem = prev_elem(temp_iter,1);
				if(left_elem == temp_iter){
					cout << "WTF" << endl;
				}
                if(left_elem && can_be_piled(left_elem,temp_iter)){
					cout << "What is 2" << endl;
                    left_elem->elem.card[0] = temp_iter->elem.card[0];
                    left_elem->elem.card[1] = temp_iter->elem.card[1];
                    left_elem->elem.nr_card+=temp_iter->elem.nr_card;
                    delete_from_stack(temp_iter,&tail);
                    incomplete = true;
#ifdef DEBUG
					iter = tail;
					while(iter!=NULL){
						cout << iter->elem.card[0] << iter->elem.card[1] <<" ";
						iter = iter->prev;
					}
					cout << endl;
#endif
                    break;
                }
                temp_iter = temp_iter->prev;
            }
        }
        struct dll_elem *ret_iter = head;
        while(ret_iter!=NULL){
            cout << ret_iter->elem.nr_card << " ";
            ret_iter = ret_iter->next;
        }
        cout << endl;

		getline(cin, line1);
	}
	return 0;
}
