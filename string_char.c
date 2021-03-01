#include "string_char.h"
#include "STRINGN.H"
#include <string.h>

struct StringN
{
    size_t dimension;
    size_t elSize;
    void* symbols;
};


struct StringN* Create0Char(size_t size, struct StringN* s)
{
   if(!zero)
   {
        return Create0(size, s->elSize, s->symbols);
   }
}


struct StringN* CreateFromValuesChar(size_t size, struct StringN* s, void* values)
{
   if(!zero)
   {
        return CreateFromValues(size, s->elSize, s->symbols, values);
   }
}


void* GetNChar(size_t index, struct StringN* s)
{
    return GetN(index, s);
}


void* SetNChar (size_t index, char* value, struct StringN* s)
{
    void* valueVoid = malloc(sizeof(char));
    *(char*)valueVoid = *(char*)value;
    return SetN(index, valueVoid, s);
}


struct StringN* ConcChar(struct StringN* s1, struct StringN* s2)
{
    struct StringN* s = malloc(sizeof(struct StringN));
    char* symbolsChar1 = (char*)(malloc(sizeof(char)));
    char* symbolsChar2 = (char*)(malloc(sizeof(char)));
    *symbolsChar1 = *(char*)(s1->symbols);
    *symbolsChar2 = *(char*)(s2->symbols);
    s->symbols = strcat(symbolsChar1, symbolsChar2);
    s->dimension = s1->dimension + s2->dimension;
    s->elSize = s1->elSize;
    return s;
}


struct StringN* SubsChar(struct StringN* s1, size_t i, size_t j)
{
    struct StringN* s = malloc(sizeof(struct StringN));
    s->dimension = j - i;
    s->elSize = s1->elSize;
    (s->symbols) = (char*)(malloc((s->dimension)*sizeof(char)));
    for (size_t v = 0; v < (j - i); v++)
    {
        char* el1 = (char*)GetNChar(i + v, s1);
        SetNChar(v, el1, s->symbols);
    }
    return s;
}


struct StringN* BijectionChar (struct StringN* s1, size_t index)
{
    return Bijection(s1, index);
}


struct StringN* RecodChar(struct StringN* s1, struct StringN (*Bijection)(struct StringN* s2, size_t index), size_t index)
{
<<<<<<< HEAD
    return Recod(s1, void* (*BijectionChar)(void* s2, size_t index));
}
=======
    return Recod(s1, BijectionChar(s1, index));
};
>>>>>>> 71733cc (Builded project)
