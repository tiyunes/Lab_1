#include "string_char.h"
#include "STRINGN.H"
#include <string.h>
#include <stdio.h>

struct StringN
{
    size_t dimension;
    size_t elSize;
    void* symbols;
};


struct StringN* Create0Char(size_t size1, size_t elSize, char* symbols)
{
   if(size1 != 0)
   {
        return Create0(size1, elSize, (void*)symbols);
   }
   else printf("%s", "Error");
}


struct StringN* CreateFromValuesChar(size_t size1, size_t elSize, void* symbols, void* values)
{
   if(size1 != 0)
   {
        return CreateFromValues(size1, elSize, symbols, values);
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
    char* symbolsChar1 = (char*)(malloc(sizeof(s1->dimension)));
    char* symbolsChar2 = (char*)(malloc(sizeof(s2->dimension)));
    symbolsChar1 = (char*)(s1->symbols);
    symbolsChar2 = (char*)(s2->symbols);
    s->symbols = (void*)strcat(symbolsChar1, symbolsChar2);
    s->dimension = s1->dimension + s2->dimension;
    s->elSize = s1->elSize;
    return s;
}


struct StringN* SubsChar(struct StringN* s1, size_t i, size_t j)
{
    struct StringN* s = malloc(sizeof(struct StringN));
    s->dimension = j - i;
    s->elSize = s1->elSize;
    s->symbols = (char*)(malloc((s->dimension) * sizeof(char)));
    for (size_t v = 0; v <= (j - i); v++)
    {
        char* el1 = (char*)malloc(sizeof(char));
        el1 = (char*)GetNChar(i + v, s1);
        SetNChar(v, el1, s);
    }
    return s;
}


struct StringN* BijectionChar (struct StringN* s1, size_t index)
{
    struct StringN* s = malloc(sizeof(struct StringN));
    s->dimension = s1->dimension;
    s->elSize = s1->elSize;
    s->symbols = malloc((sizeof(char))*(s->dimension));
    s = Bijection(s1, index);
    return s;
}


struct StringN* RecodChar(struct StringN* s1, struct StringN* (*BijectionChar)(struct StringN*, size_t))
{
    struct StringN* s = malloc(sizeof(struct StringN));
    s->dimension = s1->dimension;
    s->elSize = s1->elSize;
    s->symbols = malloc((sizeof(char))*(s->dimension));
    struct StringN* s2 = malloc(sizeof(struct StringN));
    s2->dimension = s1->dimension;
    s2->elSize = s1->elSize;
    s2->symbols = malloc((sizeof(char))*(s->dimension));
    for (size_t index = 0; index <= s1->dimension / 2; index++)
    {
        s = BijectionChar(s1, index);
        SetNChar(index, (char*)s->symbols + index * (s1->elSize), s2);
    }
    for (size_t index = s1->dimension / 2 +1 ; index <= s1->dimension; index++)
    {
        s = BijectionChar(s1, index);
        SetNChar(index, (char*)s->symbols + index * (s1->elSize), s2);
    }
    return s2;
}

int main()
{
    int size;
    scanf("%d", &size);
    char symbols[size];
    for (int i = 0; i < size; i++)
    {
        scanf("%s",(symbols + i));
    }
    printf("%s\n", symbols);
    struct StringN* s = (struct StringN*)malloc(sizeof(struct StringN));
    s->dimension = size;
    s->elSize = sizeof(char);
    s->symbols = (void*)symbols;
    char value = 'd';
    char* pValue = &value;

    //printf("%c\n", *(char*)GetNChar(1,s));

    //SetNChar(1, pValue, s);
    //printf("%s\n", (char*)s->symbols);

    //size_t elSize1 = sizeof(char);

    //struct StringN* str1 = (struct StringN*)malloc(sizeof(struct StringN));
    //str1 = CreateFromValuesChar(size, elSize1, symbols, s->symbols);
    //printf("%c\n", *(char*)(str1->symbols));

    int size2;
    //scanf("%d", &size2);
    //for (int i = 0; i < size2; i++)
    //{
   //     scanf("%s",(symbols2 + i));
    //}
    //printf("%s\n", symbols2);

    //struct StringN* s2 = (struct StringN*)malloc(sizeof(struct StringN));
    //s2->dimension = size2;
    //s2->elSize = sizeof(char);
    //s2->symbols = (void*)symbols2;

    //struct StringN* str2 = (struct StringN*)malloc(sizeof(struct StringN));
    //str2 = ConcChar(s, s2);
    //s->symbols = str2->symbols;
    //printf("%s\n", ((char*)(s->symbols)));

    //struct StringN* str2 = (struct StringN*)malloc(sizeof(struct StringN));
    //str2 = SubsChar(s, (size_t)1, (size_t)3);
    //printf("%s\n", ((char*)(str2->symbols)));


    struct StringN* str2 = (struct StringN*)malloc(sizeof(struct StringN));
    str2 = RecodChar(s, BijectionChar);
    printf("%s\n", ((char*)(str2->symbols)));
}
