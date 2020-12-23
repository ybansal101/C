#ifndef __BV_H__
#define __BV_H__

#include <inttypes.h>

typedef struct BitVector{
	uint32_t length;
	uint32_t *vector;
} BitVector;

BitVector *bv_create(uint32_t length);

void bv_delete(BitVector *b);

uint32_t bv_length(BitVector *b);

void bv_set_bit(BitVector *b, uint32_t i);

void bv_clr_bit(BitVector *b, uint32_t i);

uint8_t bv_get_bit(BitVector *b, uint32_t i);

#endif
