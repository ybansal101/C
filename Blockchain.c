//Yash Bansal
//Blockchain.c
//manipulates and handles the chain as a whole

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"Blockchain.h"
#define MAX_SIZE 100

typedef struct BlockchainObj{ //declares structure and node elements
    int size;
    Block *top;
    
} BlockchainObj;

Blockchain newBlockchain(){ //creates new list
    Blockchain b = malloc(sizeof(BlockchainObj));
    assert(b!=NULL);
    b->top = malloc(sizeof(Block) * MAX_SIZE);
    b->size = 0;
    return b;
}
void freeBlockchain(Blockchain B){ //deallocates chain of blocks
    if(B != NULL){
        for(int i =0; i < MAX_SIZE; i++){
            if(*(B->top + i) != NULL){
                free(*(B->top + i));
            }
        }
        B->size = 0;
        free(B);
    }
    else{
        fprintf(stderr, "chain does not exist.");
    }
}
int append(Blockchain B, char* data){ //adds new block with given string
    if(B != NULL && B->size < MAX_SIZE){
        long prevHash = 0;
        if (B->size > 0){
            prevHash = hash(*(B->top + B->size - 1));
        }
        Block b = newBlock(data,B->size,prevHash);
        *(B->top + B->size) = b; //interates through chain and places new block
        B->size += 1;           //at the end of chain
        return B->size;
    }
    else{
        return 0;
    }
}
int size(Blockchain B){ //returns chain length
    if(B != NULL){
        return B->size;
    }
    else{
        fprintf(stderr, "chain is empty");
        return 0;
    }
}
Block get(Blockchain B, int idx){ //returns a block given chain and index
    if(B != NULL){
        if(idx < MAX_SIZE && idx != -1){
            return *(B->top + idx);
        }
        else{
            return NULL;
        }
    }
    else{
        fprintf(stderr, "chain is empty");
        return 0;
    }
}
int valid(Blockchain B){ //validates the rule that block contains hash of prev
    int val = 0;        //block
    if(B != NULL){
        if(B->size > 1){
            long ph = hash(*(B->top));
            for(int i = 0; i < B->size; i++){
                if(previousHash(*(B->top + i)) == ph){
                    val = 1;
                    ph = hash(*(B->top + i)); //changes node head to next,
                }                            //gradually iterates and validates
                else{                       //all blocks, returns 0 or 1
                    val = 0;
                }
            }
        }
    }
    else{
        fprintf(stderr, "chain is empty");
        return 0;
    }
    return val;
}
void removeLast(Blockchain B){ //deallocates the last node of a given chain
    if(B == NULL){
        fprintf(stderr, "chain is empty");
    }
    else if(B->size == 1){ //if only one block, deletes that
        freeBlock(*(B->top));
        B->size = 0;
    }
    else{
        Block a = *(B->top + B->size - 1); //stores last block in new Block
        freeBlock(a);                     //dealloactes that block and
        B->size -= 1;                    //decrements size of chain
        
    }
}
void printBlockchain(FILE* out, Blockchain B){
    if(B == NULL){
        fprintf(stderr, "invalid chain");
        exit(EXIT_FAILURE);
    }
    else{
        for(int i = 0; i < B->size; i++){ //prints all blocks of requested
            printBlock(out, *(B->top + i)); //by iterating through and using
        }                                   //printBlock function
    }
   
}

