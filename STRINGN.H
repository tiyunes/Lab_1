#ifndef STRINGN_H_INCLUDED
#define STRINGN_H_INCLUDED
#include <stdlib.h>


struct StringN;

//I. Creating of an object
struct StringN* Create0(size_t dimension, size_t elSize, void* symbols);
struct StringN* CreateFromValues(size_t dimension, size_t elSize, void* symbols, void* values);

//II. Decomposition
void* GetN(size_t index, struct StringN* s);
struct StringN* SetN(size_t index, void* value, struct StringN* s);

//III. Operations
struct StringN* Conc(struct StringN* s1, struct StringN* s2);
struct StringN* Subs(struct StringN* s1, size_t i, size_t j);
struct StringN* Bijection (struct StringN* s1, size_t index);
struct StringN* Recod(struct StringN* s1, void* (*Bijection)(void* s2));

#endif // STRINGN_H_INCLUDED
