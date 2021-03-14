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
    struct StringN* s = (struct StringN*)malloc(sizeof(struct StringN));
    s->dimension = j - i + 1;
    s->elSize = s1->elSize;
    //printf("%d\n", s->dimension);
    s->symbols = (char*)(malloc((s->dimension) * s->elSize));
    char* el1 = (char*)malloc(sizeof(char));
    for (size_t v = 0; v < s->dimension; v++)
    {
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

void GetNCharTest(void)
{
    int i;
    //Creating 1st test string
    struct StringN* string1 = (struct StringN*)malloc(sizeof(struct StringN));
    int size1 = 7;
    int elSize = sizeof(char);
    char symbols1[7] = {"Pointer"};
    string1->dimension = size1;
    string1->elSize = sizeof(char);
    string1->symbols = (void*)symbols1;
    //Creating 2nd test string
    struct StringN* string2 = (struct StringN*)malloc(sizeof(struct StringN));
    int sizeT = 6;
    char symbolsT[6] = {"String"};
    string2->dimension = 6;
    string2->elSize = sizeof(char);
    string2->symbols = (void*)symbolsT;
    //Test GetN
    assert((*(char*)GetNChar(0,string1))=='P');
    //Test SetN
    char value = 'd';
    char* pValue = &value;
    SetNChar(0, pValue, string1);
    //printf("string2: %s\n", ((char*)(string2->symbols)));
    struct StringN* s = (struct StringN*)malloc(sizeof(struct StringN));
    s->dimension = size1;
    s->elSize = sizeof(char);
    s = SetNChar(0, pValue, string1);
    char symbols3[7] = {"dointer"};
    assert((*(char*)s->symbols)==*symbols3);
    //Test CreateFromValues
    char symbolsBuf[7] = {"Pointer"};
    struct StringN* sBuf = (struct StringN*)malloc(sizeof(struct StringN));
    sBuf->dimension = size1;
    sBuf->elSize = sizeof(char);
    sBuf = CreateFromValuesChar(size1, elSize, (void*)symbolsBuf);
    for (i = 0; i < 7; i++)
    {
        //printf("%c\n", *(symbolsBuf + i*sizeof(char)));
        //printf("%c\n", *(char*)GetNChar(i, sBuf));
        assert((*(char*)GetNChar(i, sBuf))==*(symbolsBuf + i*sizeof(char)));
    }
    string1 = sBuf;
    struct StringN* s3 = (struct StringN*)malloc(sizeof(struct StringN));
    s3->dimension = sizeT;
    s3->elSize = sizeof(char);
    s3 = CreateFromValuesChar(sizeT, elSize, (void*)symbolsT);
    //Test Conc
    struct StringN* strConc = (struct StringN*)malloc(sizeof(struct StringN));
    strConc->dimension = 13;
    strConc->symbols = (char*)malloc(strConc->dimension * sizeof(char));
    strConc->elSize = sizeof(char);
    //printf("string2: %s", ((char*)(string2->symbols)));
    strConc = ConcChar(string1, s3);
    for (i = 0; i < 13; i++)
    {
        printf("%c\n", *(char*)GetNChar(i, strConc));
    }
    char symbols4[13] = {"PointerString"};
    for (i = 0; i < 13; i++)
    {
        //printf("%c\n", *(symbols4 + i*sizeof(char)));
       // printf("%c\n", *(char*)GetNChar(i, strConc1));
        assert((*(char*)GetNChar(i, strConc))==*(symbols4 + i * sizeof(char)));
    }
    //Test Subs
    struct StringN* strSubs = (struct StringN*)malloc(sizeof(struct StringN));
    strSubs->dimension = size1;
    strSubs->elSize = sizeof(char);
    strSubs = SubsChar(string1, 1, 4);
    char symbols5[4] = {"oint"};
    for (i = 0; i < strSubs->dimension; i++)
    {
        //printf("%c\n", *(symbols5 + i*sizeof(char)));
        //printf("%c\n", *(char*)GetNChar(i, strSubs));
        assert((*(char*)GetNChar(i, strSubs))==*(symbols5 + i*sizeof(char)));
    }
    //Test Bijection
    struct StringN* strBijection = (struct StringN*)malloc(sizeof(struct StringN));
    strBijection = RecodChar(string1, BijectionChar);
    strBijection->dimension = size1;
    strBijection->elSize = sizeof(char);
    char symbols6[7] = {"retniot"};
    for (i = 0; i < strBijection->dimension; i++)
    {
        printf("%c\n", *(symbols6 + i*sizeof(char)));
        printf("%c\n", *(char*)GetNChar(i, strBijection));
        assert((*(char*)GetNChar(i, strBijection))==*(symbols6 + i*sizeof(char)));
    }
    assert((*(char*)strBijection->symbols)==*symbols6);
    printf("Assertion succeed");
}

int main()
{
    int size;
    printf("Write length of 1st string: \n");
    scanf("%d", &size);
    char symbols[size];
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
    strSub->symbols = (char*)(malloc((strSub->dimension) * strSub->elSize));
    strSub = SubsChar(s1, (size_t)pos1, (size_t)pos2);
    //printf("1st string: %s\n", ((char*)(s1->symbols)));
    printf("Substring: %s\n", ((char*)(strSub->symbols)));

    int size2;
    printf("Write length of 2nd string: \n");
    scanf("%d", &size2);
    char symbols2[size2];
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

    struct StringN* strBijection = (struct StringN*)malloc(sizeof(struct StringN));
    strBijection->dimension = s1->dimension;
    strBijection->elSize = sizeof(char);
    strBijection = RecodChar(s1, BijectionChar);
    printf("Recoding of 1st string: %s\n", ((char*)(strBijection->symbols)));
    GetNCharTest();
}
