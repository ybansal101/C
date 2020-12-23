//Yash Bansal
//BST.c
//
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "BST.h"
#include <strings.h>



int insert(char *new_data,  BSTObj **pBST){
    if(!(*pBST)){
        BSTObj *newNode = malloc(sizeof(BSTObj));
        newNode->term = new_data;
        newNode->leftChild = NULL;
        newNode->rightChild = NULL;
        *pBST = newNode;
        return 0;
    }
    else if(strcmp(new_data, (*pBST)->term) < 0){
        insert(new_data, &(*pBST)->leftChild);
        return 0;
    }
    else if(strcmp(new_data, (*pBST)->term) > 0){
        insert(new_data, &(*pBST)->rightChild);
        return 0;
    }
    else{
        return -1;
    }
}
void inorderTraverse(FILE *out, BSTObj *T){
    if (T != NULL){
        inorderTraverse(out, T->leftChild);
        fprintf(stdout, "%s, ", T->term);
        inorderTraverse(out, T->rightChild);
    }
}
void preorderTraverse(FILE *out, BSTObj *T){
    if(T != NULL){
        fprintf(stdout, "%s, ", T->term);
        preorderTraverse(out, T->leftChild);
        preorderTraverse(out, T->rightChild);
    }
}
void postorderTraverse(FILE *out, BSTObj *T){
    if (T != NULL){
        postorderTraverse(out, T->leftChild);
        postorderTraverse(out, T->rightChild);
        fprintf(stdout, "%s, ", T->term);
    }
}
void inorderLeaves(FILE *out, BSTObj *T){
    if(T == NULL){
        fprintf(out, "NO LEAVES");
    }
    else if(T->leftChild == NULL && T->rightChild == NULL){
        fprintf(out, T->term);
    }
    else{
        inorderLeaves(out, T->leftChild);
        inorderLeaves(out, T->rightChild);
    }
}
BSTObj *find(char *term_to_find, BSTObj *T){
    if(T == NULL){
        return(NULL);
    }
    if(term_to_find < T->term){
        find(term_to_find, T->leftChild);
    }
    else if(term_to_find > T->term){
        find(term_to_find, T->rightChild);
    }
    else if(term_to_find == T->term){
        return(T);
    }
    return(NULL);
}
int treeHeight(BSTObj *T, int height){
    if(T == NULL){
        return 0;
    }
    else{
        int lheight = treeHeight(T->leftChild, 0);
        int rheight = treeHeight(T->rightChild, 0);
        if(lheight > rheight){
            return(lheight + 1);
        }
        else{
            return(rheight + 1);
        }
    }
}
BSTObj * copyTree(BSTObj *T){
    if (T == NULL ){
        return(NULL);
        }
    else{
        BSTObj *temp = (BSTObj*)malloc(sizeof(BSTObj)) ;
        temp->term = T->term;    //copying data
        temp->leftChild = copyTree(T->leftChild);    //cloning left child
        temp->rightChild = copyTree(T->rightChild);  //cloning right child
        return temp;
    }
}
void makeEmpty(BSTObj **pT){
    if(*pT != NULL){
        makeEmpty(&((*pT)->leftChild));
        makeEmpty(&((*pT)->rightChild));
        free(*pT);
    }
}


