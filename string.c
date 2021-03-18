#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include "STRINGN.H"

struct StringN
{
    size_t dimension;
    size_t elSize;
    void* symbols;
};


void* GetN(size_t index, struct StringN* s)
{
    char* position = (char*)(s->symbols) + index*(s->elSize);
    return (void*)position;
}


struct StringN* SetN(size_t index, void* value, struct StringN* s)
{
    char* position = (char*)(s->symbols) + index*(s->elSize);
    memcpy((void*)position, value, s->elSize);
    return s;
}


struct StringN* CreateFromValues(size_t dimension, size_t elSize, void* values)
{
    struct StringN* s = malloc(sizeof(struct StringN));
    s->dimension = dimension;
    s->elSize = elSize;
    s->symbols = malloc(elSize * dimension);
    for (size_t i = 0; i < dimension; i++)
    {
        char* positionValue = (char*)malloc(sizeof(char));
        positionValue = (char*)values + i * elSize;
        SetN(i, (void*)positionValue, s);
    }
    return s;
}


struct StringN* Conc(struct StringN* s1, struct StringN* s2)
{
    if(!NULL)
    {
        struct StringN* s = malloc(sizeof(struct StringN));
        s->dimension = s1->dimension + s2->dimension;
        s->elSize = s1->elSize;
        s->symbols = malloc((s->elSize)*(s->dimension));
        for (size_t i = 0; i < (s1->dimension); i++)
        {
            char* position1 = (char*)(s1->symbols) + i * (s1->elSize);
            SetN(i, (void*) position1, s);
        }
        for (size_t j = 0; j < (s2->dimension); j++)
        {
            char* position2 = (char*)(s2->symbols) + j * (s2->elSize);
            SetN((s1->dimension + j), (void*) position2, s);
        }
        return s;
    }
    else
    {
        printf ("Error");
        return 0;
    }
}

struct StringN* Subs(struct StringN* s1, size_t i, size_t j)
{
    struct StringN* s = (struct StringN*)malloc(sizeof(struct StringN));
    s->dimension = j - i + 1;
    s->elSize = s1->elSize;
    s->symbols = malloc((s->elSize)*(s->dimension));
    for (size_t v = 0; v <= (j - i); v++)
    {
        void* el1 = GetN(i + v, s1);
        SetN(v, el1, s->symbols);
    }
    return s;
}

struct StringN* Bijection (struct StringN* s1, size_t index)
{
    struct StringN* s = malloc(sizeof(struct StringN));
    s->dimension = s1->dimension;
    s->elSize = s1->elSize;
    s->symbols = malloc((s->elSize)*(s->dimension));
    char* position = (char*)malloc(sizeof(char));
    position = (char*)s1->symbols + (s1->dimension - index - 1)*(s1->elSize);
    SetN(index, (void*) position, s);
    return s;
};

struct StringN* Recod(struct StringN* s1, struct StringN* (*Bijection)(struct StringN* s2, size_t index))
{
    struct StringN* s = malloc(sizeof(struct StringN));
    s->dimension = s1->dimension;
    s->elSize = s1->elSize;
    s->symbols = malloc((s->elSize)*(s->dimension));
    struct StringN* s2 = malloc(sizeof(struct StringN));
    for (size_t i = 0; i < (s->dimension) / 2; i++)
    {
        s2 = Bijection(s1, i);
        SetN(i, GetN(i, s2), s);
    }
    for (size_t j = s1->dimension / 2 + 1; j < (s1->dimension) / 2; j++)
    {
        s2 = Bijection(s1, j);
        SetN(j, GetN(j, s2), s);
    }
    return s;
}

