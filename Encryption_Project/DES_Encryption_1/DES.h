#ifndef DES_h
#define DES_h

#include <string.h>
#include "datatypes.h"

/*$PAGE*/
/*
*********************************************************************************************************
*                                       FUNCTION PROTOTYPES
*********************************************************************************************************
*/
void encrypt(void* out, const void* in, const void* key) reentrant;

void decrypt(void* out, const void* in, const uint8_t* key) reentrant;

void permute(const uint8_t *ptable, const uint8_t *in, uint8_t *out) reentrant;

void changeendian32(uint32_t * a) reentrant;

void shiftkey(uint8_t *key) reentrant;

void shiftkey_inv(uint8_t *key) reentrant;

void splitin6bitwords(const unsigned char a[]) reentrant;

uint8_t substitute(uint8_t a, uint8_t * sbp) reentrant;

uint32_t des_f(uint32_t r, uint8_t* kr) reentrant;

#endif


