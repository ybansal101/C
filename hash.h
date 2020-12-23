#ifndef __HASH_H__
#define __HASH_H__

#include "gs.h"
#include "ll.h"
#include <inttypes.h>

typedef struct HashTable{
	uint64_t salt [2];
	int length;
	ListNode **heads;
} HashTable;

HashTable *ht_create(int length);

void ht_delete(HashTable *h);

ListNode *ht_lookup(HashTable *h, char *key);

void ht_insert(HashTable *h, GoodSpeak *gs);

int ht_count(HashTable *h);

void ht_print(HashTable *h);

#endif
