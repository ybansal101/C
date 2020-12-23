#include "ll.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

ListNode *top = NULL;
float links = 0; //number of nodes traveresed to locate node
float seeks = 0; //number of times ll_lookup is used
bool move_to_front  = false; 

ListNode *ll_node_create(GoodSpeak *gs){
	if(gs){
		ListNode *node = (ListNode *)malloc(sizeof(ListNode));
		if(node){
			node->gs = gs;
			node->next = NULL;
			top = node;
			return node;
		}
	}
	return (ListNode *)NIL;		
}

void ll_node_delete(ListNode *n){ 
	if(n){
		ListNode *temp = n->next;
		ListNode *prev = top;
		while(prev){
			if(prev == n && temp == NULL){
				top = temp;
				gs_delete(prev->gs);
				free(prev);
				return;
			} else if(prev == n){
				top = temp;
				gs_delete(prev->gs);
				free(prev);
				return;
			} else if(prev->next == n){
				prev->next = temp;
				free(n->gs);
				free(n);
				return;
			}
			prev = prev->next;
		}
	}
	return;
}

void ll_delete(ListNode *head){
	ListNode *temp;
	while(head){
		temp = head;
		head = head->next;
		ll_node_delete(temp);	
	}
}
	
GoodSpeak *ll_node_gs(ListNode *n){
	return n->gs;
}

ListNode *ll_insert(ListNode **head, GoodSpeak *gs){
	ListNode *new = ll_node_create(gs);
	if(new){
		new->next = *head;
		*head = new;
		return *head;	
	}
	printf("Failed to insert.\n");
	return *head;
}

ListNode *ll_lookup(ListNode **head, char *oldspeak){
	seeks++;
	ListNode *temp = *head;
	while(temp){
		if(strcmp(gs_oldspeak(temp->gs), oldspeak) == 0){
			move_to_front = true;
			return temp;
		}
		links++; 
		temp = temp->next;
	}
	return temp;
}

void ll_node_print(ListNode *n){
	if(n){
		if(gs_newspeak(n->gs)){
			printf("%s -> %s\n", gs_oldspeak(n->gs), gs_newspeak(n->gs));
			return;
		} else{
			printf("%s\n", gs_oldspeak(n->gs));
			return;
		}
	}
	printf("Node is empty\n");
}

void ll_print(ListNode *head){
	ListNode *temp = head;
	if(temp){
		while(temp){
			ll_node_print(temp);
			temp = temp->next;
		}
		return;
	}
	printf("Cannot print empty list.\n");
	return;
}


