#include <stdlib.h>
#include <stdio.h>
#include "bv.h"
#include <inttypes.h>

BitVector *bv_create(uint32_t bit_len){ //create bit vector of given length 
        BitVector *bv = (BitVector *)malloc(sizeof(BitVector));
        if(!bv){
                return 0;
        }
        bv->length = bit_len; //set vector lenght
        bv->vector = (uint32_t *)malloc(bv->length * sizeof(uint32_t)); //allocate memory for vector to hold bits 
        return bv;
}

void bv_delete(BitVector *v){ //frees memory allocated for vector 
        free(v->vector);
        free(v);
	v->length = 0;
}
uint32_t bv_length(BitVector *v){ //returns length of bit vector 
        if(v){
		return (v->length);
	}
	return 0;
}
void bv_set_bit(BitVector *v, uint32_t i){ //sets bit at index i of v
        v->vector[i] = 1;
}
void bv_clr_bit(BitVector *v, uint32_t i){ //clears bit at index i of v
        v->vector[i] = 0;
}
uint8_t bv_get_bit(BitVector *v, uint32_t i){ // returns bit at index i of v 
        return (v->vector[i]);
}

