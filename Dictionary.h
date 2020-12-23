
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#ifndef _DICTIONARY_H_INCLUDE_
#define _DICTIONARY_H_INCLUDE_


typedef struct bucketListObj  *bucketList;

typedef struct bucketListObj {
    bucketList 	next;
    char 	item[];
} bucketListObj;


typedef struct HashTableObj {
    int		size;
    bucketList bucket[];
} HashTableObj;


HashTableObj 	*newHashTable(int size);
void 		deleteHashTable(HashTableObj * H);
bool		member(HashTableObj *H, char *str);
void 		insert(HashTableObj *H, char *str);
bool		delete(HashTableObj *H, char *str);
void		printHashTable(FILE *out, HashTableObj *H);
#endif
