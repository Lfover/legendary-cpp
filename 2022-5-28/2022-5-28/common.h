#ifndef _COMMON_H_
#define _COMMON_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <Windows.h>
#define ElemType int
void Swap(ElemType* a, ElemType* b)
{
	ElemType tmp = *a;
	*a = *b;
	*b = tmp;
}
#pragma warning(disable:4996)
#endif
