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
    if(index <= s->dimension)
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
        valueVoid = (void*)value;
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
    char* symbolsChar1 = (char*)(malloc((s1->dimension + s2->dimension)*sizeof(char)));
    char* symbolsChar2 = (char*)(malloc((s2->dimension)*sizeof(char)));
    symbolsChar1 = (char*)(s1->symbols);
    symbolsChar2 = (char*)(s2->symbols);
    s->symbols = (void*)strcat(symbolsChar1, symbolsChar2);
    s->dimension = s1->dimension + s2->dimension;
    s->elSize = s1->elSize;
    return s;
}


struct StringN* SubsChar(struct StringN* s1, size_t i, size_t j)
{
    if(j >= i && j <= s1->dimension)
    {
        for (int v = 0; v < (j - i+ 1); ++v)
        {
            memcpy(GetNChar(v, s1), GetNChar(i+v, s1), s1->elSize);
        }
        *(char*)GetNChar(j - i + 1, s1) = '\0';
        return s1;
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
    struct StringN* s = (struct StringN*)malloc(sizeof(struct StringN));
    s->dimension = s1->dimension;
    s->elSize = s1->elSize;
    s->symbols = malloc((sizeof(char))*(s->dimension));
    struct StringN* s2 = (struct StringN*)malloc(sizeof(struct StringN));
    s2->dimension = s1->dimension;
    s2->elSize = s1->elSize;
    s2->symbols = malloc((sizeof(char))*(s->dimension));
    for (size_t index = 0; index <= s1->dimension / 2; index++)
    {
        s = BijectionChar(s1, index);
        SetNChar(index, (char*)s->symbols + index * (s1->elSize), s2);
    }
    for (size_t index1 = s1->dimension / 2 + 1; index1 <= s1->dimension; index1++)
    {
        s = BijectionChar(s1, index1);
        SetNChar(index1, (char*)s->symbols + index1 * (s1->elSize), s2);
    }
    *(char*)GetNChar(s2->dimension, s2) = '\0';
    return s2;
}

void Test1()
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
    //Test Conc
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
    //Test GetN
    assert((*(char*)GetNChar(0, sTest1))=='P');
    //Test SetN
    char newValue = 'd';
    char* pnewValue = &newValue;
    char symbolsBuf[9] = {"dointer"};
    SetNChar(0, pnewValue, sTest1);
    assert((*(char*)sTest1->symbols)==*symbolsBuf);
    //Test Subs
    struct StringN* sTest3 = (struct StringN*)malloc(sizeof(struct StringN));
    int sizeTest3 = 9;
    char symbols3[9] = {"Pointer"};
    sTest3->dimension = sizeTest3;
    sTest3->elSize = elSize;
    sTest3->symbols = (void*)symbols3;
    struct StringN* strSubs = (struct StringN*)malloc(sizeof(struct StringN));
    strSubs->dimension = sizeTest1;
    strSubs->elSize = elSize;
    strSubs = SubsChar(sTest3, 1, 4);
    char symbolsSubs[6] = {"oint"};
    for (i = 0; i < 4; i++)
    {
        assert((*(char*)GetNChar(i, strSubs))==*(symbolsSubs + i * sizeof(char)));
    }
    free(strSubs);
    printf("Assertion1 succeed\n");
}

void Test2()
{
    int i;
    //Creating 1st test string
    struct StringN* sTest1 = (struct StringN*)malloc(sizeof(struct StringN));
    int sizeTest1 = 5;
    int elSize = sizeof(char);
    char symbols1[] = {"Void"};
    sTest1->dimension = sizeTest1;
    sTest1->elSize = elSize;
    sTest1->symbols = (void*)symbols1;
    //Test CreateFromValues
    char symBuf[] = {"Void"};
    struct StringN* sBuf = (struct StringN*)malloc(sizeof(struct StringN));
    sBuf->dimension = sizeTest1;
    sBuf->elSize = elSize;
    sBuf = CreateFromValuesChar(sizeTest1, elSize, (void*)symBuf);
    for (i = 0; i < 4; i++)
    {
        assert((*(char*)GetNChar(i, sBuf))==*(symBuf + i * sizeof(char)));
    }
    //Test Conc
    int sizeTest2 = 9;
    char symbols2[] = {"Function"};
    struct StringN* sTest2 = (struct StringN*)malloc(sizeof(struct StringN));
    sTest2->dimension = sizeTest2;
    sTest2->elSize = elSize;
    sTest2->symbols = symbols2;
    struct StringN* sTestT = (struct StringN*)malloc(sizeof(char));
    sTestT->dimension = sizeTest2;
    sTestT->elSize = elSize;
    sTestT = CreateFromValuesChar(sizeTest2, elSize, symbols2);
    struct StringN* strConc = (struct StringN*)malloc(sizeof(struct StringN));
    strConc->dimension = sizeTest1 + sizeTest2;
    strConc->elSize = elSize;
    strConc = ConcChar(sTest1, sTestT);
    char symbolsConc[] = {"VoidFunction"};
    for (i = 0; i < 12; i++)
    {
        assert((*(char*)GetNChar(i, strConc))==*(symbolsConc + i * sizeof(char)));
    }
    free(sTestT);
    free(strConc);
    //Test GetN
    assert((*(char*)GetNChar(0, sTest1))=='V');
    //Test SetN
    char newValue = 'd';
    char* pnewValue = &newValue;
    char symbolsBuf[] = {"doid"};
    SetNChar(0, pnewValue, sTest1);
    assert((*(char*)sTest1->symbols)==*symbolsBuf);
    //Test Subs
    struct StringN* sTest3 = (struct StringN*)malloc(sizeof(struct StringN));
    int sizeTest3 = 5;
    char symbols3[] = {"Void"};
    sTest3->dimension = sizeTest3;
    sTest3->elSize = elSize;
    sTest3->symbols = (void*)symbols3;
    struct StringN* strSubs = (struct StringN*)malloc(sizeof(struct StringN));
    strSubs->dimension = sizeTest1;
    strSubs->elSize = elSize;
    strSubs = SubsChar(sTest3, 0, 2);
    char symbolsSubs[] = {"Voi"};
    for (i = 0; i < 3; i++)
    {
        assert((*(char*)GetNChar(i, strSubs))==*(symbolsSubs + i * sizeof(char)));
    }
    free(strSubs);
    printf("Assertion2 succeed\n");
}

void Test3()
{
    int i;
    //Creating 1st test string
    struct StringN* sTest1 = (struct StringN*)malloc(sizeof(struct StringN));
    int sizeTest1 = 5;
    int elSize = sizeof(char);
    char symbols1[] = {"Book"};
    sTest1->dimension = sizeTest1;
    sTest1->elSize = elSize;
    sTest1->symbols = (void*)symbols1;
    //Test CreateFromValues
    char symBuf[] = {"Book"};
    struct StringN* sBuf = (struct StringN*)malloc(sizeof(struct StringN));
    sBuf->dimension = sizeTest1;
    sBuf->elSize = elSize;
    sBuf = CreateFromValuesChar(sizeTest1, elSize, (void*)symBuf);
    for (i = 0; i < 4; i++)
    {
        assert((*(char*)GetNChar(i, sBuf))==*(symBuf + i * sizeof(char)));
    }
    //Test Conc
    int sizeTest2 = 9;
    char symbols2[] = {"Integral"};
    struct StringN* sTest2 = (struct StringN*)malloc(sizeof(struct StringN));
    sTest2->dimension = sizeTest2;
    sTest2->elSize = elSize;
    sTest2->symbols = symbols2;
    struct StringN* sTestT = (struct StringN*)malloc(sizeof(char));
    sTestT->dimension = sizeTest2;
    sTestT->elSize = elSize;
    sTestT = CreateFromValuesChar(sizeTest2, elSize, symbols2);
    struct StringN* strConc = (struct StringN*)malloc(sizeof(struct StringN));
    strConc->dimension = sizeTest1 + sizeTest2;
    strConc->elSize = elSize;
    strConc = ConcChar(sTest1, sTestT);
    char symbolsConc[] = {"BookIntegral"};
    for (i = 0; i < 12; i++)
    {
        assert((*(char*)GetNChar(i, strConc))==*(symbolsConc + i * sizeof(char)));
    }
    free(sTestT);
    free(strConc);
    //Test GetN
    assert((*(char*)GetNChar(1, sTest1))=='o');
    //Test SetN
    char newValue = 'r';
    char* pnewValue = &newValue;
    char symbolsBuf[] = {"rook"};
    SetNChar(0, pnewValue, sTest1);
    assert((*(char*)sTest1->symbols)==*symbolsBuf);
    //Test Subs
    struct StringN* sTest3 = (struct StringN*)malloc(sizeof(struct StringN));
    int sizeTest3 = 5;
    char symbols3[] = {"Book"};
    sTest3->dimension = sizeTest3;
    sTest3->elSize = elSize;
    sTest3->symbols = (void*)symbols3;
    struct StringN* strSubs = (struct StringN*)malloc(sizeof(struct StringN));
    strSubs->dimension = sizeTest1;
    strSubs->elSize = elSize;
    strSubs = SubsChar(sTest3, 1, 2);
    char symbolsSubs[] = {"oo"};
    for (i = 0; i < 2; i++)
    {
        assert((*(char*)GetNChar(i, strSubs))==*(symbolsSubs + i * sizeof(char)));
    }
    free(strSubs);
    printf("Assertion3 succeed\n");
}

int main()
{
    int i;
    int size;
    printf("Write length of 1st string: \n");
    scanf("%d%*c", &size);
    char symbols[size + 1];
    printf("Write symbols of 1st string: \n");
    fgets(symbols, size + 1, stdin);
    printf("1st string: %s\n", symbols);
    struct StringN* s1 = (struct StringN*)malloc(sizeof(struct StringN));
    s1->dimension = size;
    s1->elSize = sizeof(char);
    s1->symbols = (void*)symbols;
    int pos;
    printf("Write number of symbol: \n");
    scanf("%d%*c", &pos);
    printf("Symbol of that index: %c\n", *(char*)GetNChar(pos,s1));
    int posChange = pos;
    char value;
    printf("Write new symbol of that index: \n");
    scanf("%s%*c", &value);
    char* pValue = &value;
    s1 = SetNChar((size_t)posChange, pValue, s1);
    printf("1st string with changed symbol: %s\n", (char*)s1->symbols);

    int size2;
    printf("Write length of 2nd string: \n");
    scanf("%d%*c", &size2);
    char symbols2[size2 + 2];
    printf("Write symbols of 2nd string: \n");
    fgets(symbols2, size2 + 1, stdin);
    printf("2nd string: %s\n", symbols2);

    struct StringN* s2 = (struct StringN*)malloc(sizeof(struct StringN));
    s2->dimension = size2;
    s2->elSize = sizeof(char);
    s2->symbols = (void*)symbols2;
    struct StringN* strConc = (struct StringN*)malloc(sizeof(struct StringN));
    strConc->dimension = size + size2;
    strConc->elSize = sizeof(char);
    strConc = ConcChar(s1, s2);
    printf("Concatenation of 1st (changed )and 2nd strings: %s\n", ((char*)(strConc->symbols)));
    free(s2);
    free(strConc);

    size_t pos1;
    printf("Write position of 1st index of 1st string: \n");
    scanf("%d%*c", &pos1);
    size_t pos2;
    printf("Write position of 2nd index of 1st string: \n");
    scanf("%d%*c", &pos2);
    struct StringN* strSub = (struct StringN*)malloc(sizeof(struct StringN));
    strSub->dimension = pos2 - pos1 + 1;
    strSub->elSize = sizeof(char);
    strSub = SubsChar(s1, (size_t)pos1, (size_t)pos2);
    printf("Substring of 1st string: %s\n", (char*)(strSub->symbols));
    free(strSub);

    int size3;
    printf("Write length of 3rd string: \n");
    scanf("%d%*c", &size3);
    char symbols3[size3 + 1];
    printf("Write symbols of 3rd string: \n");
    fgets(symbols3, size3 + 1, stdin);
    printf("3rd string: %s\n", symbols3);
    struct StringN* s3 = (struct StringN*)malloc(sizeof(struct StringN));
    s3->dimension = size3;
    s3->elSize = sizeof(char);
    s3->symbols = (void*)symbols3;
    struct StringN* strBijection = (struct StringN*)malloc(sizeof(struct StringN));
    strBijection->dimension = size3;
    strBijection->elSize = sizeof(char);
    strBijection = RecodChar(s3, BijectionChar);
    printf("Recoding of 3rd string: %s\n", ((char*)(strBijection->symbols)));
    free(strBijection);

    Test1();
    Test2();
    Test3();
}
