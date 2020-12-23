//Yash Bansal
//Block.c
//handles the blocks of the chain

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"Block.h"
#define STR_LEN 100

typedef struct BlockObj{ //creates elements within each block
    int idx;
    char* string;
    long previousHash;
} BlockObj;

typedef BlockObj *Block;

Block newBlock(char* data, int id, long hash){ //constructor for Block type
    Block b = malloc(sizeof(BlockObj));
    assert(b!=NULL);
    b->idx = id;
    b->string = (char*)malloc(sizeof(char) * (strlen(data) + 1));
    strcpy(b->string, data);
    b->previousHash = hash;
    return(b);
}
void freeBlock(Block B){ //destructor for Block type
    if(B != NULL){
        free(B->string);
        free(B);
    }
}
char* data(Block B){ //returns the string saved within block
    if(B != NULL){
        return B->string;
    }
    return NULL;
}
long previousHash(Block B){ //returns the hash value of prev block, stored in
    if(B != NULL){         //requested block
        return B->previousHash;
    }
    return (long)NULL;
}
long hash(Block B){     //computes the hash value of given block, stored in next
    long hash = B->idx;//block
    hash += B->previousHash;
    char* ptr = B->string;
    while (*ptr != '\0') {
        hash += *ptr;
        ptr += 1;
    }
    return hash;
}
void printBlock(FILE* out, Block B){ //prints out block in requested format
    if(B == NULL){
        fprintf(stderr, "invalid block");
        exit(EXIT_FAILURE);
    }
    fprintf(out, "%d = %s\n", B->idx, B->string);
}
