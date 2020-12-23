#include "hash.h"
#include "speck.h"
#include "ll.h"
#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>

HashTable *ht_create(int length){
	HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
	if(ht){
		ht->salt[0] = 0x85ae998311115ae3;
		ht->salt[1] = 0xb6fac2ae33a40089;
		ht->length = length;
		ht->heads = (ListNode **)calloc(length, sizeof(ListNode *));
		return ht;
	}
	return (HashTable *)NIL;
}

void ht_delete(HashTable *h){
	if(h){
		for(int i = 0; i < h->length; i++){
			if(h->heads[i]){
				ll_delete(h->heads[i]);
			}
		}
		h->length = 0;
		free(h);	
	} else{
		printf("HashTable to delete is NULL.\n");
	}
	return;
}

ListNode *ht_lookup(HashTable *h, char *key){
	ListNode *temp;
	for(int i = 0; i < h->length; i++){
		temp = ll_lookup(&(h->heads[i]), key);
		if(temp){
			return temp;
		} 		
	}
	return (ListNode *)NIL;	
}

void ht_insert(HashTable *h, GoodSpeak *gs){
	int index = hash(h->salt, gs_oldspeak(gs));
	index = abs(index % h->length);
	//if(index > ht_count(h) - 1){
	//	printf("Hashtable is full!\n");
	//	return;
	//}
	if(ht_lookup(h, gs_oldspeak(gs))){
		return;
	} else{
		ll_insert(&(h->heads[index]), gs);
		return;
	}
}

int  ht_count(HashTable *h){
	if(h){
		return h->length;
	} 
	return 0;
}

void ht_print(HashTable *h){
	int i = 0;
	while(i < ht_count(h)){
		if(h->heads[i]){
			printf("list %d:\n", i);
			ll_print((h->heads[i]));	
		} /*else{
			printf("empty list head\n");
		}*/
		i++;
	}	
	return;
}
