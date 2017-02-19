#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <malloc.h>

//#define DEBUG 1

using namespace std;

int nr_piles;

struct element{
	char card[2];
	//int nr_card;
};

struct sll_elem{
	struct element elem;
	struct sll_elem *next;
};

struct dll_elem{
	//struct element elem;
	struct sll_elem *pile_head;
	struct dll_elem *next;
	struct dll_elem *prev;
	int nr_cards;
};

void insert_in_stack(struct dll_elem **head, struct dll_elem **tail, struct element elem){
	if(*head == NULL){
		struct dll_elem *temp = (struct dll_elem *)malloc(sizeof(struct dll_elem));
		struct sll_elem *top_card = (struct sll_elem *)malloc(sizeof(struct sll_elem));
		top_card->elem = elem;
		top_card->next = NULL;
		temp->pile_head = top_card;
		temp->prev = NULL;
		temp->next = NULL;
		temp->nr_cards = 1;
		(*tail) = (*head) = temp;
	}
	else{
		struct dll_elem *temp = (struct dll_elem *)malloc(sizeof(struct dll_elem));
		struct sll_elem *top_card = (struct sll_elem *)malloc(sizeof(struct sll_elem));
		top_card->elem = elem;
		top_card->next = NULL;
		temp->pile_head = top_card;
		temp->prev = (*tail);
		temp->next = NULL;
		temp->nr_cards = 1;
		(*tail)->next = temp;
		(*tail) = temp;
	}
	return;
}

void delete_from_stack(struct dll_elem *elem, struct dll_elem **head, struct dll_elem **tail){
	if((*tail) == elem){
		(*tail) = elem->prev;
	}

	if(elem->next!=NULL){
		elem->next->prev = elem->prev;
	}
	if(elem->prev!=NULL){
		elem->prev->next = elem->next;
	}
	//free(elem);
	free(elem);
}

void insert_in_inner_stack(struct sll_elem **head, struct element elem){
	if((*head) == NULL){
		(*head) = (struct sll_elem *)malloc(sizeof(struct sll_elem));
		(*head)->elem = elem;
		(*head)->next = NULL;
	}
	else{
		struct sll_elem *temp = (struct sll_elem *)malloc(sizeof(struct sll_elem));
		temp->elem = elem;
		temp->next = (*head);
		(*head) = temp;
	}
}

void delete_head_inner_stack(struct sll_elem **head){
	struct sll_elem *temp = (*head);
	(*head) = (*head)->next;
	free(temp);
}

struct sll_elem *top(struct dll_elem *elem){
	return (elem->pile_head);
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
	struct sll_elem *left_top = bottom->pile_head;
	struct sll_elem *right_top = top->pile_head;
    if((left_top->elem.card[0] == right_top->elem.card[0]) || (left_top->elem.card[1] == right_top->elem.card[1])){
        return true;
    }
    return false;
}

void remove_top_card(struct dll_elem *top, struct dll_elem **head, struct dll_elem **tail){
	if(top->nr_cards == 1){
		delete_from_stack(top,head,tail);
		nr_piles--;
	}
	else{
		top->nr_cards--;
		top->pile_head = top->pile_head->next;
	}
	return;
}

void simple_insert(struct dll_elem *left, struct element elem){
	struct sll_elem *temp = (struct sll_elem *)malloc(sizeof(struct sll_elem));
	temp->elem = elem;
	temp->next = left->pile_head;
	left->pile_head = temp;
	left->nr_cards++;
	return;
}

int main(){
    //freopen("output.txt","w",stdout);
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
			insert_in_stack(&head,&tail,temp_elem);
		}
		stringstream sss(line2);
		while(sss >> card){
			temp_elem.card[0] = card[0];
			temp_elem.card[1] = card[1];
			insert_in_stack(&head,&tail,temp_elem);
		}
#ifdef DEBUG
		struct dll_elem *iter = tail;
		while(iter!=NULL){
			cout << iter->pile_head->elem.card[0] << iter->pile_head->elem.card[1] <<" ";
			iter = iter->prev;
		}
		cout << endl;
#endif
        bool incomplete = true;
		nr_piles = 52;
        while(incomplete){
            //cout << "loop" << endl;
            incomplete = false;
            struct dll_elem *temp_iter = head;
            struct dll_elem *left_elem;
            while(temp_iter!=NULL){
                left_elem = prev_elem(temp_iter,3);

                if(left_elem && can_be_piled(left_elem,temp_iter)){
					//cout << "What is 1" << endl;
					temp_elem.card[0] = temp_iter->pile_head->elem.card[0];
					temp_elem.card[1] = temp_iter->pile_head->elem.card[1];
					remove_top_card(temp_iter,&head, &tail);
					simple_insert(left_elem,temp_elem);

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
				/*if(left_elem == temp_iter){
					cout << "WTF" << endl;
				}*/
                if(left_elem && can_be_piled(left_elem,temp_iter)){
					//cout << "What is 2" << endl;
					temp_elem.card[0] = temp_iter->pile_head->elem.card[0];
					temp_elem.card[1] = temp_iter->pile_head->elem.card[1];
					remove_top_card(temp_iter,&head, &tail);
					simple_insert(left_elem,temp_elem);

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
                temp_iter = temp_iter->next;
            }
        }

		cout << nr_piles;
		if(nr_piles > 1){
			cout << " piles ";
		}
		else{
			cout << " pile ";
		}
		cout << "remaining:";
        struct dll_elem *ret_iter = head;
        while(ret_iter!=NULL){
            cout << " " <<ret_iter->nr_cards;
            ret_iter = ret_iter->next;
        }
        cout << endl;

		getline(cin, line1);
	}
	return 0;
}
