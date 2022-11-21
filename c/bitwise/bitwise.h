#ifndef __BITWISE_H__
#define __BITWISE_H__
#include<stddef.h>
#include<stdio.h>

long Pow2(unsigned int x, unsigned int y);

int IsPow2A(unsigned int n);

int IsPow2B(unsigned int n);

int AddOne(int n);

void PrintThreeBits(unsigned int * array, size_t arr_size);

void ByteMirrorLoop(unsigned char byte);

void ByteMirrorNoLoop(unsigned char byte);

int NoIfTwoAndSix(unsigned char byte);

int NoIfTwoOrSix(unsigned char byte);

unsigned char SwapThirdFifth(unsigned char byte);

#endif
