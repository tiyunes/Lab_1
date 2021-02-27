#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>

struct StringN
{
    size_t dimension;
    size_t elSize
    void* symbols;
};

struct StringN* Create0(size_t size, size_t elSize, void* symbols)
{
    struct StringN* s = malloc(sizeof(struct StringN));
    s->dimension = size;
    s->elSize = elSize;
    s->symbols = malloc(elSize*size);
    void* p0 = NULL;
    for (size_t i = 0; i < size; i++)
    {
        char* pos = (char*)s->symbols + i*s->elSize;
		memcpy((void*)pos, p0, s->elSize);
    }
}


struct StringN* CreateFromValues(size_t dimension, size_t elSize, void* symbols, void* values)
{
    struct StringN* s = malloc(sizeof(struct StringN));
    s->dimension = dimension;
    s->elSize = elSize;
    s->symbols = malloc(elSize*size);
    void* p0 = NULL;
    for (size_t i = 0; i < dimension; i++)
    {
        char* pos = (char*)s->symbols + i*s->elSize;
        memcpy((void*)pos, *(values+i), s->elSize);
    }
}


void* GetN(size_t index, struct StringN* s)
{
    void* pos = (s + index);
    return pos;
}


struct StringN* SetN(size_t index, void* value, struct StringN* s)
{
    *(s->symbols + index) = *value;
    return s;
}


struct StringN* Conc(struct StringN* s1, struct StringN* s2)
{
    if(s1&&s2)
    {
        struct StringN* s = malloc(sizeof(struct StringN));
        s->dimension = s1->dimension + s2->dimension;
        s->elSize = elSize;
        s->symbols = malloc(elSize*(s->dimension));
        for (size_t i = 0; i < (s1->dimension); i++)
        {
            setN(i, (s1 + i), s);
        }
        for (size_t j = 0; j < (s2->dimension); j++)
        {
            setN((s1->dimension + j), (s2 + j), s);
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
    struct StringN* s = malloc(sizeof(stringN));
    s->dimension = abs(i-j);
    s->elSize = s1->elSize;
    s->symbols = malloc(elSize*(s->dimension));
    for (size_t v = 0; v < (j - i); v++)
    {
        void* el1 = GetN(i + v, s1);
        SetN(v, el1, s->symbols);
    }
    return s;
}

struct StringN* Bijection (struct StringN* s1, size_t index)
{
    struct StringN* s = malloc(sizeof(stringN));
    s->dimension = s1->dimension;
    s->elSize = s1->elSize;
    s->symbols = malloc((s->elSize)*(s->dimension));
    *(s->symbols + index) = *(s1->symbols + s->dimension - index);
    return s;
};

struct StringN* Recod(struct StringN* s1, void* (*Bijection)(void* s2, size_t index))
{
    struct StringN* s = malloc(sizeof(stringN));
    s->dimension = s1->dimension;
    s->elSize = s1->elSize;
    s->symbols = malloc((s->elSize)*(s->dimension));
    for (size_t i = 0; i < (s->dimension); i++)
    {
        setN(i, Bijection(s1, i), s);
    }
    return s;
}

int main()
{

    return 0;
}
