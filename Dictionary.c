//Yash Bansal
//Dictionary.c
//implements Dictionary.h, manipulates HashTable

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Dictionary.h"
#include <strings.h>
#include <assert.h>

const int tableSize = 101;

typedef struct HashTableObj  *hashTable;

// rotate_left()
// rotate the bits in an unsigned int
unsigned int rotate_left(unsigned int value, int shift) {
  int sizeInBits = 8*sizeof(unsigned int);
  shift = shift & (sizeInBits - 1);
  if ( shift == 0 )
  return value;
  return (value << shift) | (value >> (sizeInBits - shift));
}
// pre_hash()
// turn a string into an unsigned int
unsigned int pre_hash(char* input) {
  unsigned int result = 0xBAE86554;
  while (*input) {
    result ^= *input++;
    result = rotate_left(result, 5);
  }
  return result;
}
// hash()
// turns a string into an int in the range 0 to tableSize-1
int hash(char* key, int tableSize){
  return pre_hash(key)%tableSize;
}

/* bucketList newNode(char* key){ //constructor for newNode, used in insert
  bucketListObj *N = malloc(sizeof(int)+ strlen(key) + 1);
  //N->item = (char *)calloc(strlen(key) + 1, sizeof(char));
  strcpy(N->item, key);
  N->next = NULL;
  return N;
}

void freeNode(bucketList *N){ //deconstructor for bucketList
  if(N != NULL && (*N) != NULL){
    free((*N)->item);
    free(N);
    *N = NULL;
  }

}
*/

HashTableObj 	*newHashTable(int size){ //creates new hashtable, allocates memory for attributes, returns hashTable
  HashTableObj *H;
  H = (HashTableObj *)malloc(sizeof(HashTableObj) + sizeof(bucketList)*size);
  assert(H != NULL);
  H->size = size;
  for(int i = 0; i < size; i++){
    H->bucket[i] = NULL;
  }
  return H;
}

void 		deleteHashTable(HashTableObj * H){ //frees entire table
  int i;
  if (H == NULL){
    return;
  }
  bucketListObj *next;
  if (H != NULL){
    for (i = 0; i < H->size; i++){
      if (H->bucket[i] != NULL){
        while (H->bucket[i]->next != NULL){
          next = H->bucket[i]->next;
          free(H->bucket[i]);
          H->bucket[i] = next;
        }
        next = H->bucket[i]->next;
        free(H->bucket[i]);
        H->bucket[i] = next;
      }
    }
    H->size = 0;
    free(H->bucket[i]);
    H->bucket[i] = NULL;
  }
}


bool		member(HashTableObj *H, char *str){ //checks if given string is member of hashtable
  int x = hash(str, H->size);
  while (H->bucket[x] != NULL){
      if (H->bucket[x]->item != str){
        H->bucket[x] = H->bucket[x]->next;
      }
      else if (H->bucket[x]->item == str){
        return 1;
      }
  }
  return 0;
}

void 		insert(HashTableObj *H, char *str){ //checks if string hash exists or not, inserts new node, denies duplicate
  bucketListObj *N = malloc(sizeof(int)+ strlen(str) + 1);
  strcpy(N->item, str);
  int x = hash(N->item, H->size);
  if(H->bucket[x] == 0){
    H->bucket[x] = N;
    N->next = NULL;
  }
  else{
    bucketListObj *temp = H->bucket[x];
    while (temp->next != NULL){
      temp = temp->next;
    }
    temp->next = N;
    N->next = NULL;
  }
}

bool		delete(HashTableObj *H, char *str){ //deletes requested string
  bucketListObj *prev;
  int x = hash(str, H->size);
  if (str == NULL || H == NULL){
    return 0;
  }
  while (strcmp(H->bucket[x]->item, str) != 0){
    prev = H->bucket[x];
    H->bucket[x] = H->bucket[x]->next;
  }
  if (strcmp(H->bucket[x]->item, str) == 0){
    H->bucket[x] = H->bucket[x]->next;
    free(prev);
  }
  else{
    prev->next = H->bucket[x]->next;
    free(H->bucket[x]);
  }
  return 1;
}


void		printHashTable(FILE *out, HashTableObj *H){ //prints all strings in hashtable 
  bucketListObj *temp;
  for (int i = 0; i < H->size; i++){
    if (H->bucket[i] != NULL){
      temp = H->bucket[i];
      fprintf(stdout, "%s\n", temp->item);
      while (temp != NULL){
        temp = temp->next;
      }
    }
  }
}
