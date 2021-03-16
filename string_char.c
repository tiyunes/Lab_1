#include "string_char.h"
#include "STRINGN.H"
#include <string.h>
#include <stdio.h>
#include <assert.h>

struct StringN
{
    size_t dimension;
    size_t elSize;
    void* symbols;
};


struct StringN* CreateFromValuesChar(size_t size1, size_t elSize, void* values)
{
   if(size1 != 0)
   {
        return CreateFromValues(size1, elSize, values);
   }
}


void* GetNChar(size_t index, struct StringN* s)
{
    if(index <= s->dimension - 1)
    {
        return GetN(index, s);
    }
    else
    {
        printf("Invalid input data. \n");
        exit(0);
    }
}


struct StringN* SetNChar (size_t index, char* value, struct StringN* s)
{
    if(index <= s->dimension)
    {
        void* valueVoid = malloc(sizeof(char));
        *(char*)valueVoid = *(char*)value;
        return SetN(index, valueVoid, s);
    }
    else
    {
        printf("Invalid input data. \n");
        exit(0);
    }
}


struct StringN* ConcChar(struct StringN* s1, struct StringN* s2)
{
    struct StringN* s = (struct StringN*)malloc(sizeof(struct StringN));
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
    if(j >= i)
    {
        struct StringN* s = (struct StringN*)malloc(sizeof(struct StringN));
        s->dimension = j - i + 1;
        s->elSize = s1->elSize;
        s->symbols = (char*)malloc(s1->elSize*(s->dimension + 2));
        for (int v = 0; v < s->dimension; ++v)
        {
            SetNChar(v, (char*)GetNChar(i + v, s1), s);
        }
        return s;
    }
    else
    {
        printf("Invalid input data. \n");
        exit(0);
    }
}


struct StringN* BijectionChar (struct StringN* s1, size_t index)
{
    if(index <= s1->dimension)
    {
            struct StringN* s = malloc(sizeof(struct StringN));
            s->dimension = s1->dimension;
            s->elSize = s1->elSize;
            s->symbols = malloc((sizeof(char))*(s->dimension));
            s = Bijection(s1, index);
            return s;
    }
    else
    {
        printf("Invalid input data. \n");
        exit(0);
    }
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
    for (size_t index = s1->dimension / 2 + 1; index <= s1->dimension; index++)
    {
        s = BijectionChar(s1, index);
        SetNChar(index, (char*)s->symbols + index * (s1->elSize), s2);
    }
    return s2;
}

void Test()
{
    int i;
    //Creating 1st test string
    struct StringN* sTest1 = (struct StringN*)malloc(sizeof(struct StringN));
    int sizeTest1 = 9;
    int elSize = sizeof(char);
    char symbols1[9] = {"Pointer"};
    sTest1->dimension = sizeTest1;
    sTest1->elSize = elSize;
    sTest1->symbols = (void*)symbols1;
    //Test CreateFromValues
    char symBuf[9] = {"Pointer"};
    struct StringN* sBuf = (struct StringN*)malloc(sizeof(struct StringN));
    sBuf->dimension = sizeTest1;
    sBuf->elSize = elSize;
    sBuf = CreateFromValuesChar(sizeTest1, elSize, (void*)symBuf);
    for (i = 0; i < 7; i++)
    {
        assert((*(char*)GetNChar(i, sBuf))==*(symBuf + i * sizeof(char)));
    }
    int sizeTest2 = 6;
    char symbols2[6] = {"Name"};
    struct StringN* sTest2 = (struct StringN*)malloc(sizeof(struct StringN));
    sTest2->dimension = sizeTest2;
    sTest2->elSize = elSize;
    sTest2->symbols = symbols2;
    struct StringN* sTestT = (struct StringN*)malloc(sizeof(char));
    sTestT->dimension = sizeTest2;
    sTestT->elSize = elSize;
    sTestT = CreateFromValuesChar(sizeTest2, elSize, symbols2);
    //Test Conc
    struct StringN* strConc = (struct StringN*)malloc(sizeof(struct StringN));
    strConc->dimension = sizeTest1 + sizeTest2;
    strConc->elSize = elSize;
    strConc = ConcChar(sTest1, sTestT);
    char symbolsConc[13] = {"PointerName"};
    for (i = 0; i < 11; i++)
    {
        assert((*(char*)GetNChar(i, strConc))==*(symbolsConc + i * sizeof(char)));
    }
    free(sTestT);
    free(strConc);
    //Test Subs
    struct StringN* strSubs = (struct StringN*)malloc(sizeof(struct StringN));
    strSubs->dimension = sizeTest1;
    strSubs->elSize = elSize;
    strSubs = SubsChar(sTest1, 1, 4);
    char symbolsSubs[6] = {"oint"};
    for (i = 0; i < 4; i++)
    {
        assert((*(char*)GetNChar(i, strSubs))==*(symbolsSubs + i * sizeof(char)));
    }
    free(strSubs);
    //Test GetN
    assert((*(char*)GetNChar(0, sTest1))=='P');
    //Test SetN
    char newValue = 'd';
    char* pnewValue = &newValue;
    char symbolsBuf[9] = {"dointer"};
    SetNChar(0, pnewValue, sTest1);
    assert((*(char*)sTest1->symbols)==*symbolsBuf);
    printf("Assertion succeed\n");
}

int main()
{
    int size;
    printf("Write length of 1st string: \n");
    scanf("%d", &size);
    char symbols[size + 2];
    printf("Write symbols of 1st string: \n");
    for (int i = 0; i < size; i++)
    {
        scanf("%s",(symbols + i));
    }
    printf("1st string: %s\n", symbols);
    struct StringN* s1 = (struct StringN*)malloc(sizeof(struct StringN));
    s1->dimension = size;
    s1->elSize = sizeof(char);
    s1->symbols = (void*)symbols;
    int pos;
    printf("Write number of symbol: \n");
    scanf("%d", &pos);
    printf("Symbol of that index: %c\n", *(char*)GetNChar(pos,s1));
    int posChange = pos;
    char value;
    printf("Write new symbol of that index: \n");
    scanf("%s", &value);
    char* pValue = &value;
    s1 = SetNChar((size_t)posChange, pValue, s1);
    printf("1st string with changed symbol: %s\n", (char*)s1->symbols);

    size_t pos1;
    printf("Write position of 1st index: \n");
    scanf("%d", &pos1);
    size_t pos2;
    printf("Write position of 2nd index: \n");
    scanf("%d", &pos2);
    struct StringN* strSub = (struct StringN*)malloc(sizeof(struct StringN));
    strSub->dimension = pos2 - pos1 + 1;
    strSub->elSize = sizeof(char);
    strSub = SubsChar(s1, (size_t)pos1, (size_t)pos2);
    printf("Substring: %s\n", (char*)(strSub->symbols));
    free(strSub);

    int size2;
    printf("Write length of 2nd string: \n");
    scanf("%d", &size2);
    char symbols2[size2 + 2];
    printf("Write symbols of 2nd string: \n");
    for (int i = 0; i < size2; i++)
    {
        scanf("%s",(symbols2 + i));
    }
    printf("2nd string: %s\n", symbols2);

    struct StringN* s2 = (struct StringN*)malloc(sizeof(struct StringN));
    s2->dimension = size2;
    s2->elSize = sizeof(char);
    s2->symbols = (void*)symbols2;
    struct StringN* strConc = (struct StringN*)malloc(sizeof(struct StringN));
    strConc->dimension = size + size2;
    strConc->elSize = sizeof(char);
    strConc = ConcChar(s1, s2);
    printf("Concatenation of 1st and 2nd strings: %s\n", ((char*)(strConc->symbols)));
    free(s2);
    free(strConc);

    struct StringN* strBijection = (struct StringN*)malloc(sizeof(struct StringN));
    strBijection->dimension = s1->dimension;
    strBijection->elSize = sizeof(char);
    strBijection = RecodChar(s1, BijectionChar);
    printf("Recoding of 1st string: %s\n", ((char*)(strBijection->symbols)));
    free(strBijection);
    Test();
}
