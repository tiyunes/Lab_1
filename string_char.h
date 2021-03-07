#pragma once
#ifndef STRING_CHAR_H_INCLUDED
#define STRING_CHAR_H_INCLUDED
#include <stdlib.h>

void* zero = NULL;

struct StringN;

struct StringN* Create0Char(size_t size1, size_t elSize, char* symbols);
struct StringN* CreateFromValuesChar(size_t size1, size_t elSize, void* symbols, void* values);

void* GetNChar(size_t index, struct StringN* s);
void* SetNChar (size_t index, char* value, struct StringN* s);


struct StringN* ConcChar(struct StringN* s1, struct StringN* s2);
struct StringN* SubsChar(struct StringN* s1, size_t i, size_t j);
struct StringN* BijectionChar (struct StringN* s1, size_t index);
struct StringN* RecodChar(struct StringN* s1, struct StringN* (*BijectionChar)(struct StringN*, size_t));

#endif // STRING_CHAR_H_INCLUDED
